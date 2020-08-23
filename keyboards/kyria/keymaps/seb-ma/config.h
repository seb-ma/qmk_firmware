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

//-----------------------------
// Only-hardware configuration
//-----------------------------

#ifdef OLED_DRIVER_ENABLE
#   define OLED_DISPLAY_128X64
#endif

// If you are using an Elite C rev3 on the follower side, uncomment the lines below:
#define SPLIT_USB_DETECT
#define NO_USB_STARTUP_CHECK

#define ENCODER_DIRECTION_FLIP
// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 2

// Allows to use either side as the master. Look at the documentation for info:
// https://docs.qmk.fm/#/config_options?id=setting-handedness
// Need to flash eeprom-lefthand.eep/eeprom-righthand.eep to each half
#define EE_HANDS // Handedness by EEPROM

// RGB
#ifdef RGBLIGHT_ENABLE
    // This option enables synchronization of the RGB Light modes between the controllers of the split keyboard.
#   define RGBLIGHT_SPLIT
#endif

//----------------------------
// QMK features configuration
// Overriding/Complement to config.h from user directory
//----------------------------

// RGB
#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_LIMIT_VAL      200 // The maximum brightness level (255 is too high for the keyboard)

    // Define LEDs order for fluid animations
//#   define RGBLIGHT_LED_MAP {0, 1, 2, 9, 8, 7, 4, 3, 5, 6, 19, 18, 17, 10, 11, 12, 15, 16, 14, 13} // Orients LEDs to a circle around both halves.
//#   define RBGLIGHT_LED_MAP {9, 8, 6, 7, 5, 3, 2, 4, 1, 0, 10, 12, 13, 11, 14, 16, 17, 15, 18, 19} // Orients LEDs for a left half-right half columnar progression.

#   undef RGBLIGHT_ANIMATIONS     // Disable all additional animation modes - use selective define RGBLIGHT_EFFECT_xxxx to reduce space used

#   ifndef HALVE_BOTH_LIGHT
//#       define RGBLIGHT_EFFECT_ALTERNATING
//#       define RGBLIGHT_EFFECT_BREATHING
//#       define RGBLIGHT_EFFECT_CHRISTMAS
//#       define RGBLIGHT_EFFECT_KNIGHT
//#       define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#       define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#       define RGBLIGHT_EFFECT_SNAKE
//#       define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#       define RGBLIGHT_EFFECT_TWINKLE
//#       define RGBLIGHT_EFFECT_RGB_TEST
#   endif

#endif // RGBLIGHT_ENABLE
