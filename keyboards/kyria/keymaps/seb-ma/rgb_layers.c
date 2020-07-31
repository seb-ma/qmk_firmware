#ifdef RGBLIGHT_LAYERS
#include QMK_KEYBOARD_H
#include "rgb.h"

/* Definition of RGB layers */
const rgblight_segment_t LAYER_RGB_BASE[] PROGMEM = RGBLIGHT_LAYER_SEGMENTS(
    { 0, RGBLED_NUM, HSV_RED}
);
const rgblight_segment_t LAYER_RGB_NUM_SYMB[] PROGMEM = RGBLIGHT_LAYER_SEGMENTS(
    { 0, RGBLED_NUM, HSV_BLUE}
);
const rgblight_segment_t LAYER_RGB_NAV_MOUSE[] PROGMEM = RGBLIGHT_LAYER_SEGMENTS(
    { 0, RGBLED_NUM, HSV_SPRINGGREEN}
);
const rgblight_segment_t LAYER_RGB_MEDIA_RGB[] PROGMEM = RGBLIGHT_LAYER_SEGMENTS(
    { 0, RGBLED_NUM, HSV_PURPLE}
);
const rgblight_segment_t LAYER_RGB_MACRO_RECORD[] PROGMEM = RGBLIGHT_LAYER_SEGMENTS(
    { 8, 2, HSV_YELLOW},
    {18, 2, HSV_YELLOW}
);
const rgblight_segment_t LAYER_RGB_LEADER[] PROGMEM = RGBLIGHT_LAYER_SEGMENTS(
    { 9, 1, HSV_GREEN},
    {19, 1, HSV_GREEN}
);
const rgblight_segment_t LAYER_RGB_CAPSLOCK[] PROGMEM = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 1, HSV_AZURE},
    {10, 1, HSV_AZURE}
);

#endif // RGBLIGHT_LAYERS
