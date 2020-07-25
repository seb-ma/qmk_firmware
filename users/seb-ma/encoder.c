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
            tap_code16((clockwise) ? KC_AUDIO_VOL_DOWN : KC_AUDIO_VOL_UP);
        } else { // Second encoder
            // Track Next / Previous
            tap_code16((clockwise) ? KC_MEDIA_NEXT_TRACK : KC_MEDIA_PREV_TRACK);
        }
        // Do not continue
        return;
    }
#endif // EXTRAKEY_ENABLE
    // All others layers
    if (index == 0) { // First encoder
        // Down  ; Scroll Down
        // Up    ; Scroll Up
        tap_code16(interpret_keycode(clockwise ? C_ENC1_CW : C_ENC1_RCW));
    } else { // Second encoder
        // Right ; End
        // Left  ; Home
        tap_code16(interpret_keycode(clockwise ? C_ENC2_CW : C_ENC2_RCW));
    }
}

#endif // FOLLOWER_ONLY
#endif // ENCODER_ENABLE
