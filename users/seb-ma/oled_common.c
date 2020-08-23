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
#include "oled.h"
#include "transport_user.h"

#if !defined(MASTER_ONLY)
// This array only exists to have a define of NB_ANIMATIONS
char compute_nb_animations[NB_ANIMATIONS];
#endif

/* Simple call to oled_write_P with nb ' ' */
void oled_write_space_nb(const uint8_t nb) {
    for (uint8_t i = 0; i < nb; ++i) {
       oled_write_P(PSTR(" "), false);
    }
}

/* Callback (used by core) at the start of oled_init */
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#ifdef RENDER_ANIMATIONS
    oled_init_animations();
#endif
#if defined(POMODORO_TIMER) && !defined(MASTER_ONLY)
    oled_init_pomodoro();
#endif

    return OLED_ROTATION_180;
}

/* Callback (used by core) to handle screen displaying */
void oled_task_user(void) {
    if (is_keyboard_master()) {
#ifndef FOLLOWER_ONLY
        // Renders the current keyboard state (layers, modifiers...)
        render_status();
#endif
    } else if (user_data_m2s.oled2) {
#ifdef RENDER_ANIMATIONS
        // Renders the animation
        render_animation();
#endif
#if defined(POMODORO_TIMER) && !defined(MASTER_ONLY)
        render_pomodoro();
#endif
    } else {
        oled_off();
    }
}

#endif // OLED_DRIVER_ENABLE
