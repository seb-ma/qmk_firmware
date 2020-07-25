#ifdef USER_ADDING_NBSP
#include "keymap_bepo.h"

#include "custom_keys.h"
#include "eeprom_user.h"
#include "user_feature_closechar.h"
#include "user_feature_nbsp.h"

/* Indicates if a non-breakable space must be added (according to holding modifier) */
bool mod_hold_nb_sp = false;

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

/* Add a non breaking space when typping some chars: ;:!?«» */
uint16_t handle_adding_non_breaking_space(const uint16_t keycode, const bool ignore_mods, const keyrecord_t *const record) {
    if (keycode == C_TAB_NBSP) { // Manage non breaking space or tabulation
        static uint16_t timer = 0;
        mod_hold_nb_sp = record->event.pressed;
        if (record->event.pressed) {
            // Holding
            timer = timer_read();
            return C_DUMMY;
        } else if (timer_elapsed(timer) > TAPPING_TERM) {
            // Released and not a tap - don't process tab
            return C_DUMMY;
        }
        // else: press a tab
        // FIXME: can't process tab holding
        tap_char_u(KC_TAB);
        return C_DUMMY;
    } else if (mod_hold_nb_sp && record->event.pressed) {
        const uint16_t keycode_mods = ignore_mods ? keycode : get_keycode_with_mods_applied(keycode);



        switch (keycode_mods) {
        case BP_LDAQ: // «
            tap_char_u(keycode_mods);
            tap_nbsp_u();
#ifdef USER_CLOSE_CHAR
            // Specific case where keycode has been immediately processed as a tap. Register it directly in close char.
            handle_open_close_char(keycode_mods, true, record, C_DUMMY);
#endif
            return C_DUMMY;
        case BP_RDAQ: // »
        case BP_EXLM: // !
        case BP_SCLN: // ;
        case BP_COLN: // :
        case BP_QUES: // ?
            tap_nbsp_u();
            // Open char will be processed normally
            break;
        }
    }
    // Process all other keycodes normally
    return keycode;
}
#endif // USER_ADDING_NBSP
