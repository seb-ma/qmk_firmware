#pragma once
#include QMK_KEYBOARD_H

/* Custom keycodes declarations
unless explicitly specified in comments, behavior of keys is implemented in process_record_user */
enum user_keycodes {
    C_DUMMY = SAFE_RANGE,  // To use as a not special user key - nothing to do or let QMK handle it

    C_COMM_QUOT,           // (bépo adaptation) Comma and simple apostrophe in bépo layer
    C_RSQU_QUES,           // (bépo adaptation) French apostrophe and question mark in bépo layer

    C_COMMA_DOT,           // Comma and dot in numbers layer
#ifdef DYNAMIC_MACRO_ENABLE
    C_DYN_MACRO1,          // Play DynMacro 1 ; Record/Stop DynMacro 1
    C_DYN_MACRO2,          // Play DynMacro 2 ; Record/Stop DynMacro 2
#endif
#ifdef USER_CLOSE_CHAR
    C_CLOSE_CHAR,          // Close last opening char
    C_CLOSE_CHAR_CLEAR,    // Close lasts opening chars
#endif
#ifdef USER_ADDING_NBSP
    C_TAB_NBSP,            // Tab on tap and Add nbsp on holding
#endif
#ifdef ENCODER_ENABLE
    C_ENC1_CW,             // Down  ; Scroll Down
    C_ENC1_RCW,            // Up    ; Scroll Up
    C_ENC2_CW,             // Right ; End
    C_ENC2_RCW,            // Left  ; Home
#endif
#ifdef MOUSEKEY_ENABLE
    C_MS_ACCEL,            // KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2
#endif
#ifdef RGBLIGHT_ENABLE
    C_RGB_TOGGLE,          // Toggle RGB without writting in eeprom
    C_RGB_SAVE_EEPROM,     // Toggle RGB with writting in eeprom
#endif
#ifdef OLED_DRIVER_ENABLE
#   ifdef TRANSPORT_USER_DATA
    C_OLED2_TOGGLE,        // Toggle OLED follower without writting in eeprom
    C_OLED2_STORE_EEPROM,  // Store OLED follower with in eeprom
    C_OLED2_REINIT,        // Reinitialize animation of OLED follower
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
#ifndef USER_ADDING_NBSP
#   define C_TAB_NBSP            KC_TAB
#endif

#ifndef DYNAMIC_MACRO_ENABLE
#   define C_DYN_MACRO1          XXXXXXX
#   define C_DYN_MACRO2          XXXXXXX
#endif
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
#ifndef MOUSEKEY_ENABLE
#   define C_MS_BTNS             XXXXXXX
#   define C_MS_ACCEL            XXXXXXX
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

/* Interpret keycode according to modifiers (based on key_alter_map and key_mod_full_map) */
uint16_t interpret_keycode(const uint16_t keycode);

/* Interpret keycode as unicode (in best effort: search direct keycode, then search in all mods variations) */
uint16_t interpret_keycode_unicode(const uint16_t keycode);

/* Send a PROGMEM string on unicode string according to Unicode activation */
void send_str(const char* str);

/* Get the keycode with the mods applied */
uint16_t get_keycode_with_mods_applied(const uint16_t keycode);

#endif // FOLLOWER_ONLY
