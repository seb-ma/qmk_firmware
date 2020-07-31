#pragma once
#ifdef RGBLIGHT_ENABLE
#include QMK_KEYBOARD_H

#include "dynamic_macros.h"
#include "leader.h"

#ifdef RGBLIGHT_LAYERS
/* Definition of RGB layers: specific to each keyboard */
extern const rgblight_segment_t LAYER_RGB_BASE[] PROGMEM;
extern const rgblight_segment_t LAYER_RGB_NUM_SYMB[] PROGMEM;
extern const rgblight_segment_t LAYER_RGB_NAV_MOUSE[] PROGMEM;
extern const rgblight_segment_t LAYER_RGB_MEDIA_RGB[] PROGMEM;
extern const rgblight_segment_t LAYER_RGB_MACRO_RECORD[] PROGMEM;
extern const rgblight_segment_t LAYER_RGB_LEADER[] PROGMEM;
extern const rgblight_segment_t LAYER_RGB_CAPSLOCK[] PROGMEM;

/* Definion of layers (later layers take precedence)
 Correlate define of RGBLIGHT_MAX_LAYERS (in config.h) when adding a rgb layer
*/
static const rgblight_segment_t* const rgblight_layers_user[RGBLIGHT_MAX_LAYERS + 1] PROGMEM = RGBLIGHT_LAYERS_LIST(
    LAYER_RGB_BASE,
    LAYER_RGB_NUM_SYMB,
    LAYER_RGB_NAV_MOUSE,
    LAYER_RGB_MEDIA_RGB,
    LAYER_RGB_MACRO_RECORD,
    LAYER_RGB_LEADER,
    LAYER_RGB_CAPSLOCK
    // Update RGBLIGHT_MAX_LAYERS in config.h according to number of layers
);
#endif // RGBLIGHT_LAYERS

/* Check if this is a custom rgb key and process it if true
 (To be called in process_record_user)
*/
bool handle_rgb(const uint16_t keycode, keyrecord_t *const record);

/* Render status of layer */
void rgb_display_layer(const layer_state_t state);

#ifdef DYNAMIC_MACRO_ENABLE
/* Render status of dynamic macros */
void rgb_display_dynamic_macros(const t_dyn_macros_state dyn_macros_state[]);
#endif

#ifdef LEADER_ENABLE
/* Render status of leader sequences */
void rgb_display_leader(const t_leader_state* const leader_state);
#endif

/* Render status of leds */
bool rgb_display_leds(const led_t led_state);

#endif // RGBLIGHT_ENABLE
