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
#ifdef OLED_DRIVER_ENABLE
#ifndef MASTER_ONLY

#include <stdio.h>

#include "oled.h"
#include "oled_follower.h"
#include "oled_custom_font_constants.h"
#include "transport_user.h"

#ifdef RENDER_ANIMATIONS
/* Pointers on function to render init frame of each animation */
render_init_frame_fct render_init[NB_ANIMATIONS];
#endif // RENDER_ANIMATIONS


#if defined(POMODORO_TIMER) && !defined(MASTER_ONLY)

/* bi-state value used as a trigger to reinit pomodoro */
static bool previous_pomodoro_reinit_state;
uint32_t pomodoro_start_timer = 0;

/* Initialize pomodoro */
void oled_init_pomodoro(void) {
    previous_pomodoro_reinit_state = user_data_m2s.pomodoro_reinit_toggle;
}

/* Display the pomodoro timer */
void render_pomodoro(void) {
    // Handle the toggle command
    if (previous_pomodoro_reinit_state != user_data_m2s.pomodoro_reinit_toggle) {
        previous_pomodoro_reinit_state = user_data_m2s.pomodoro_reinit_toggle;
#ifdef RENDER_ANIMATIONS
        // Reinit display
        oled_clear();
        render_init[user_data_m2s.animation_idx](&animation);
#endif
        if (pomodoro_start_timer == 0) {
            pomodoro_start_timer = timer_read32();
        } else {
            pomodoro_start_timer = 0;
            oled_set_cursor(0, 7);
            oled_write_space_nb(7);
        }
    }
    // A timer is running
    if (pomodoro_start_timer != 0) {
        const uint32_t time_s = MAX(0, (POMODORO_TIMER * 60) - (timer_elapsed32(pomodoro_start_timer) / 1000));
        char pomodoro_str[6];
        oled_set_cursor(0, 7);
        oled_write_P(logos_1row[LOGO_POMODORO], time_s == 0); // 2
        sprintf(pomodoro_str, "%02lu:%02lu", time_s / 60, time_s % 60);
        oled_write(pomodoro_str, time_s == 0); // 5
        if (time_s == 0) {
            pomodoro_start_timer = 0;
        }
    }
}

#endif // defined(POMODORO_TIMER) && !defined(MASTER_ONLY)


#ifdef RENDER_ANIMATIONS

/* Declaration of the animation */
t_animation animation;

/* Timer for continuing animation before stopping OLED */
uint32_t timeout_animation = 0;

/* bi-state value used as a trigger to reinit animation */
static bool previous_anim_reinit_state;
/* Last index of animation displayed */
static uint8_t previous_anim_index;

/* Pointers on function to render next frame of each animation */
render_next_frame_fct render_next[NB_ANIMATIONS];

/* Declaration of a shared buffer that can be used by animations */
char shared_animation_buffer[MAX_SHARED_ANIMATION_BUFFER];

/* Initialize functions pointers to render animations */
void oled_init_animations(void) {
    uint8_t i = 0;
#   ifdef BONGOCAT_ANIMATION
    render_init[i]   = bongocat_render_init_frame;
    render_next[i++] = bongocat_render_next_frame;
#   endif
#   ifdef LIFE_ANIMATION
    render_init[i]   = gamelife_render_init_frame;
    render_next[i++] = gamelife_render_next_frame;
#   endif
#   ifdef POMODORO_ANIMATION
    render_init[i]   = pomodoro_render_init_frame;
    render_next[i++] = pomodoro_render_next_frame;
#   endif
#   ifdef ONEKO_ANIMATION
    render_init[i]   = oneko_render_init_frame;
    render_next[i++] = oneko_render_next_frame;
#   endif
#   ifdef STARFIELD_ANIMATION
    render_init[i]   = starfield_render_init_frame;
    render_next[i++] = starfield_render_next_frame;
#   endif

    previous_anim_reinit_state = !user_data_m2s.anim_reinit_toggle;
    previous_anim_index = -1;
}

/* Render the defined animation */
void render_animation(void) {
    if (animation.ratioPerc != -1) {
#   ifdef WPM_ENABLE
        // Compute the ratio to apply to pace animation based on current word per minute typping
        animation.ratioPerc = (get_current_wpm() == 0) ? 0 : MIN(animation.frame_duration_max, MAX(animation.frame_duration_min, 100 * get_current_wpm() / STANDARD_WPM));
#   else
        animation.ratioPerc = -1;
#   endif
    }

#   ifdef WPM_ENABLE
    // Switch off if timeout without key pressed and no pomodoro running
    // XXX: Find a clean way to have key press detection without WPM_ENABLE (add it to custom transport)
    if (get_current_wpm() > 0
#       ifdef POMODORO_TIMER
        || pomodoro_start_timer != 0
#       endif // POMODORO_TIMER
    ) {
        timeout_animation = timer_read32();
    } else if (timer_elapsed32(timeout_animation) > OLED_TIMEOUT) {
        oled_off();
        return;
    }
#   endif

    if (user_data_m2s.anim_reinit_toggle != previous_anim_reinit_state
    || user_data_m2s.animation_idx != previous_anim_index) {
        // Restart animation
        previous_anim_reinit_state = user_data_m2s.anim_reinit_toggle;
        previous_anim_index = user_data_m2s.animation_idx;
        oled_clear();
        render_init[user_data_m2s.animation_idx](&animation);
        animation.start_timer = timer_read32();
    } else if ((animation.ratioPerc <= 0 && timer_elapsed32(animation.start_timer) > animation.frame_duration)
            || (animation.ratioPerc > 0  && timer_elapsed32(animation.start_timer) > animation.frame_duration * 100 / animation.ratioPerc)) {
        // Renders next frame of the animation if time's up
        if (render_next[user_data_m2s.animation_idx](&animation)) {
            animation.start_timer = timer_read32();
        }
    }
}
#endif // RENDER_ANIMATIONS

#endif // MASTER_ONLY
#endif // OLED_DRIVER_ENABLE
