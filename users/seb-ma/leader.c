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
#ifdef LEADER_ENABLE
#include <string.h>
#include "keymap_bepo.h"

#include "custom_keys.h"
#include "eeprom_user.h"
#include "leader.h"
#include "oled.h"
#include "rgb.h"

#ifndef NO_SECRETS
#   include "secrets.h" // file may not exist
#endif


LEADER_EXTERNS();

/* State of leader sequence */
t_leader_state leader_state = {.is_success = false, .name = "", .timer = 0};

/* Set the state of the leader sequence */
void set_leader_state(bool is_success, const char* const name) {
    leader_state.is_success = is_success;
    leader_state.timer = timer_read();
//    strlcpy(leader_state.name, name, sizeof(leader_state.name));
}

/* Send the leader sequence and set its state */
void send_and_state(const char* const cmd, const char* const name) {
    send_str(cmd);
    set_leader_state(true, name == NULL ? cmd : name);
}

/* Handle leader sequences */
inline void handle_leader_key(void) {
    LEADER_DICTIONARY() {
        leading = false;

        SEQ_ONE_KEY(BP_AGRV) {
            send_and_state(PSTR(SS_LCTL("w")), /*PSTR("Close")*/"");
        } else SEQ_ONE_KEY(BP_A) {
            send_and_state(PSTR(SS_LCTL("a")), /*PSTR("Select all")*/"");
        } else SEQ_ONE_KEY(BP_U) {
            send_and_state(PSTR(SS_LCTL("x")), /*PSTR("Cut")*/"");
        } else SEQ_ONE_KEY(BP_I) {
            send_and_state(PSTR(SS_LCTL("c")), /*PSTR("Copy")*/"");
        } else SEQ_ONE_KEY(BP_E) {
            send_and_state(PSTR(SS_LCTL("v")), /*PSTR("Paste")*/"");
        } else SEQ_ONE_KEY(BP_P) {
            send_and_state(PSTR(SS_LCTL("z")), /*PSTR("Undo")*/"");
        } else SEQ_ONE_KEY(BP_O) {
            send_and_state(PSTR(SS_LCTL("y")), /*PSTR("Redo")*/"");
        } else SEQ_ONE_KEY(BP_T) {
            send_and_state(PSTR(SS_LCTL(SS_LSFT("t"))), /*PSTR("Last tab")*/"");
        } else SEQ_ONE_KEY(BP_H) {
            send_and_state(PSTR("https://"), NULL);
        } else SEQ_ONE_KEY(KC_G) {
            send_and_state(PSTR("/giphy "), NULL);
#ifndef NO_SECRETS
        } else SEQ_TWO_KEYS(BP_S, BP_M) {
            send_and_state(secrets[SEC_UID], /*PSTR("uid")*/"");
        } else SEQ_TWO_KEYS(BP_S, BP_K) {
            send_and_state(secrets[SEC_PRODUCT], /*PSTR("Product")*/"");
#endif
        } else {
            // Incorrect sequence
            set_leader_state(false, PSTR("Error"));
        }

        // Call leader_end at the end of the function, instead of at the start.
        // (It permits to use is_success)
        leader_end();
    }
}

/* Callback (used by core) called when the `KC_LEAD` key is tapped */
void leader_start(void) {
#ifdef RGBLIGHT_ENABLE
    rgb_display_leader(&leader_state);
#endif
}

/* Callback called when the leader sequence is processed */
void leader_end(void) {
#ifdef RGBLIGHT_ENABLE
    rgb_display_leader(&leader_state);
#endif
}

#endif // LEADER_ENABLE
