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
#ifdef USER_CLOSE_CHAR
#include QMK_KEYBOARD_H

/* Handle the keys corresponding to an opening char: "(«[{
 Return the key itself or the first closing key if this is the special close key
*/
uint16_t handle_open_close_char(const uint16_t keycode, const bool ignore_mods, const keyrecord_t *const record, const uint16_t previous_keycode);

#endif // USER_CLOSE_CHAR
