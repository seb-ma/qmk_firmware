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
#ifdef TAP_DANCE_ENABLE

/* Tap dance keys declarations */
enum tapdances {
    TD_COMM_QUOTE = 0, // Single: ','           Double: '''
    TD_GUIS,           // Single: KC_LGUI       Double: KC_APP
#ifdef MOUSEKEY_ENABLE
    TD_MS_BTNS,        // Single: KC_MS_BTN1    Double: KC_MS_BTN2
    TD_MS_ACCEL,       // Single: KC_MS_ACCEL0  Double: KC_MS_ACCEL1; Triple: KC_MS_ACCEL2
#endif
};

#endif // TAP_DANCE_ENABLE
