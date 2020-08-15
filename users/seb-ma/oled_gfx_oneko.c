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
#if defined(OLED_DRIVER_ENABLE) && defined(RENDER_ANIMATIONS) && defined(ONEKO_ANIMATION)
#include QMK_KEYBOARD_H
#include "lib/lib8tion/lib8tion.h"

#include "oled_gfx_oneko.h"

#define ANIM_FRAME_DURATION 200 // Duration of each frame (at standard pace)

// Number max of sprites to display between 2 moves
#define NB_MAX_TURNS_PLAYING 20

/*
Animation of Oneko randomly walking and playing through the screen
The animation alternates walking at random position on screen and actions (for a random number of steps)
There are 32 sprites (using symmetry) of 32×32.
Walking sprites are:
- up, down, left, right, up left, up right, down left, down right
- each direction is composed of 2 sprites
Actions sprites are:
- sleep, awake, mati, jare, kaki, togi up, togi down, togi left, togi right
- each action is composed of 2 sprites

Sources:
    Images:    https://github.com/tie/oneko
    Converter: https://javl.github.io/image2cpp/ (in Draw mode, use "Vertical - 1 bit per pixel")
    Optimizer: gen_oneko.c
*/

#define SPRITE_HEIGHT 32
#define SPRITE_WIDTH  32
/* Number of pixels to move */
#define MOVE_STEP_COLUMN 4
#define MOVE_STEP_ROW    2

#define NB_ROWS OLED_DISPLAY_HEIGHT
#define NB_COLS OLED_DISPLAY_WIDTH


/* Structure used to define differences with the base frame */
typedef struct {
    const uint8_t* idx_delta;
    const uint8_t* siz;
    const char*    val;
    uint16_t       nb_idx;
} t_diff;

/* Each animation is composed of 2 sprites */
#define NB_SPRITES_ANIM 2

/* Moves frames */
static const t_diff moves[3][2][NB_SPRITES_ANIM] = {
    // Up
    {
        {
            {.idx_delta = upleft1_idx_delta,  .siz = upleft1_siz,  .val = upleft1_val,  .nb_idx = sizeof(upleft1_idx_delta)},
            {.idx_delta = upleft2_idx_delta,  .siz = upleft2_siz,  .val = upleft2_val,  .nb_idx = sizeof(upleft2_idx_delta)},
        },
        {
            {.idx_delta = up1_idx_delta,      .siz = up1_siz,      .val = up1_val,      .nb_idx = sizeof(up1_idx_delta)},
            {.idx_delta = up2_idx_delta,      .siz = up2_siz,      .val = up2_val,      .nb_idx = sizeof(up2_idx_delta)},
        },
    },
    // Middle
    {
        {
            {.idx_delta = left1_idx_delta,    .siz = left1_siz,    .val = left1_val,    .nb_idx = sizeof(left1_idx_delta)},
            {.idx_delta = left2_idx_delta,    .siz = left2_siz,    .val = left2_val,    .nb_idx = sizeof(left2_idx_delta)},
        },
        {
            {.idx_delta = mati2_idx_delta,    .siz = mati2_siz,    .val = mati2_val,    .nb_idx = sizeof(mati2_idx_delta)},
            {.idx_delta = jare2_idx_delta,    .siz = jare2_siz,    .val = jare2_val,    .nb_idx = sizeof(jare2_idx_delta)},
        },
    },
    // Down
    {
        {
            {.idx_delta = dwleft1_idx_delta,  .siz = dwleft1_siz,  .val = dwleft1_val,  .nb_idx = sizeof(dwleft1_idx_delta)},
            {.idx_delta = dwleft2_idx_delta,  .siz = dwleft2_siz,  .val = dwleft2_val,  .nb_idx = sizeof(dwleft2_idx_delta)},
        },
        {
            {.idx_delta = down1_idx_delta,    .siz = down1_siz,    .val = down1_val,    .nb_idx = sizeof(down1_idx_delta)},
            {.idx_delta = down2_idx_delta,    .siz = down2_siz,    .val = down2_val,    .nb_idx = sizeof(down2_idx_delta)},
        },
    },
};

/* Actions frames */
enum action_sprites {
    ACT_SLEEP,
    ACT_AWAKE,
    ACT_MATI,
    ACT_JARE,
    ACT_KAKI,
    ACT_TOGI_L,
    ACT_TOGI_U,
    ACT_TOGI_D,

    ACT_SIZE,
};

