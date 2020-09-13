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
#ifndef FOLLOWER_ONLY

#include <string.h>

#include "keymap_bepo.h"
#include "keymap_french.h"
#include "sendstring_bepo.h"

#include "custom_keys.h"
#include "dynamic_macros.h"
#include "eeprom_user.h"
#include "oled.h"
#include "rgb.h"
#include "unicode_keys.h"
#include "user_feature_closechar.h"

/* Structure of keycode and alternative keycode if mod */
typedef struct {
    const uint16_t keycode;
    const uint16_t key_alter;
} key_alter_map_t;

/* Map of keys interpreted according to AltGr mod - if AltGr -> get key_alter, else get keycode */
const key_alter_map_t key_mod_altgr_map[] PROGMEM = {
    {KC_ESC,  KC_CAPSLOCK},
    {KC_F1,   KC_F11},
    {KC_F2,   KC_F12},
    {KC_F3,   KC_F13},
    {KC_F4,   BP_LCBR},
    {KC_F5,   BP_RCBR},
    {KC_F6,   BP_DCIR},
    {KC_F7,   BP_CARN},
    {KC_F8,   BP_BSLS},
    {KC_F9,   BP_SLSH},
#ifdef OLED_DRIVER_ENABLE
    {C_OLED2_TOGGLE,     C_OLED2_STORE_EEPROM},
    {C_OLED2_ANIM_CYCLE, C_OLED2_ANIM_STORE_EEPROM},
#endif
#ifdef RGBLIGHT_ENABLE
    {C_RGB_TOGGLE, RGB_TOG},
#endif
#ifdef USER_CLOSE_CHAR
    {C_CLOSE_CHAR, C_CLOSE_CHAR_CLEAR},
#endif
};

// Simple macro concatenation
#define CONCATE(A, B) A ## B
// Macro to create list of: Ctrl(KM1), Shift Ctrl(KM1), Ctrl(KM2), Shift Ctrl(KM2)
#define SHORTCUTS_KEYMAP(KM1, KM2, X) C(CONCATE(KM1, X)), S(C(CONCATE(KM1, X))), C(CONCATE(KM2, X)), S(C(CONCATE(KM2, X)))
// Macro to create list based on bépo and fr
#define SHORTCUTS_BP_FR(X) SHORTCUTS_KEYMAP(BP_, FR_, X)

/* Map of keys interpreted according to mods
 if shift+altgr -> get key_shift_altgr
 else if altgr  -> get key_altgr
 else if shift  -> get key_shift
 else get key
*/
const key_mod_full_map_t key_mod_full_map[] PROGMEM = {
    //keycode,    key,      key_shift,   key_altgr, key_shift_altgr
    {BP_COMM,     BP_COMM,  S(BP_COMM),  BP_QUOT,   S(ALGR(BP_COMM))}, // , ; '
    {BP_RSQU,     BP_RSQU,  S(BP_QUOT),  BP_IQUE,   S(ALGR(BP_QUOT))}, // ’ ? ¿

    {C_COMMA_DOT, BP_COMM,  S(BP_COMM),  BP_DOT,    S(BP_DOT)},  // , ; . :
    {BP_C,        BP_C,     S(BP_C),     BP_CCED,   S(BP_CCED)}, // c C ç Ç

#ifdef ENCODER_ENABLE
#   ifdef EXTRAKEY_ENABLE
    {C_ENC1_CW,  KC_MS_WH_DOWN, S(KC_MS_WH_DOWN), KC_PGDOWN, S(KC_PGDOWN)},
    {C_ENC1_RCW, KC_MS_WH_UP,   S(KC_MS_WH_UP),   KC_PGUP,   S(KC_PGUP)},
#   else // EXTRAKEY_ENABLE
    {C_ENC1_CW,  KC_PGDOWN, S(KC_PGDOWN), KC_DOWN,       S(KC_DOWN)},
    {C_ENC1_RCW, KC_PGUP,   S(KC_PGUP),   KC_UP,         S(KC_UP)},
#   endif // EXTRAKEY_ENABLE
    {C_ENC2_CW,  KC_RIGHT,  S(KC_RIGHT),  KC_END,        S(KC_END)},
    {C_ENC2_RCW, KC_LEFT,   S(KC_LEFT),   KC_HOME,       S(KC_HOME)},
#endif // ENCODER_ENABLE

    {C_SC_NEW_TAB,    SHORTCUTS_BP_FR(T)},
    {C_SC_UNDO,       SHORTCUTS_BP_FR(Z)},
    {C_SC_REDO,       SHORTCUTS_BP_FR(Y)},
    {C_SC_CUT,        SHORTCUTS_BP_FR(X)},
    {C_SC_COPY,       SHORTCUTS_BP_FR(C)},
    {C_SC_PASTE,      SHORTCUTS_BP_FR(V)},
    {C_SC_SELECT_ALL, SHORTCUTS_BP_FR(A)},
    {C_SC_CLOSE,      SHORTCUTS_BP_FR(W)},
    {C_SC_REPLACE,    SHORTCUTS_BP_FR(H)},
    {C_SC_FIND,       SHORTCUTS_BP_FR(F)},
};

