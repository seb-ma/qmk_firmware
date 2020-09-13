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
#include "keymap_bepo.h"

#include "custom_keys.h"
#include "eeprom_user.h"
#include "leader.h"
#include "oled.h"
#include "rgb.h"

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#   include "secrets.h" // file may not exist
#endif


LEADER_EXTERNS();

/* State of leader sequence */
t_leader_state leader_state = {.is_success = false, .timer = 0};

/* Set the state of the leader sequence */
void set_leader_state(bool is_success) {
    leader_state.is_success = is_success;
    leader_state.timer = timer_read();
}

/* Send the leader sequence and set its state */
void send_and_state(const char* const cmd) {
    send_str(cmd);
    set_leader_state(true);
}

/* Handle leader sequences */
inline void handle_leader_key(void) {
    LEADER_DICTIONARY() {
        leading = false;

        /* Git */
        SEQ_TWO_KEYS(BP_G, BP_A) {
            send_and_state(PSTR("git add ."));
        } else SEQ_TWO_KEYS(BP_G, BP_C) {
            send_and_state(PSTR("git commit -m ''"));
            tap_char_u(KC_LEFT);
        } else SEQ_THREE_KEYS(BP_G, BP_C, BP_A) {
            send_and_state(PSTR("git commit --amend"));
        } else SEQ_TWO_KEYS(BP_G, BP_D) {
            send_and_state(PSTR("git diff --staged"));
        } else SEQ_TWO_KEYS(BP_G, BP_F) {
            send_and_state(PSTR("git fetch"));
        } else SEQ_TWO_KEYS(BP_G, BP_L) {
            send_and_state(PSTR("git log"));
        } else SEQ_THREE_KEYS(BP_G, BP_L, BP_O) {
            send_and_state(PSTR("git log --oneline"));
        } else SEQ_TWO_KEYS(BP_G, BP_O) {
            send_and_state(PSTR("git checkout"));
        } else SEQ_TWO_KEYS(BP_G, BP_P) {
            send_and_state(PSTR("git pull"));
        } else SEQ_TWO_KEYS(BP_G, BP_S) {
            send_and_state(PSTR("git status"));

        /* Others */
#ifndef NO_SECRETS
        } else SEQ_TWO_KEYS(BP_S, BP_M) {
            send_and_state(secrets[SEC_UID]);
        } else SEQ_TWO_KEYS(BP_S, BP_K) {
            send_and_state(secrets[SEC_PRODUCT]);
#endif
        } else {
            // Incorrect sequence
            set_leader_state(false);
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
