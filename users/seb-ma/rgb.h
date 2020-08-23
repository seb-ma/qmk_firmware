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
#pragma once
#ifdef RGBLIGHT_ENABLE
#include QMK_KEYBOARD_H

#include "dynamic_macros.h"
#include "leader.h"

#ifdef RGBLIGHT_LAYERS

/* List of layers by index
 (must be declared in the same order when initializing rgblight_layers_user)
*/
enum layer_index {
    IDX_LAYER_RGB_BASE = 0,
    IDX_LAYER_RGB_NUM_SYMB,
    IDX_LAYER_RGB_NAV_MOUSE,
    IDX_LAYER_RGB_SHORTCUTS,
    IDX_LAYER_RGB_MEDIA_RGB,
    IDX_LAYER_RGB_MACRO_RECORD,
    IDX_LAYER_RGB_LEADER,
    IDX_LAYER_RGB_CAPSLOCK,

    IDX_LAYER_SIZE
};

_Static_assert(IDX_LAYER_SIZE == RGBLIGHT_MAX_LAYERS, "RGBLIGHT_MAX_LAYERS has incorrect value regarding layer_index declaration");

/* Definition of RGB layers: specific to each keyboard */
extern const rgblight_segment_t LAYER_RGB_BASE[] PROGMEM;
extern const rgblight_segment_t LAYER_RGB_NUM_SYMB[] PROGMEM;
extern const rgblight_segment_t LAYER_RGB_NAV_MOUSE[] PROGMEM;
extern const rgblight_segment_t LAYER_RGB_SHORTCUTS[] PROGMEM;
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
    LAYER_RGB_SHORTCUTS,
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