/* Get a related keycode according to pressed modifiers
 only unregister mods if pressed
 if a keycode is C_DUMMY: ignore it - use keycode instead
*/
uint16_t get_keycode_according_mods(const uint16_t keycode, const uint16_t keycode_shift, const uint16_t keycode_altgr, const uint16_t keycode_altgr_shift) {
    if (get_mods() & MOD_BIT(KC_RALT)) {
        if (get_mods() & MOD_MASK_SHIFT) {
            if (keycode_altgr_shift != C_DUMMY) {
                return keycode_altgr_shift;
            }
        } else if (keycode_altgr != C_DUMMY) {
            return keycode_altgr;
        }
    } else if (get_mods() & MOD_MASK_SHIFT && keycode_shift != C_DUMMY) {
        return keycode_shift;
    }
    return keycode;
}

/* Interpret keycode according to modifiers (based on the map in parameter) */
uint16_t interpret_keycode_in_map(const key_mod_full_map_t map[], int16_t map_size, const uint16_t keycode) {
    // Identify custom key according to modifiers
    for (uint8_t i = 0; i < map_size / sizeof(key_mod_full_map_t); i++) {
        if (keycode == pgm_read_word(&(map[i].keycode))) {
            return get_keycode_according_mods(pgm_read_word(&(map[i].key)), pgm_read_word(&(map[i].key_shift)), pgm_read_word(&(map[i].key_altgr)), pgm_read_word(&(map[i].key_shift_altgr)));
        }
    }
    return keycode;
}

/* Interpret keycode according to modifiers (based on key_mod_altgr_map and key_mod_full_map) */
uint16_t interpret_keycode(const uint16_t keycode) {
    // Identify custom key according to modifiers
    for (uint8_t i = 0; i < sizeof(key_mod_altgr_map) / sizeof(key_alter_map_t); i++) {
        if (keycode == pgm_read_word(&(key_mod_altgr_map[i].keycode))) {
            return get_keycode_according_mods(keycode, C_DUMMY, pgm_read_word(&(key_mod_altgr_map[i].key_alter)), C_DUMMY);
        }
    }
    uint16_t new_keycode = interpret_keycode_in_map(key_mod_full_map, sizeof(key_mod_full_map), keycode);
    return new_keycode;
}

#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
/* Interpret keycode as unicode (in best effort: search direct keycode, then search in all mods variations) */
uint16_t interpret_keycode_unicode(const uint16_t keycode) {
    const uint16_t keycode_direct = interpret_keycode_in_map(unicode_mod_full_map, sizeof(unicode_mod_full_map), keycode);
    if (keycode_direct == keycode) {
        int16_t size = sizeof(unicode_mod_full_map) / sizeof(key_mod_full_map_t);
        // Keycode not found in map: search in altgr variation
        for (uint8_t i = 0; i < size; i++) {
            if (keycode == ALGR(unicode_mod_full_map[i].keycode)) {
                return get_keycode_according_mods(pgm_read_word(&(unicode_mod_full_map[i].key_altgr)), pgm_read_word(&(unicode_mod_full_map[i].key_shift_altgr)), C_DUMMY, C_DUMMY);
            }
        }
        // Not found in altgr: search in shift and shift + altgr variations
        for (uint8_t i = 0; i < size; i++) {
            if (keycode == S(unicode_mod_full_map[i].keycode)) {
                return unicode_mod_full_map[i].key_shift;
            }
            if (keycode == S(ALGR(unicode_mod_full_map[i].keycode))) {
                return unicode_mod_full_map[i].key_shift_altgr;
            }
        }
    }
    return keycode_direct;
}
#endif // defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)

/* Tap char according to unicode activation or not */
void tap_char_u(const uint16_t keycode) {
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    if (user_config.unicode) {
        unicode_input_start();
        register_hex32(interpret_keycode_unicode(keycode));
        unicode_input_finish();
    } else {
        tap_code16(keycode);
    }
#else
    tap_code16(keycode);
#endif
}

/* Tap non breakable space according to unicode activation or not */
void tap_nbsp_u(void) {
    tap_char_u(BP_NBSP); // non breakable space char
}

/* Send a PROGMEM string or unicode string according to Unicode activation */
void send_str(const char* str) {
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    if (user_config.unicode) {
        send_unicode_string(str);
    } else {
        send_string_P(str);
    }
#else
    send_string_P(str);
#endif
    // Set the number of chars sent
    nb_char_sent = strlen(str);
}

/* register or unregister (f argument for function) a keycode without interaction of current mods */
void do_f_keycode(const uint16_t keycode, void (*f)(uint16_t)) {
    // Clear mods
    uint8_t weak_mods = get_weak_mods();
    uint8_t real_mods = get_mods();
    clear_weak_mods();
    clear_mods();
    // Call function
    f(keycode);
    // Restore mods
    set_weak_mods(weak_mods);
    set_mods(real_mods);
}

