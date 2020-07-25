#include QMK_KEYBOARD_H

#include "keymap.h"
#include "layers.h"

//------------------------------
// Helpers to construct layouts
//------------------------------
#define CONCATE(id, name) id ## name

/* Assemble all the #define of a layer definition */
#define COMPOSE_LAYER(id) \
    CONCATE(id, _ROW1_LEFT) CONCATE(id, _ROW1_RIGHT) \
    CONCATE(id, _ROW2_LEFT) CONCATE(id, _ROW2_RIGHT) \
    CONCATE(id, _ROW3_LEFT) CONCATE(id, _THUMB_ROW1_LEFT) CONCATE(id, _THUMB_ROW1_RIGHT) CONCATE(id, _ROW3_RIGHT) \
    CONCATE(id, _THUMB_ROW2_LEFT) CONCATE(id, _THUMB_ROW2_RIGHT)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)


//-------------------------
// Keymaps definitions
// & layer states behavior
//-------------------------

/* Keymap definition of layers (array used by core) */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BEPO]          = LAYOUT_wrapper(COMPOSE_LAYER(BEPO)),
    [_FUNC_NUM_SYMB] = LAYOUT_wrapper(COMPOSE_LAYER(FUNC_NUM_SYMB)),
    [_NAV_MOUSE]     = LAYOUT_wrapper(COMPOSE_LAYER(NAV_MOUSE)),
    [_MEDIA_RGB]     = LAYOUT_wrapper(COMPOSE_LAYER(MEDIA_RGB)),
};
