#ifdef COMBO_ENABLE
#include QMK_KEYBOARD_H
#include "keymap_bepo.h"

#include "custom_keys.h"
#ifndef NO_SECRETS
#   include "secrets.h" // file may not exist
#endif

/* List of combos */
enum combo_events {
    // Shortcuts
    COMBO_close = 0,
    COMBO_select_all,
    COMBO_cut,
    COMBO_copy,
    COMBO_paste,
    COMBO_undo,
    COMBO_redo,
    COMBO_last_tab,
    // Quadrigrams
    COMBO_elle,
    COMBO_ique,
    COMBO_ment,
    COMBO_quel,
    COMBO_tion,
    // Others
    COMBO_https,
    COMBO_giphy,
#ifndef NO_SECRETS
    COMBO_uid,
    COMBO_product,
#endif
};


/* Definition of combos */
// Shortcuts
const uint16_t combo_close      [] PROGMEM = {KC_SPACE, BP_AGRV, COMBO_END};
const uint16_t combo_select_all [] PROGMEM = {KC_SPACE, BP_A,    COMBO_END};
const uint16_t combo_cut        [] PROGMEM = {KC_SPACE, BP_U,    COMBO_END};
const uint16_t combo_copy       [] PROGMEM = {KC_SPACE, BP_I,    COMBO_END};
const uint16_t combo_paste      [] PROGMEM = {KC_SPACE, BP_E,    COMBO_END};
const uint16_t combo_undo       [] PROGMEM = {KC_SPACE, BP_P,    COMBO_END};
const uint16_t combo_redo       [] PROGMEM = {KC_SPACE, BP_O,    COMBO_END};
const uint16_t combo_last_tab   [] PROGMEM = {KC_SPACE, BP_T,    COMBO_END};
// Quadrigrams
const uint16_t combo_elle       [] PROGMEM = {BP_E,     BP_L,    COMBO_END};
const uint16_t combo_ique       [] PROGMEM = {BP_I,     BP_Q,    COMBO_END};
const uint16_t combo_ment       [] PROGMEM = {BP_M,     BP_E,    COMBO_END};
const uint16_t combo_quel       [] PROGMEM = {BP_Q,     BP_U,    COMBO_END};
const uint16_t combo_tion       [] PROGMEM = {BP_T,     BP_I,    COMBO_END};
// Others
const uint16_t combo_https      [] PROGMEM = {KC_SPACE, BP_H,    COMBO_END};
const uint16_t combo_giphy      [] PROGMEM = {KC_SPACE, BP_G,    COMBO_END};
#ifndef NO_SECRETS
    const uint16_t combo_uid    [] PROGMEM = {BP_S,     BP_M,    COMBO_END};
    const uint16_t combo_product[] PROGMEM = {BP_S,     BP_K,    COMBO_END};
#endif

/* Declaration of combos */
combo_t key_combos[COMBO_COUNT] = {
    // Shortcuts
    [COMBO_close]      = COMBO(combo_close,      LCTL(BP_W)),
    [COMBO_select_all] = COMBO(combo_select_all, LCTL(BP_A)),
    [COMBO_cut]        = COMBO(combo_cut,        LCTL(BP_X)),
    [COMBO_copy]       = COMBO(combo_copy,       LCTL(BP_C)),
    [COMBO_paste]      = COMBO(combo_paste,      LCTL(BP_V)),
    [COMBO_undo]       = COMBO(combo_undo,       LCTL(BP_Z)),
    [COMBO_redo]       = COMBO(combo_redo,       LCTL(BP_Y)),
    [COMBO_last_tab]   = COMBO(combo_last_tab,   LCTL(LSFT(BP_T))),
    // Quadrigrams
    [COMBO_elle]       = COMBO_ACTION(combo_elle),
    [COMBO_ique]       = COMBO_ACTION(combo_ique),
    [COMBO_ment]       = COMBO_ACTION(combo_ment),
    [COMBO_quel]       = COMBO_ACTION(combo_quel),
    [COMBO_tion]       = COMBO_ACTION(combo_tion),

    // Others
    [COMBO_https]      = COMBO_ACTION(combo_https),
    [COMBO_giphy]      = COMBO_ACTION(combo_giphy),
#ifndef NO_SECRETS
    [COMBO_uid]        = COMBO_ACTION(combo_uid),
    [COMBO_product]    = COMBO_ACTION(combo_product),
#endif
};


/* Callback (used by core) of custom behavior for combos */
void process_combo_event(uint8_t combo_index, bool pressed) {
    if (pressed) {
        switch(combo_index) {
        case COMBO_elle:
            send_str(PSTR("elle"));
            break;
        case COMBO_ique:
            send_str(PSTR("ique"));
            break;
        case COMBO_ment:
            send_str(PSTR("ment"));
            break;
        case COMBO_quel:
            send_str(PSTR("quel"));
            break;
        case COMBO_tion:
            send_str(PSTR("tion"));
            break;
        case COMBO_https:
            send_str(PSTR("https://"));
            break;
        case COMBO_giphy:
            send_str(PSTR("/giphy "));
            break;
#ifndef NO_SECRETS
        case COMBO_uid:
            send_str(secrets[SEC_UID]);
            break;
        case COMBO_product:
            send_str(secrets[SEC_PRODUCT]);
            break;
#endif // NO_SECRETS
        }
    }
}

#endif // COMBO_ENABLE
