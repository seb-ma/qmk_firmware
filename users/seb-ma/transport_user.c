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
#include QMK_KEYBOARD_H
#include "transport_user.h"

/* Data user transmitted from master halve to follower */
user_data_m2s_t user_data_m2s;

#ifdef TRANSPORT_USER_DATA

/* To be called in transport layer (function transport_master) to transmit user data from master to follower */
uint32_t get_user_data_m2s_user(void) {
    return user_data_m2s.raw;
}

/* To be called in transport layer (function transport_slave) to store user data from master to follower */
void set_user_data_m2s_user(uint32_t user_data) {
    user_data_m2s.raw = user_data;
}

#endif // TRANSPORT_USER_DATA