static const t_diff actions[][NB_SPRITES_ANIM] = {
    // The only sprites that may not be reversed (they contain characters)
    {
        {.idx_delta = sleep1_idx_delta, .siz = sleep1_siz, .val = sleep1_val, .nb_idx = sizeof(sleep1_idx_delta)},
        {.idx_delta = sleep2_idx_delta, .siz = sleep2_siz, .val = sleep2_val, .nb_idx = sizeof(sleep2_idx_delta)},
    },
    // This sprites can be reversed but as they are symmetricals, it has no effect
    {
        {.idx_delta = mati2_idx_delta,  .siz = mati2_siz,  .val = mati2_val,  .nb_idx = sizeof(mati2_idx_delta)},
        {.idx_delta = awake_idx_delta,  .siz = awake_siz,  .val = awake_val,  .nb_idx = sizeof(awake_idx_delta)},
    },
    {
        {.idx_delta = mati2_idx_delta,  .siz = mati2_siz,  .val = mati2_val,  .nb_idx = sizeof(mati2_idx_delta)},
        {.idx_delta = mati3_idx_delta,  .siz = mati3_siz,  .val = mati3_val,  .nb_idx = sizeof(mati3_idx_delta)},
    },
    // All this sprites can be reversed
    {
        {.idx_delta = mati2_idx_delta,  .siz = mati2_siz,  .val = mati2_val,  .nb_idx = sizeof(mati2_idx_delta)},
        {.idx_delta = jare2_idx_delta,  .siz = jare2_siz,  .val = jare2_val,  .nb_idx = sizeof(jare2_idx_delta)},
    },
    {
        {.idx_delta = kaki1_idx_delta,  .siz = kaki1_siz,  .val = kaki1_val,  .nb_idx = sizeof(kaki1_idx_delta)},
        {.idx_delta = kaki2_idx_delta,  .siz = kaki2_siz,  .val = kaki2_val,  .nb_idx = sizeof(kaki2_idx_delta)},
    },
    {
        {.idx_delta = ltogi1_idx_delta, .siz = ltogi1_siz, .val = ltogi1_val, .nb_idx = sizeof(ltogi1_idx_delta)},
        {.idx_delta = ltogi2_idx_delta, .siz = ltogi2_siz, .val = ltogi2_val, .nb_idx = sizeof(ltogi2_idx_delta)},
    },
    {
        {.idx_delta = utogi1_idx_delta, .siz = utogi1_siz, .val = utogi1_val, .nb_idx = sizeof(utogi1_idx_delta)},
        // utogi2 = utogi1 reversed
        {.idx_delta = NULL, .siz = NULL, .val = NULL, .nb_idx = 0},
    },
    {
        {.idx_delta = dtogi1_idx_delta, .siz = dtogi1_siz, .val = dtogi1_val, .nb_idx = sizeof(dtogi1_idx_delta)},
        // dtogi2 = dtogi1 reversed
        {.idx_delta = NULL, .siz = NULL, .val = NULL, .nb_idx = 0},
    },
};

/* Structure used to determine next frame */
typedef struct {
    int8_t  current_frame;
    bool    current_frame_reversed;
    uint8_t current_position_row;
    uint8_t current_position_col;
    uint8_t destination_position_row;
    uint8_t destination_position_col;
} ok_last_frames_t;
/* Description of last frames */
static ok_last_frames_t last_frames;


/* Render a diff frame on oled */
void render_sprite(const t_diff* diff, const ok_last_frames_t* last_frames) {
    uint16_t index_sprite = 0;
    uint16_t offset = 0;
    // Draw the new frame
    for (uint16_t i = 0; i < diff->nb_idx; i++) {
        index_sprite += pgm_read_byte(diff->idx_delta + i);
        for (uint8_t j = 0; j < pgm_read_byte(diff->siz + i); j++) {
            uint8_t oled_x = last_frames->current_position_col;
            uint8_t oled_y = last_frames->current_position_row + 8 * ((index_sprite + j) / SPRITE_WIDTH);
            if (last_frames->current_frame_reversed) {
                oled_x += SPRITE_WIDTH - (index_sprite + j) % SPRITE_WIDTH;
            } else {
                oled_x += (index_sprite + j) % SPRITE_WIDTH;
            }
            const char value = pgm_read_byte(diff->val + offset);
            for (uint8_t b = 0; b < 8; b++) {
                oled_write_pixel(oled_x, oled_y + b, 1 & (value >> b));
            }
            offset++;
        }
    }
}

