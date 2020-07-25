#ifdef RGBLIGHT_ENABLE

#include "custom_keys.h"
#include "dynamic_macros.h"
#include "layers.h"
#include "leader.h"
#include "rgb.h"

/*
https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgblight.md

Physical leds position (xx) related to keys
Master and follower may be inverted (right / left), 0-10 are always on master, 11-20 on follower

//
//                                         Master                                                             Follower
//
//              1       2       3       4       5       6                                             1       2       3       4       5       6
//                          ┌───────┬──────(05)─────┬───────┐                                     ┌───────┬─────(15)──────┬───────┐
//          ┌──(10)─┬─(06)──┤       │       │       │       │                                     │       │       │       │       ├──(20)─┬─(16)──┐
//          │       │       │       │       │       │       │                                     │       │       │       │       │       │       │
//    Row 1 │       │       │       │       │       │       │                                     │       │       │       │       │       │       │
//          │       │       ├───────┼───────┼───────┼──(04)─┤                                     ├─(14)──┼───────┼───────┼───────┤       │       │
//          ├───────┼───────┤       │       │       │       │                                     │       │       │       │       ├───────┼───────┤
//          │       │       │       │       │       │       │                                     │       │       │       │       │       │       │
//    Row 2 │       │       │       │       │       │       │                                     │       │       │       │       │       │       │
//          │       │       ├───────┼───────┼───────┼───────┤    1      2            1      2     ├───────┼───────┼───────┼───────┤       │       │
//          ├──(09)─┼──(07)─┤       │       │       │       │┌───────┬───────┐   ┌───────┬───────┐│       │       │       │       ├──(19)─┼─(17)──┤
//          │       │       │       │       │       │       ││      (01)     │   │     (11)      ││       │       │       │       │       │       │
//    Row 3 │       │       │       │       │       │       ││       │       │   │       │       ││       │       │       │       │       │       │
//          │       │       ├───────┴───────┴───────┴───────┘│       │       │   │       │       │└───────┴───────┴───────┴───────┤       │       │
//          └───────┴───────┘    ┌(08)───┬───(03)┬────(02)───┴───┬───┴───┬───┘   └───┬───┴───┬───┴───(12)────┬(13)───┬───(18)┐    └───────┴───────┘
//                               │       │       │       │       │       │           │       │       │       │       │       │
//                   Thumb row 2 │       │       │       │       │       │           │       │       │       │       │       │
//                               │       │       │       │       │       │           │       │       │       │       │       │
//                               └───────┴───────┴───────┴───────┴───────┘           └───────┴───────┴───────┴───────┴───────┘
//                                   1       2       3       4       5                  1       2       3       4       5
//
*/

/* Indicates if layers must be enabled */
static bool rgb_layer_change = true;

/* Check if this is a custom rgb key and process it if true
 (To be called in process_record_user)
*/
bool handle_rgb(const uint16_t keycode, keyrecord_t *const record) {
    if (record->event.pressed) {
        switch (keycode) {
        case C_RGB_TOGGLE:
            rgblight_toggle_noeeprom();
            // Reactivate layers
            rgb_layer_change = true;
            return false;
        case RGB_TOG:
            // Reactivate layers
            rgb_layer_change = true;
            break;
        case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT:
            // Deactivate layers
            rgb_layer_change = false;
            break;
        }
    }
    return true;
}

/* If RGB layers are not activated, this implementation only manages layout layers. */

#ifdef RGBLIGHT_LAYERS

/* List of layers by index
 (must be declared in the same order when initializing rgblight_layers_user)
*/
enum layer_index {
    IDX_LAYER_RGB_BASE = 0,
    IDX_LAYER_RGB_NUM_SYMB,
    IDX_LAYER_RGB_NAV_MOUSE,
    IDX_LAYER_RGB_MEDIA_RGB,
    IDX_LAYER_RGB_MACRO_RECORD,
    IDX_LAYER_RGB_MACRO_PLAY,
    IDX_LAYER_RGB_LEADER,
    IDX_LAYER_RGB_CAPSLOCK,

    IDX_LAYER_SIZE
};

