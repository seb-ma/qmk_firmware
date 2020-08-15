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
#include QMK_KEYBOARD_H

/* Structure of data user transmitted from master halve to follower */
typedef union {
    uint32_t raw;
    struct {
        bool    oled2                 : 1; // OLED 2 on or off
        uint8_t animation_idx         : 3; // Index of animation to display
        bool    anim_reinit_toggle    : 1; // Used as a trigger to reinit animation
        bool    pomodoro_reinit_toggle: 1; // Used as a trigger to reinit pomodoro timer
      //uint8_t unused                :26;
    };
} user_data_m2s_t;

/* Data user transmitted from master halve to follower */
extern user_data_m2s_t user_data_m2s;