/*  Play a sequence of actions on place */
void do_action_sequence(ok_last_frames_t* last_frames, const int16_t remaining) {
    static uint8_t counter = 0;
    static uint8_t num_sprite = ACT_AWAKE;
    if (last_frames->current_frame == -1) {
        // First element of action
        counter = 0;
    }
    if (remaining == 1) {
        // Last element of action
        num_sprite = ACT_AWAKE;
        last_frames->current_frame = 0;
    } else {
        if (counter) {
            // Alternate sprites of same action
            last_frames->current_frame = (last_frames->current_frame + 1) % (NB_SPRITES_ANIM);
            counter--;
        } else {
            // Start a new sprite
            num_sprite = random8_max(ACT_SIZE);
            counter = 2 + random8_max(remaining > 0 ? remaining : NB_MAX_TURNS_PLAYING);
            last_frames->current_frame = 0;
            // reversed ?
            last_frames->current_frame_reversed = num_sprite != ACT_SLEEP && random8_max(2);
        }
    }
    if ((num_sprite == ACT_TOGI_U || num_sprite == ACT_TOGI_D)
            && last_frames->current_frame == 1) {
        // Sprite 2 does not exist: it is a reverse of sprite 1
        last_frames->current_frame = 0;
        last_frames->current_frame_reversed = !last_frames->current_frame_reversed;
    }
    if (last_frames->current_frame == 0) {
        oled_clear();
    }
    render_sprite(&actions[num_sprite][last_frames->current_frame], last_frames);
}

/* Callback to render the first frame of the animation */
void oneko_render_init_frame(t_animation* animation) {
    last_frames.current_frame = 0;
    last_frames.current_frame_reversed = false;
    last_frames.current_position_row = random8_max(NB_ROWS - SPRITE_HEIGHT);
    last_frames.current_position_col = random8_max(NB_COLS - SPRITE_WIDTH);
    last_frames.destination_position_row = last_frames.current_position_row;
    last_frames.destination_position_col = last_frames.current_position_col;

    animation->start_timer = timer_read32();
    animation->frame_duration = ANIM_FRAME_DURATION;
    // Not dependant to WPM
    animation->ratioPerc = -1;
    animation->frame_duration_min = ANIM_FRAME_DURATION;
    animation->frame_duration_max = ANIM_FRAME_DURATION;

    oneko_render_next_frame(animation);
}

/* Callback to render the next frame of the animation
 NB: the current rendering assumes that there is only the animation on the screen
*/
void oneko_render_next_frame(t_animation* animation) {
    static int16_t playing_step = 0;
    animation->start_timer = timer_read32();
    if (animation->ratioPerc == 0 || playing_step > 0) {
        // No keyboard tap or in waiting sequence: alternate action sprites
        do_action_sequence(&last_frames, playing_step);
        if (playing_step >= 0) {
            playing_step--;
        }
    } else {
        if (playing_step != 0) {
            // Wake up cat before walking
            do_action_sequence(&last_frames, 1);
            playing_step = 0;
            return;
        }
        int8_t i = 0;
        int8_t j = 0;
        last_frames.current_frame_reversed = false;
        // Clear the previous drawn frame
        oled_clear();

        if (last_frames.destination_position_row != last_frames.current_position_row) {
            i = (last_frames.destination_position_row > last_frames.current_position_row) ? 1 : -1;
            last_frames.current_position_row += (i == 1) ?
                MIN(last_frames.destination_position_row - last_frames.current_position_row, MOVE_STEP_ROW)
              : MAX(last_frames.destination_position_row - last_frames.current_position_row, -MOVE_STEP_ROW);
        }
        if (last_frames.destination_position_col != last_frames.current_position_col) {
            j = -1;
            last_frames.current_frame_reversed = (last_frames.destination_position_col > last_frames.current_position_col);
            last_frames.current_position_col += (last_frames.current_frame_reversed) ?
                 MIN(last_frames.destination_position_col - last_frames.current_position_col, i ? MOVE_STEP_ROW : MOVE_STEP_COLUMN)
               : MAX(last_frames.destination_position_col - last_frames.current_position_col, i ? -MOVE_STEP_ROW : -MOVE_STEP_COLUMN);
        }
        render_sprite(&moves[i + 1][j + 1][last_frames.current_frame], &last_frames);
        last_frames.current_frame = (last_frames.current_frame + 1) % (NB_SPRITES_ANIM);

        if (last_frames.destination_position_row == last_frames.current_position_row
         && last_frames.destination_position_col == last_frames.current_position_col) {
            // Define a new destination
            last_frames.destination_position_row = random8_max(NB_ROWS - SPRITE_HEIGHT);
            last_frames.destination_position_col = random8_max(NB_COLS - SPRITE_WIDTH);
            playing_step = 1 + random8_max(NB_MAX_TURNS_PLAYING);
            last_frames.current_frame = -1;
        }
    }
}

#endif // defined(OLED_DRIVER_ENABLE) && defined(ONEKO_ANIMATION)
