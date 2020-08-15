/*
Copyright 2020 @seb-ma

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "oled.h"
#if defined(OLED_DRIVER_ENABLE) && defined(RENDER_ANIMATIONS) && defined(BONGOCAT_ANIMATION)
#include QMK_KEYBOARD_H
#include "lib/lib8tion/lib8tion.h"

#include "oled_gfx_bongocat.h"

#define ANIM_FRAME_DURATION 250     // Duration of each frame (at standard pace)
#define ANIM_FRAME_DURATION_MIN 100 // Minimal duration of each frame
#define ANIM_FRAME_DURATION_MAX 500 // Maximal duration of each frame

/*
Frames of bongo cat playing on keyboard
Animation is done as follow:
- base frame (bongo cat with hands up)
- one of the 6 other frames (bongo cat with 1 hand on 1 of the 6 keys)
- base frame or one of the 3 opposite frames (witch gives bongo cat with 2 hands on 2 of the 6 keys)
- base frame if not previous
- ...
This gives 16 frames randomly displayed (1+6+3*3)
NB: it is possible to use one hand followed by the other cause the frames have no common pixels

To reduce memory size of frames, each frame is encoded with difference of "base" frame
Base frame is encoded with difference of union of all other frames + an empty frame

Encoding gives 3 arrays:
- index (delta index related to previous) of each difference between the frame and the base
- size of consecutive bytes that change from index (including identical isolated chars)
- values of differences
This mechanism permits to store less indexes

// NB: 70 bytes may be saved by using a single array containing the 3 data for all the frames (due to byte alignment)

Sources:
    Images:    Bongo cat: https://bongo-cat.glitch.me/
    Converter: https://javl.github.io/image2cpp/ (in Draw mode, use "Vertical - 1 bit per pixel")
    Optimizer: gen_bongocat.c

Frames:
- up:   2 hands up
- key1: 1st hand on key 1
- key2: 1st hand on key 2
- key3: 1st hand on key 3
- key4: 2nd hand on key 4
- key5: 2nd hand on key 5
- key6: 2nd hand on key 6
*/

/* Structure used to define differences with the base frame */
typedef struct {
    const uint8_t* idx_delta;
    const uint8_t* siz;
    const char*    val;
    uint16_t       nb_idx;
} t_diff;


/* The base frame */
static const t_diff diff_up = {.idx_delta = up_idx_delta, .siz = up_siz, .val = up_val, .nb_idx = sizeof(up_idx_delta)};
/* Other frames */
static const t_diff diffs[] = {
    {.idx_delta = diff_key1_up_idx_delta, .siz = diff_key1_up_siz, .val = diff_key1_up_val, .nb_idx = sizeof(diff_key1_up_idx_delta)},
    {.idx_delta = diff_key2_up_idx_delta, .siz = diff_key2_up_siz, .val = diff_key2_up_val, .nb_idx = sizeof(diff_key2_up_idx_delta)},
    {.idx_delta = diff_key3_up_idx_delta, .siz = diff_key3_up_siz, .val = diff_key3_up_val, .nb_idx = sizeof(diff_key3_up_idx_delta)},
    {.idx_delta = diff_key4_up_idx_delta, .siz = diff_key4_up_siz, .val = diff_key4_up_val, .nb_idx = sizeof(diff_key4_up_idx_delta)},
    {.idx_delta = diff_key5_up_idx_delta, .siz = diff_key5_up_siz, .val = diff_key5_up_val, .nb_idx = sizeof(diff_key5_up_idx_delta)},
    {.idx_delta = diff_key6_up_idx_delta, .siz = diff_key6_up_siz, .val = diff_key6_up_val, .nb_idx = sizeof(diff_key6_up_idx_delta)},
};

/* Render a diff frame on oled */
void render_diff(const t_diff* diff) {
    uint16_t index = 0;
    uint16_t offset = 0;
    // Draw only differences with the full frame
    for (uint16_t i = 0; i < diff->nb_idx; i++) {
        index += pgm_read_byte(diff->idx_delta + i);
        for (uint8_t j = 0; j < pgm_read_byte(diff->siz + i); j++) {
            oled_write_raw_byte(pgm_read_byte(diff->val + offset), index + j);
            offset++;
        }
    }
}

/* Structure used to determine next frame */
typedef struct {
    uint8_t previous_frame  : 4;
    uint8_t nb_since_frame0 : 4;
} bg_last_frames_t;
/* Description of last frames */
static bg_last_frames_t last_frames = {.previous_frame = 0, .nb_since_frame0 = 0};

/* Callback to render the first frame of the animation */
void bongocat_render_init_frame(t_animation* animation) {
    last_frames.previous_frame = 0;
    last_frames.nb_since_frame0 = 0;

    animation->start_timer = timer_read32();
    animation->frame_duration = ANIM_FRAME_DURATION;
    animation->frame_duration_min = ANIM_FRAME_DURATION_MIN;
    animation->frame_duration_max = ANIM_FRAME_DURATION_MAX;
    // Dependant to WPM
    animation->ratioPerc = 0;
    // Base frame
    render_diff(&diff_up);
}

/* Callback to render the next frame of the animation
 NB: the current rendering assumes that there is only the animation on the screen
 It doesn't clear previous screen but only apply differences
 To manage this case, modify behavior to do the following sequence:
 clear, render base, render diff (if this is not the base that is desired)
*/
void bongocat_render_next_frame(t_animation* animation) {
    static const uint8_t nb_diffs = sizeof(diffs) / sizeof(t_diff);
    animation->start_timer = timer_read32();
    // Alternate between base frame and others
    if (animation->ratioPerc == 0 || last_frames.nb_since_frame0 >= 2) {
        // No keyboard tap
        // or Two frames without displaying base frame. Display base frame
        bongocat_render_init_frame(animation);
    } else if (last_frames.previous_frame == 0) {
        // Previous frame is base. Randomly select another frame
        last_frames.previous_frame = random8_max(nb_diffs);
        last_frames.nb_since_frame0++;
        render_diff(&diffs[last_frames.previous_frame]);
    } else {
        // Base or an opposite paw
        uint8_t rnd = random8_max(1 + nb_diffs / 2);
        if (rnd == 0) {
            bongocat_render_init_frame(animation);
        } else {
            last_frames.previous_frame = ((last_frames.previous_frame / (nb_diffs / 2)) * (nb_diffs / 2) + 2 + rnd) % nb_diffs;
            last_frames.nb_since_frame0++;
            render_diff(&diffs[last_frames.previous_frame]);
        }
    }
}

#endif // defined(OLED_DRIVER_ENABLE) && defined(BONGOCAT_ANIMATION)
