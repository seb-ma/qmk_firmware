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
#pragma once
#ifdef OLED_DRIVER_ENABLE
#include QMK_KEYBOARD_H

/* MIN and MAX functions exist somewhere in QMK tree and may or may not be defined according to enabled features */
#ifndef MIN
#   define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#endif
#ifndef MAX
#   define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif

/* Simple call to oled_write_P with nb ' ' */
void oled_write_space_nb(const uint8_t nb);

#if !defined(MASTER_ONLY) && NB_ANIMATIONS > 0
#   define RENDER_ANIMATIONS
#endif


#ifdef RENDER_ANIMATIONS

/* Initialize functions pointers to render animations */
void oled_init_animations(void);

/* Render the defined animation */
void render_animation(void);

#endif // RENDER_ANIMATIONS

#ifdef POMODORO_TIMER

/* Initialize pomodoro */
void oled_init_pomodoro(void);

/* Display the pomodoro timer */
void render_pomodoro(void);

#endif // POMODORO_TIMER

#ifndef FOLLOWER_ONLY

/* Render all the status of the keyboard (21 cols × 8 rows) */
void render_status(void);

/* Check if this is a custom rgb key and process it if true
 (To be called in process_record_user)
*/
bool handle_oled(const uint16_t keycode, keyrecord_t *const record);

#endif // FOLLOWER_ONLY

#endif // OLED_DRIVER_ENABLE
