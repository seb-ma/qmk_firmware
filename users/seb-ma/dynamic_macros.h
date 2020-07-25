#pragma once
#ifdef DYNAMIC_MACRO_ENABLE
#include QMK_KEYBOARD_H

/* Check if this is a macro key and process it if true
 (To be called in process_record_user)
*/
bool handle_dynamic_macro(const uint16_t keycode, keyrecord_t* record);

/* Definition of a macro state */
typedef struct {
    bool     recording;        // Is currently recording
    uint32_t timer_played;     // Last playing time
    uint32_t timer_last_error; // Last error time
} t_dyn_macros_state;

/* State of the 2 available dynamic macros */
extern t_dyn_macros_state dyn_macros_state[];

#endif // DYNAMIC_MACRO_ENABLE
