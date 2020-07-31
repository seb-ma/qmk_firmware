#ifdef DYNAMIC_MACRO_ENABLE

#include "custom_keys.h"
#include "dynamic_macros.h"
#include "rgb.h"

/* State of the 2 available dynamic macros */
t_dyn_macros_state dyn_macros_state[] = {
    {
        .recording = false,
        .timer_played = 0,
        .timer_last_error = 0
    },
    {
        .recording = false,
        .timer_played = 0,
        .timer_last_error = 0
    },
};

/* Check if this is a macro key and process it if true
 (To be called in process_record_user)
*/
bool handle_dynamic_macro(const uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        uint8_t index = 0;
        switch (keycode) {
            case DYN_REC_START1:
                index = 0;
                break;
            case DYN_REC_START2:
                index = 1;
                break;
            default:
                return true;
        }

        // DYN_REC_START1 or DYN_REC_START2
        if (dyn_macros_state[(index + 1) % 2].recording) {
            // Error on trying to record nested macro
            dyn_macros_state[index].timer_last_error = timer_read32();
            return true;
        }
        dyn_macros_state[index].recording = true;
    }
    return true;
}


/* Callback triggered when you play back a macro
 direction indicates which macro it is, with `1` being Macro 1, `-1` being Macro 2, and 0 being no macro.
 */
void dynamic_macro_play_user(int8_t direction) {
    uint8_t index = 0;
    switch (direction) {
        case 1:
            index = 0;
            break;
        case -1:
            index = 1;
            break;
        default:
            return;
    }
    // Update state
    dyn_macros_state[index].timer_played = timer_read32();
#ifdef RGBLIGHT_ENABLE
    rgb_display_dynamic_macros(dyn_macros_state);
#endif
}

/* Triggered when you start recording a macro */
void dynamic_macro_record_start_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgb_display_dynamic_macros(dyn_macros_state);
#endif
}

/* Triggered when the macro recording is stopped
 direction indicates which macro it is, with `1` being Macro 1, `-1` being Macro 2, and 0 being no macro.
*/
void dynamic_macro_record_end_user(int8_t direction) {
    // Update state
    dyn_macros_state[0].recording = false;
    dyn_macros_state[1].recording = false;
#ifdef RGBLIGHT_ENABLE
    rgb_display_dynamic_macros(dyn_macros_state);
#endif
}

#endif // DYNAMIC_MACRO_ENABLE