/* Get the keycode with the mods applied */
uint16_t get_keycode_with_mods_applied(const uint16_t keycode) {
    uint16_t code = (keycode != C_DUMMY) ? keycode : 0;
    const uint8_t real_mods = get_mods();
    // Left mods
    if (real_mods & MOD_BIT(KC_LCTL)) {code = LCTL(code);}
    if (real_mods & MOD_BIT(KC_LSFT)) {code = LSFT(code);}
    if (real_mods & MOD_BIT(KC_LALT)) {code = LALT(code);}
    if (real_mods & MOD_BIT(KC_LGUI)) {code = LGUI(code);}
    // Right mods
    if (real_mods & MOD_BIT(KC_RCTL)) {code = RCTL(code);}
    if (real_mods & MOD_BIT(KC_RSFT)) {code = RSFT(code);}
    if (real_mods & MOD_BIT(KC_RALT)) {code = RALT(code);}
    if (real_mods & MOD_BIT(KC_RGUI)) {code = RGUI(code);}

    return code;
}

/* Number of char that was sent last time */
uint8_t nb_char_sent = 0;

/* Callback (used by core) to handle custom keys behavior implementation */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //--------------------------------------------
    // Alter (interpret) the keycode to adjust it
    //--------------------------------------------

    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode &= QK_BASIC_MAX;
    }
    // Identify custom/overridded key according to modifiers
    uint16_t keycode_new = interpret_keycode(keycode);
    switch (keycode_new) {
    case C_RESET_EEPROM:
        eeconfig_init();
        return false;
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    case C_TOGGLE_UNICODE:
        user_config.unicode = !user_config.unicode;
        eeconfig_update_user(user_config.raw);
        return false;
#endif // defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    case KC_BSPACE:
        if (record->event.pressed) {
            // Remove the string previously sent (except 1 that is processed normally)
            while (nb_char_sent > 1) {
                tap_code(KC_BSPACE);
                nb_char_sent--;
            }
        }
        break;
    }

    // The last pressed key (after alteration cycle in process_record_user)
    static uint16_t previous_keycode = C_DUMMY;
    static uint16_t next_previous_keycode = C_DUMMY;
    static uint16_t next_previous_keycode_not_altered = C_DUMMY;
    static uint16_t next_previous_keycode_new = C_DUMMY;
    // Don't do it on modifiers and don't store QMK functions || Filter out the actual keycode from MT and LT keys
    if (record->event.pressed && (keycode_new < KC_LCTRL || keycode_new > KC_RGUI)) {
        // Store last keycode for reference in user functions
        previous_keycode = next_previous_keycode;
        next_previous_keycode = (keycode != keycode_new) ? keycode_new : get_keycode_with_mods_applied(keycode);
        next_previous_keycode_not_altered = keycode;
        next_previous_keycode_new = (keycode != keycode_new) ? keycode_new : keycode;
        nb_char_sent = 1;
    }

    //-----------------------------
    // Process the altered keycode
    //-----------------------------

#ifdef USER_CLOSE_CHAR
    // Check if this is an open char or the special close key or a close char (and remove it of the list)
    keycode_new = handle_open_close_char(keycode_new, (keycode != keycode_new), record, previous_keycode);
#endif // USER_CLOSE_CHAR
#ifdef DYNAMIC_MACRO_ENABLE
    // Check if this is a macro key and process it if true
    if (!handle_dynamic_macro(keycode_new, record)) {
        return false;
    }
#endif // DYNAMIC_MACRO_ENABLE
#ifdef OLED_DRIVER_ENABLE
    if (!handle_oled(keycode_new, record)) {
        return false;
    }
#endif // OLED_DRIVER_ENABLE
#ifdef RGBLIGHT_ENABLE
    if (!handle_rgb(keycode_new, record)) {
        return false;
    }
#endif // RGBLIGHT_ENABLE

#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    if (user_config.unicode) {
        keycode_new = interpret_keycode_unicode(keycode_new);
    }
    // Unicode is processed by quantum -> skip it
#   ifdef UNICODE_ENABLE
    if (keycode_new < QK_UNICODE || keycode_new > QK_UNICODE_MAX)
#   else // UNICODE_ENABLE
    if (keycode_new < QK_UNICODEMAP || keycode_new > QK_UNICODEMAP_MAX)
#   endif // UNICODE_ENABLE
#endif // defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    {
        // If keycode is changed, process is else skip it
        if (keycode != keycode_new && keycode_new <= QK_MODS_MAX) {
            do_f_keycode(keycode_new, record->event.pressed ? register_code16 : unregister_code16);
            return false;
        } else if (!record->event.pressed
                && next_previous_keycode_not_altered == keycode
                && next_previous_keycode_not_altered != next_previous_keycode
                && next_previous_keycode_not_altered != next_previous_keycode_new) {
            // Specific case when modifiers are released too early thus custom key is not recognized when release is processed
            // here: only check if keycode from layout is the same as the last pressed and was a custom key
            do_f_keycode(next_previous_keycode, unregister_code16);
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE)
        } else {
            return process_unicode_common(keycode_new, record);
#endif
        }
    }
    // Process all other keycodes normally
    return true;
}

#endif // FOLLOWER_ONLY
