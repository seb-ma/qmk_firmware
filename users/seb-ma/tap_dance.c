#ifdef TAP_DANCE_ENABLE
#include QMK_KEYBOARD_H
#include "keymap_bepo.h"

#include "tap_dance.h"

#ifdef MOUSEKEY_ENABLE
/* Tap Dance to change mouse acceleration */
void dance_msaccel(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_MS_ACCEL0);
    } else if (state->count == 2) {
        tap_code16(KC_MS_ACCEL1);
    } else { // 3 or more
        tap_code16(KC_MS_ACCEL2);
    }
}
#endif // MOUSEKEY_ENABLE

/* Tap Dance definitions (array used by core) */
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_COMM_QUOTE]   = ACTION_TAP_DANCE_DOUBLE(BP_COMM, BP_QUOT),
    [TD_GUIS]         = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_APP),
#ifdef MOUSEKEY_ENABLE
    [TD_MS_BTNS]      = ACTION_TAP_DANCE_DOUBLE(KC_MS_BTN1, KC_MS_BTN2),
    [TD_MS_ACCEL]     = ACTION_TAP_DANCE_FN(dance_msaccel),
#endif
};

#endif // TAP_DANCE_ENABLE
