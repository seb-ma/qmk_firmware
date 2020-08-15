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
#ifdef USER_CLOSE_CHAR
#include "keymap_bepo.h"

#include "user_feature_closechar.h"

/* List of close char related to the open ones */
static uint16_t close_char[MAX_CLOSE_CHAR] = {C_DUMMY};
/* Index of first close char to output */
static int8_t index_close_char = -1;

_Static_assert(MAX_CLOSE_CHAR <= 128, "Variable index_close_char must be declared on > 8 bits (int16_t)");

/* Structure of association between open char and close char */
typedef struct {
    const uint16_t open;
    const uint16_t close;
} close_char_map_t;

/* List of association between open char and close char */
const close_char_map_t close_char_map[] = {
    {BP_DQUO, BP_DQUO}, // ""
    {BP_LDAQ, BP_RDAQ}, // «»
    {BP_LPRN, BP_RPRN}, // ()
    {BP_LCBR, BP_RCBR}, // {}
    {BP_LBRC, BP_RBRC}, // []
};

/* Handle the keys corresponding to an opening char: "(«[{
 Return the key itself or the first closing key if this is the special close key
*/
uint16_t handle_open_close_char(const uint16_t keycode, const bool ignore_mods, const keyrecord_t *const record, const uint16_t previous_keycode) {
    if (record->event.pressed) {
        if (keycode == C_CLOSE_CHAR_CLEAR) {
            // Clear buffer
            index_close_char = -1;
            close_char[0] = C_DUMMY;
            return C_DUMMY;
        } else if (keycode == C_CLOSE_CHAR) {
            // Get the last related close char
            const uint16_t keycode_close_char = closechar_pop();
            // Append a nbsp for the specific case of '»'
            if (keycode_close_char == BP_RDAQ && previous_keycode != BP_NBSP) {
                tap_nbsp_u();
                nb_char_sent = 2;
            }
            return keycode_close_char;
        } else {
            const uint16_t keycode_mods = ignore_mods ? keycode : get_keycode_with_mods_applied(keycode);
            if (index_close_char >= 0 && keycode_mods == close_char[index_close_char]) {
                // If the close char was manually tapped, remove it
                index_close_char--;
                return keycode;
            } else if (keycode == KC_BSPACE && index_close_char >= 0) {
                for (uint8_t i = 0; i < sizeof(close_char_map) / sizeof(close_char_map_t); i++) {
                    // If the open char was a mistake (backspaced), remove the last close char
                    if (close_char_map[i].open == previous_keycode && close_char_map[i].close == close_char[index_close_char]) {
                        index_close_char--;
                        return keycode;
                    }
                    // If the close char was a mistake (backspaced), retreive the last close char
                    if (close_char_map[i].close == previous_keycode) {
                        index_close_char++;
                        return keycode;
                    }
                }
            } else {
                closechar_push(keycode_mods);
            }
        }
    } else if (keycode == C_CLOSE_CHAR) {
        return close_char[index_close_char + 1];
    }
    return keycode;
}

/* If keycode is a close char, push it to the buffer */
void closechar_push(const uint16_t keycode) {
    if (index_close_char < MAX_CLOSE_CHAR - 2) {
        // If this is an open char, store the related close char
        for (uint8_t i = 0; i < sizeof(close_char_map) / sizeof(close_char_map_t); i++) {
            if (close_char_map[i].open == keycode) {
                close_char[++index_close_char] = close_char_map[i].close;
                break;
            }
        }
    }
}

/* Pop the last close char from buffer */
uint16_t closechar_pop(void) {
    if (index_close_char >= 0) {
        return close_char[index_close_char--];
    }
    return C_DUMMY;
}

#endif // USER_CLOSE_CHAR
