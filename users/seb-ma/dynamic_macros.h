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
#ifdef DYNAMIC_MACRO_ENABLE
#include QMK_KEYBOARD_H

/* Check if this is a macro key and process it if true
 (To be called in process_record_user)
*/
bool handle_dynamic_macro(const uint16_t keycode, keyrecord_t* record);

/* Definition of a macro state */
typedef struct {
    bool     recording;        // Is currently recording
    uint32_t timer_played;     // Last playing time
    uint32_t timer_last_error; // Last error time
} t_dyn_macros_state;

/* State of the 2 available dynamic macros */
extern t_dyn_macros_state dyn_macros_state[];

#endif // DYNAMIC_MACRO_ENABLE
