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
#ifdef ENCODER_ENABLE
#ifndef FOLLOWER_ONLY

#include QMK_KEYBOARD_H

#include "custom_keys.h"
#include "layers.h"

/* Callback (used by core) of encoders behavior implementation */
void encoder_update_user(uint8_t index, bool clockwise) {
#ifdef EXTRAKEY_ENABLE
    if (layer_state_is(_MEDIA_RGB)) {
        if (index == 0) { // First encoder
            // Volume Up / Down
            tap_code((clockwise) ? KC_AUDIO_VOL_UP : KC_AUDIO_VOL_DOWN);
        } else { // Second encoder
            // Track Next / Previous
            tap_code((clockwise) ? KC_MEDIA_NEXT_TRACK : KC_MEDIA_PREV_TRACK);
        }
        // Do not continue
        return;
    }
#endif // EXTRAKEY_ENABLE
    // All others layers
    if (index == 0) { // First encoder
        // Scroll Down  ; Page Scroll Down
        // Scroll Up    ; Page Scroll Up
        tap_code16(interpret_keycode(clockwise ? C_ENC1_CW : C_ENC1_RCW));
    } else { // Second encoder
        // Right ; End
        // Left  ; Home
        tap_code16(interpret_keycode(clockwise ? C_ENC2_CW : C_ENC2_RCW));
    }
}

#endif // FOLLOWER_ONLY
#endif // ENCODER_ENABLE
