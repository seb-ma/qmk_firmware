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
#include QMK_KEYBOARD_H

/* Custom keycodes declarations
unless explicitly specified in comments, behavior of keys is implemented in process_record_user */
enum user_keycodes {
    C_DUMMY = SAFE_RANGE,  // To use as a not special user key - nothing to do or let QMK handle it

    C_COMMA_DOT,           // Comma and dot in numbers layer
#ifdef USER_CLOSE_CHAR
    C_CLOSE_CHAR,          // Close last opening char
    C_CLOSE_CHAR_CLEAR,    // Close lasts opening chars
#endif
#ifdef ENCODER_ENABLE
    C_ENC1_CW,             // Down  ; Scroll Down
    C_ENC1_RCW,            // Up    ; Scroll Up
    C_ENC2_CW,             // Right ; End
    C_ENC2_RCW,            // Left  ; Home
#endif
#ifdef RGBLIGHT_ENABLE
    C_RGB_TOGGLE,          // Toggle RGB without writting in eeprom
    C_RGB_SAVE_EEPROM,     // Toggle RGB with writting in eeprom
#endif
#ifdef OLED_DRIVER_ENABLE
#   ifdef TRANSPORT_USER_DATA
    C_OLED2_TOGGLE,                 // Toggle OLED follower without writting in eeprom
    C_OLED2_STORE_EEPROM,           // Store OLED follower with in eeprom
    C_OLED2_REINIT,                 // Reinitialize animation of OLED follower
    C_OLED2_ANIMATION_CYCLE,        // Cycle throw available animations without writting in eeprom
    C_OLED2_ANIMATION_STORE_EEPROM, // Store current animation in eeprom
#   endif // TRANSPORT_USER_DATA
#   ifdef POMODORO_TIMER
    C_POMODORO_TOGGLE,     // Start a pomodoro timer
#   endif
#endif // OLED_DRIVER_ENABLE
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    C_TOGGLE_UNICODE,      // Toggle usage of unicode
#endif
};

// Define XXXXXXX for keys that are associated to unavailable features
#ifndef USER_CLOSE_CHAR
#   define C_CLOSE_CHAR          XXXXXXX
#   define C_CLOSE_CHAR_CLEAR    XXXXXXX
#endif
#ifndef ENCODER_ENABLE
#   define C_ENC1_CW             XXXXXXX
#   define C_ENC1_RCW            XXXXXXX
#   define C_ENC2_CW             XXXXXXX
#   define C_ENC2_RCW            XXXXXXX
#endif
#ifndef RGBLIGHT_ENABLE
#   define C_RGB_TOGGLE          XXXXXXX
#   define C_RGB_TOGGLE_EEPROM   XXXXXXX
#endif
#if !(defined(OLED_DRIVER_ENABLE) && defined(TRANSPORT_USER_DATA))
#   define C_OLED2_TOGGLE        XXXXXXX
#   define C_OLED2_STORE_EEPROM  XXXXXXX
#   define C_OLED2_REINIT        XXXXXXX
#   define C_OLED2_ANIMATION_CYCLE        XXXXXXX
#   define C_OLED2_ANIMATION_STORE_EEPROM XXXXXXX
#endif
#if !defined(POMODORO_TIMER)
#   define C_POMODORO_TOGGLE     XXXXXXX
#endif
#if !(defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE))
#   define C_TOGGLE_UNICODE      XXXXXXX
#   define UNICODE_MODE_FORWARD  XXXXXXX
#   define UNICODE_MODE_REVERSE  XXXXXXX
#   define UNICODE_MODE_MAC      XXXXXXX
#   define UNICODE_MODE_LNX      XXXXXXX
#   define UNICODE_MODE_WIN      XXXXXXX
#   define UNICODE_MODE_BSD      XXXXXXX
#   define UNICODE_MODE_WINC     XXXXXXX
#endif // !(defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE))
#ifndef UNICODE_ENABLE
#   define UC(k)                 XXXXXXX
#endif
#ifndef UNICODEMAP_ENABLE
#   define X(i)                  XXXXXXX
#   define XP(i, j)              XXXXXXX
#endif

#ifndef FOLLOWER_ONLY
/* Structure of keycode and alternative keycode if shift and/or altgr mod */
typedef struct {
    const uint16_t keycode;
    const uint16_t key;
    const uint16_t key_shift;
    const uint16_t key_altgr;
    const uint16_t key_shift_altgr;
} key_mod_full_map_t;

/* Number of char that was sent last time */
extern uint8_t nb_char_sent;

/* Interpret keycode according to modifiers (based on key_alter_map and key_mod_full_map) */
uint16_t interpret_keycode(const uint16_t keycode);

/* Interpret keycode as unicode (in best effort: search direct keycode, then search in all mods variations) */
uint16_t interpret_keycode_unicode(const uint16_t keycode);

/* Tap char according to unicode activation or not */
void tap_char_u(const uint16_t keycode);

/* Tap non breakable space according to unicode activation or not */
void tap_nbsp_u(void);

/* Send a PROGMEM string on unicode string according to Unicode activation */
void send_str(const char* str);

/* Get the keycode with the mods applied */
uint16_t get_keycode_with_mods_applied(const uint16_t keycode);

#endif // FOLLOWER_ONLY
