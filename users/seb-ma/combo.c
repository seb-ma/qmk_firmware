#ifdef COMBO_ENABLE
#include QMK_KEYBOARD_H
#include <string.h>
#include "keymap_bepo.h"

#include "custom_keys.h"
#include "user_feature_closechar.h"
#ifndef NO_SECRETS
#   include "secrets.h" // file may not exist
#endif

/* List of combos */
enum combo_events {
    // Shortcuts (8)
    COMBO_close = 0,
    COMBO_select_all,
    COMBO_cut,
    COMBO_copy,
    COMBO_paste,
    COMBO_undo,
    COMBO_redo,
    COMBO_last_tab,
    // Quadrigrams (5)
    COMBO_elle,
    COMBO_ique,
    COMBO_ment,
    COMBO_quel,
    COMBO_tion,
    // Non-breaking space (12)
    COMBO_nbsp_ldaq,
    COMBO_nbsp_rdaq,
    COMBO_nbsp_u,
    COMBO_nbsp_i,
    COMBO_nbsp_exlm,
    COMBO_nbsp_scln,
    COMBO_nbsp_coln,
    COMBO_nbsp_ques,
    COMBO_nbsp_dcir,
    COMBO_nbsp_comm,
    COMBO_nbsp_dot,
    COMBO_nbsp_rsqu,
    // Others (2)
    COMBO_https,
    COMBO_giphy,
#ifndef NO_SECRETS
    COMBO_uid,
    COMBO_product,
#endif

    COMBO_SIZE
};

/* Check of declaration of COMBO_COUNT */
_Static_assert(COMBO_COUNT == COMBO_SIZE, "COMBO_COUNT must be defined to the same value than COMBO_SIZE");


/* Definition of combos */
// Shortcuts
const uint16_t combo_close      [] PROGMEM = {KC_TAB,   BP_AGRV, COMBO_END};
const uint16_t combo_select_all [] PROGMEM = {KC_TAB,   BP_A,    COMBO_END};
const uint16_t combo_cut        [] PROGMEM = {KC_TAB,   BP_U,    COMBO_END};
const uint16_t combo_copy       [] PROGMEM = {KC_TAB,   BP_I,    COMBO_END};
const uint16_t combo_paste      [] PROGMEM = {KC_TAB,   BP_E,    COMBO_END};
const uint16_t combo_undo       [] PROGMEM = {KC_TAB,   BP_P,    COMBO_END};
const uint16_t combo_redo       [] PROGMEM = {KC_TAB,   BP_O,    COMBO_END};
const uint16_t combo_last_tab   [] PROGMEM = {KC_TAB,   BP_T,    COMBO_END};
// Quadrigrams
const uint16_t combo_elle       [] PROGMEM = {BP_E,     BP_L,    COMBO_END};
const uint16_t combo_ique       [] PROGMEM = {BP_I,     BP_Q,    COMBO_END};
const uint16_t combo_ment       [] PROGMEM = {BP_M,     BP_E,    COMBO_END};
const uint16_t combo_quel       [] PROGMEM = {BP_Q,     BP_U,    COMBO_END};
const uint16_t combo_tion       [] PROGMEM = {BP_T,     BP_I,    COMBO_END};
// Non-breaking space
const uint16_t combo_nbsp_ldaq  [] PROGMEM = {KC_SPACE, BP_LDAQ, COMBO_END}; // « (nbsp after)
const uint16_t combo_nbsp_rdaq  [] PROGMEM = {KC_SPACE, BP_RDAQ, COMBO_END}; // »
const uint16_t combo_nbsp_u     [] PROGMEM = {KC_SPACE, BP_U,    COMBO_END}; // u (sublayer of «)
const uint16_t combo_nbsp_i     [] PROGMEM = {KC_SPACE, BP_I,    COMBO_END}; // i (sublayer of »)
const uint16_t combo_nbsp_exlm  [] PROGMEM = {KC_SPACE, BP_EXLM, COMBO_END}; // !
const uint16_t combo_nbsp_scln  [] PROGMEM = {KC_SPACE, BP_SCLN, COMBO_END}; // ;
const uint16_t combo_nbsp_coln  [] PROGMEM = {KC_SPACE, BP_COLN, COMBO_END}; // :
const uint16_t combo_nbsp_ques  [] PROGMEM = {KC_SPACE, BP_QUES, COMBO_END}; // ?
const uint16_t combo_nbsp_dcir  [] PROGMEM = {KC_SPACE, BP_DCIR, COMBO_END}; // ^ (non shifted of !)
const uint16_t combo_nbsp_comm  [] PROGMEM = {KC_SPACE, BP_COMM, COMBO_END}; // , (non shifted of ;)
const uint16_t combo_nbsp_dot   [] PROGMEM = {KC_SPACE, BP_DOT , COMBO_END}; // . (non shifted of :)
const uint16_t combo_nbsp_rsqu  [] PROGMEM = {KC_SPACE, BP_RSQU, COMBO_END}; // ’ (non shifted of ?) (different from standard bépo map due to relocation of "'")
// Others
const uint16_t combo_https      [] PROGMEM = {KC_SPACE, BP_H,    COMBO_END};
const uint16_t combo_giphy      [] PROGMEM = {KC_SPACE, BP_G,    COMBO_END};
#ifndef NO_SECRETS
const uint16_t combo_uid        [] PROGMEM = {BP_S,     BP_M,    COMBO_END};
const uint16_t combo_product    [] PROGMEM = {BP_S,     BP_K,    COMBO_END};
#endif // NO_SECRETS

