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
#ifdef LEADER_ENABLE
#include QMK_KEYBOARD_H

/* Leader keys definitions
 To be called in matrix_scan_user
*/
void handle_leader_key(void);

/* Definition of a leader sequence state */
typedef struct {
    uint16_t timer;
    bool     is_success;
} t_leader_state;

/* State of leader sequence */
extern t_leader_state leader_state;

#endif // LEADER_ENABLE