_Static_assert(IDX_LAYER_SIZE == RGBLIGHT_MAX_LAYERS, "RGBLIGHT_MAX_LAYERS has incorrect value regarding layer_index declaration");

#endif // RGBLIGHT_LAYERS

/* Render status of layer */
void rgb_display_layer(const layer_state_t state) {
    if (rgb_layer_change) {
#ifdef RGBLIGHT_LAYERS
        // All rgb layers will light up related to active keycode layers
        rgblight_set_layer_state(IDX_LAYER_RGB_BASE,      layer_state_cmp(state, _BEPO));
        rgblight_set_layer_state(IDX_LAYER_RGB_NUM_SYMB,  layer_state_cmp(state, _FUNC_NUM_SYMB));
        rgblight_set_layer_state(IDX_LAYER_RGB_NAV_MOUSE, layer_state_cmp(state, _NAV_MOUSE));
        rgblight_set_layer_state(IDX_LAYER_RGB_MEDIA_RGB, layer_state_cmp(state, _MEDIA_RGB));
#else // RGBLIGHT_LAYERS
        if (layer_state_cmp(state, _MEDIA_RGB)) {
            rgblight_sethsv_range(HSV_PURPLE, 0, RGBLED_NUM);
        } else if (layer_state_cmp(state, _NAV_MOUSE)) {
            rgblight_sethsv_range(HSV_BLUE, 0, RGBLED_NUM);
        } else if (layer_state_cmp(state, _FUNC_NUM_SYMB)) {
            rgblight_sethsv_range(HSV_ORANGE, 0, RGBLED_NUM);
        } else if (layer_state_cmp(state, _BEPO)) {
            rgblight_sethsv_range(HSV_RED, 0, RGBLED_NUM);
        }
#endif // RGBLIGHT_LAYERS
    }
}

#ifdef DYNAMIC_MACRO_ENABLE
/* Render status of dynamic macros */
void rgb_display_dynamic_macros(const t_dyn_macros_state dyn_macros_state[]) {
#   ifdef RGBLIGHT_LAYERS
    // Activate/deactivate macro recording layer according to status
    rgblight_set_layer_state(IDX_LAYER_RGB_MACRO_RECORD, (dyn_macros_state[0].recording || dyn_macros_state[1].recording));
#       ifdef RGBLIGHT_LAYER_BLINK
    // If a macro has been played, blink
    if (timer_elapsed32(dyn_macros_state[0].timer_last_error) < DYNMACRO_STATE_DISPLAY_DURATION
     || timer_elapsed32(dyn_macros_state[1].timer_last_error) < DYNMACRO_STATE_DISPLAY_DURATION) {
        rgblight_blink_layer(IDX_LAYER_RGB_MACRO_PLAY, DYNMACRO_STATE_DISPLAY_DURATION);
    }
#       endif // RGBLIGHT_LAYER_BLINK
#   endif // RGBLIGHT_LAYERS
}
#endif // DYNAMIC_MACRO_ENABLE

#ifdef LEADER_ENABLE
/* Render status of leader sequences */
void rgb_display_leader(const t_leader_state* const leader_state) {
#   ifdef RGBLIGHT_LAYERS
    // Invert layer state
    rgblight_set_layer_state(IDX_LAYER_RGB_LEADER, !rgblight_get_layer_state(IDX_LAYER_RGB_LEADER));
#   endif
}
#endif // LEADER_ENABLE

/* Render status of leds */
bool rgb_display_leds(const led_t led_state) {
#ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(IDX_LAYER_RGB_CAPSLOCK,   led_state.caps_lock);
    //rgblight_set_layer_state(IDX_LAYER_RGB_NUMLOCK,    led_state.num_lock);
    //rgblight_set_layer_state(IDX_LAYER_RGB_SCROLLLOCK, led_state.scroll_lock);
    //rgblight_set_layer_state(IDX_LAYER_RGB_COMPOSE,    led_state.compose);
    //rgblight_set_layer_state(IDX_LAYER_RGB_KANA,       led_state.kana);
#endif
    return true;
}

#endif // RGBLIGHT_ENABLE
