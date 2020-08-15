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

/* Structure of data user stored in eeprom */
typedef union {
    uint32_t raw;
    struct {
        bool     unicode      : 1; // UNICODE on or off
        bool     oled2        : 1; // OLED 2  on or off
        uint8_t  animation_idx: 3; // Index of animation to display
      //uint32_t unused       :27;
    };
} user_config_t;

/* Data user stored in eeprom */
extern user_config_t user_config;
