#include QMK_KEYBOARD_H
#include "eeprom.h"

#include "eeprom_user.h"
#include "hid.h"
#include "keymap.h"
#include "layers.h"
#include "leader.h"
#include "oled.h"
#include "rgb.h"
#include "transport_user.h"


/* Callback (used by core) called early during startup */
void keyboard_pre_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    debug_matrix = true;
    debug_keyboard = true;
    debug_mouse = true;
#endif
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();

    // Data that can be sent to follower
    user_data_m2s.oled2 = user_config.oled2;
    user_data_m2s.animation_idx = user_config.animation_idx;
    user_data_m2s.anim_reinit_toggle = 0;
    user_data_m2s.pomodoro_reinit_toggle = 0;
}

/* Callback (used by core) called after firmware has initialized */
void keyboard_post_init_user(void) {
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS)
    // Enable the LED layers
    rgblight_layers = rgblight_layers_user;
#endif
}

/* Callback (used by core) called every time the layer changes */
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _FUNC_NUM_SYMB, _NAV_MOUSE, _MEDIA_RGB);
#ifdef RAW_ENABLE
    send_hid_status(state);
#endif
#ifdef RGBLIGHT_ENABLE
    rgb_display_layer(state);
#endif
    return state;
}

/* Callback (called by core) when the state of one of those 5 LEDs changes:
  Num Lock, Caps Lock, Scroll Lock, Compose, Kana
*/
bool led_update_user(led_t state) {
#ifdef RAW_ENABLE
    send_hid_status(layer_state);
#endif
#ifdef RGBLIGHT_ENABLE
    return rgb_display_leds(state);
#else
    return true;
#endif
}

/* Callback (used by core) called at every matrix scan
 which is basically as often as the MCU can handle
*/
void matrix_scan_user(void) {
#ifdef LEADER_ENABLE
    handle_leader_key();
#endif
}