/* Declaration of combos */
combo_t key_combos[COMBO_COUNT] = {
    /* Shortcuts */
    [COMBO_close]      = COMBO(combo_close,      LCTL(BP_W)),
    [COMBO_select_all] = COMBO(combo_select_all, LCTL(BP_A)),
    [COMBO_cut]        = COMBO(combo_cut,        LCTL(BP_X)),
    [COMBO_copy]       = COMBO(combo_copy,       LCTL(BP_C)),
    [COMBO_paste]      = COMBO(combo_paste,      LCTL(BP_V)),
    [COMBO_undo]       = COMBO(combo_undo,       LCTL(BP_Z)),
    [COMBO_redo]       = COMBO(combo_redo,       LCTL(BP_Y)),
    [COMBO_last_tab]   = COMBO(combo_last_tab,   LCTL(LSFT(BP_T))),

    /* Quadrigrams */
    [COMBO_elle]       = COMBO_ACTION(combo_elle),
    [COMBO_ique]       = COMBO_ACTION(combo_ique),
    [COMBO_ment]       = COMBO_ACTION(combo_ment),
    [COMBO_quel]       = COMBO_ACTION(combo_quel),
    [COMBO_tion]       = COMBO_ACTION(combo_tion),

    /* Non-breaking space */
    [COMBO_nbsp_ldaq]  = COMBO_ACTION(combo_nbsp_ldaq), // « (nbsp after)
    [COMBO_nbsp_rdaq]  = COMBO_ACTION(combo_nbsp_rdaq), // »
    // interpertation of sub-layer version of previous keys
    [COMBO_nbsp_u]     = COMBO_ACTION(combo_nbsp_u), // «
    [COMBO_nbsp_i]     = COMBO_ACTION(combo_nbsp_i), // »

    [COMBO_nbsp_exlm]  = COMBO_ACTION(combo_nbsp_exlm), // !
    [COMBO_nbsp_scln]  = COMBO_ACTION(combo_nbsp_scln), // ;
    [COMBO_nbsp_coln]  = COMBO_ACTION(combo_nbsp_coln), // :
    [COMBO_nbsp_ques]  = COMBO_ACTION(combo_nbsp_ques), // ?
    // interpertation of non shifted version of previous keys
    [COMBO_nbsp_dcir]  = COMBO_ACTION(combo_nbsp_dcir), // ^ (!)
    [COMBO_nbsp_comm]  = COMBO_ACTION(combo_nbsp_comm), // , (;)
    [COMBO_nbsp_dot ]  = COMBO_ACTION(combo_nbsp_dot ), // . (:)
    [COMBO_nbsp_rsqu]  = COMBO_ACTION(combo_nbsp_rsqu), // ’ (?) (different from standard bépo map due to relocation of "'")

    /* Others */
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
        /* Quadrigrams */
        case COMBO_elle:
            send_str(PSTR("elle"));
            nb_char_sent = 4;
            break;
        case COMBO_ique:
            send_str(PSTR("ique"));
            nb_char_sent = 4;
            break;
        case COMBO_ment:
            send_str(PSTR("ment"));
            nb_char_sent = 4;
            break;
        case COMBO_quel:
            send_str(PSTR("quel"));
            nb_char_sent = 4;
            break;
        case COMBO_tion:
            send_str(PSTR("tion"));
            nb_char_sent = 4;
            break;

        /* Non-breaking space */
        case COMBO_nbsp_ldaq:
        case COMBO_nbsp_u:
            closechar_push(BP_LDAQ);
            tap_char_u(BP_LDAQ);
            tap_nbsp_u();
            nb_char_sent = 2;
            break;
        case COMBO_nbsp_rdaq:
        case COMBO_nbsp_i:
            closechar_push(BP_RDAQ);
            tap_nbsp_u();
            tap_char_u(BP_RDAQ);
            nb_char_sent = 2;
#ifdef USER_CLOSE_CHAR
            // Remove potential stored close char
            keyrecord_t record;
            record.event.pressed = pressed;
            handle_open_close_char(BP_RDAQ, true, &record, C_DUMMY);
#endif
            break;
        case COMBO_nbsp_exlm:
        case COMBO_nbsp_dcir:
            tap_nbsp_u();
            tap_char_u(BP_EXLM);
            nb_char_sent = 2;
            break;
        case COMBO_nbsp_scln:
        case COMBO_nbsp_comm:
            tap_nbsp_u();
            tap_char_u(BP_SCLN);
            nb_char_sent = 2;
            break;
        case COMBO_nbsp_coln:
        case COMBO_nbsp_dot:
            tap_nbsp_u();
            tap_char_u(BP_COLN);
            nb_char_sent = 2;
            break;
        case COMBO_nbsp_ques:
        case COMBO_nbsp_rsqu:
            tap_nbsp_u();
            tap_char_u(BP_QUES);
            nb_char_sent = 2;
            break;
        /* Others */
        case COMBO_https:
            send_str(PSTR("https://"));
            nb_char_sent = 8;
            break;
        case COMBO_giphy:
            send_str(PSTR("/giphy "));
            nb_char_sent = 7;
            break;
#ifndef NO_SECRETS
        case COMBO_uid:
            send_str(secrets[SEC_UID]);
            nb_char_sent = strlen_P(secrets[SEC_UID]);
            break;
        case COMBO_product:
            send_str(secrets[SEC_PRODUCT]);
            nb_char_sent = strlen_P(secrets[SEC_PRODUCT]);
            break;
#endif // NO_SECRETS
        }
    }
}

#endif // COMBO_ENABLE
