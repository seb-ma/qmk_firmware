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
    // Quadrigrams (13)
    //  stats from http://www.bibmath.net/crypto/index.php?action=affiche&quoi=chasseur/frequences_francais
    COMBO_aire, // 0.12%
    COMBO_dans, // 0.18%
    COMBO_elle, // 0.21%
    COMBO_ette, // 0.11%
    COMBO_ente, // 0.12%
    COMBO_ille, // 0.12%
    COMBO_ique, // 0.26%
    COMBO_ment, // 0.31%
    COMBO_omme, // 0.16%
    COMBO_onne, // 0.11%
    COMBO_pour, // 0.16%
    COMBO_quel, // 0.17%
    COMBO_tion, // 0.33%
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
    COMBO_end_sentence,
    COMBO_giphy,
#ifndef NO_SECRETS
    COMBO_uid,
    COMBO_product,
    COMBO_p1,
    COMBO_p2,
#endif

    COMBO_SIZE
};

/* Check of declaration of COMBO_COUNT */
_Static_assert(COMBO_COUNT == COMBO_SIZE, "COMBO_COUNT must be defined to the same value than COMBO_SIZE");


/* Definition of combos */
// Quadrigrams
const uint16_t combo_aire         [] PROGMEM = {BP_A,     BP_I,    COMBO_END};
const uint16_t combo_dans         [] PROGMEM = {BP_D,     BP_A,    COMBO_END};
const uint16_t combo_elle         [] PROGMEM = {BP_E,     BP_L,    COMBO_END};
const uint16_t combo_ente         [] PROGMEM = {BP_E,     BP_N,    COMBO_END};
const uint16_t combo_ette         [] PROGMEM = {BP_E,     BP_T,    COMBO_END};
const uint16_t combo_ille         [] PROGMEM = {BP_I,     BP_L,    COMBO_END};
const uint16_t combo_ique         [] PROGMEM = {BP_I,     BP_Q,    COMBO_END};
const uint16_t combo_ment         [] PROGMEM = {BP_M,     BP_E,    COMBO_END};
const uint16_t combo_omme         [] PROGMEM = {BP_O,     BP_M,    COMBO_END};
const uint16_t combo_onne         [] PROGMEM = {BP_O,     BP_N,    COMBO_END};
const uint16_t combo_pour         [] PROGMEM = {BP_P,     BP_O,    COMBO_END};
const uint16_t combo_quel         [] PROGMEM = {BP_Q,     BP_U,    COMBO_END};
const uint16_t combo_tion         [] PROGMEM = {BP_T,     BP_I,    COMBO_END};
// Non-breaking space
const uint16_t combo_nbsp_ldaq    [] PROGMEM = {KC_SPACE, BP_LDAQ, COMBO_END}; // « (nbsp after)
const uint16_t combo_nbsp_rdaq    [] PROGMEM = {KC_SPACE, BP_RDAQ, COMBO_END}; // »
const uint16_t combo_nbsp_u       [] PROGMEM = {KC_SPACE, BP_U,    COMBO_END}; // u (sublayer of «)
const uint16_t combo_nbsp_i       [] PROGMEM = {KC_SPACE, BP_I,    COMBO_END}; // i (sublayer of »)
const uint16_t combo_nbsp_exlm    [] PROGMEM = {KC_SPACE, BP_EXLM, COMBO_END}; // !
const uint16_t combo_nbsp_scln    [] PROGMEM = {KC_SPACE, BP_SCLN, COMBO_END}; // ;
const uint16_t combo_nbsp_coln    [] PROGMEM = {KC_SPACE, BP_COLN, COMBO_END}; // :
const uint16_t combo_nbsp_ques    [] PROGMEM = {KC_SPACE, BP_QUES, COMBO_END}; // ?
const uint16_t combo_nbsp_dcir    [] PROGMEM = {KC_SPACE, BP_DCIR, COMBO_END}; // ^ (non shifted of !)
const uint16_t combo_nbsp_comm    [] PROGMEM = {KC_SPACE, BP_COMM, COMBO_END}; // , (non shifted of ;)
const uint16_t combo_nbsp_dot     [] PROGMEM = {KC_SPACE, BP_DOT , COMBO_END}; // . (non shifted of :)
const uint16_t combo_nbsp_rsqu    [] PROGMEM = {KC_SPACE, BP_RSQU, COMBO_END}; // ’ (non shifted of ?) (different from standard bépo map due to relocation of "'")
// Others
const uint16_t combo_end_sentence [] PROGMEM = {BP_T,     BP_DOT,  COMBO_END};
const uint16_t combo_giphy        [] PROGMEM = {KC_SPACE, BP_G,    COMBO_END};
#ifndef NO_SECRETS
const uint16_t combo_uid          [] PROGMEM = {BP_S,     BP_M,    COMBO_END};
const uint16_t combo_product      [] PROGMEM = {BP_S,     BP_K,    COMBO_END};
const uint16_t combo_p1           [] PROGMEM = {BP_P,     BP_T,    COMBO_END};
const uint16_t combo_p2           [] PROGMEM = {BP_P,     BP_S,    COMBO_END};
#endif // NO_SECRETS

/* Declaration of combos */
combo_t key_combos[COMBO_COUNT] = {
    /* Quadrigrams */
    [COMBO_aire]         = COMBO_ACTION(combo_aire),
    [COMBO_dans]         = COMBO_ACTION(combo_dans),
    [COMBO_elle]         = COMBO_ACTION(combo_elle),
    [COMBO_ette]         = COMBO_ACTION(combo_ette),
    [COMBO_ente]         = COMBO_ACTION(combo_ente),
    [COMBO_ille]         = COMBO_ACTION(combo_ille),
    [COMBO_ique]         = COMBO_ACTION(combo_ique),
    [COMBO_ment]         = COMBO_ACTION(combo_ment),
    [COMBO_omme]         = COMBO_ACTION(combo_omme),
    [COMBO_onne]         = COMBO_ACTION(combo_onne),
    [COMBO_pour]         = COMBO_ACTION(combo_pour),
    [COMBO_quel]         = COMBO_ACTION(combo_quel),
    [COMBO_tion]         = COMBO_ACTION(combo_tion),

    /* Non-breaking space */
    [COMBO_nbsp_ldaq]    = COMBO_ACTION(combo_nbsp_ldaq), // « (nbsp after)
    [COMBO_nbsp_rdaq]    = COMBO_ACTION(combo_nbsp_rdaq), // »
    // interpertation of sub-layer version of previous keys
    [COMBO_nbsp_u]       = COMBO_ACTION(combo_nbsp_u), // «
    [COMBO_nbsp_i]       = COMBO_ACTION(combo_nbsp_i), // »

    [COMBO_nbsp_exlm]    = COMBO_ACTION(combo_nbsp_exlm), // !
    [COMBO_nbsp_scln]    = COMBO_ACTION(combo_nbsp_scln), // ;
    [COMBO_nbsp_coln]    = COMBO_ACTION(combo_nbsp_coln), // :
    [COMBO_nbsp_ques]    = COMBO_ACTION(combo_nbsp_ques), // ?
    // interpertation of non shifted version of previous keys
    [COMBO_nbsp_dcir]    = COMBO_ACTION(combo_nbsp_dcir), // ^ (!)
    [COMBO_nbsp_comm]    = COMBO_ACTION(combo_nbsp_comm), // , (;)
    [COMBO_nbsp_dot ]    = COMBO_ACTION(combo_nbsp_dot ), // . (:)
    [COMBO_nbsp_rsqu]    = COMBO_ACTION(combo_nbsp_rsqu), // ’ (?) (different from standard bépo map due to relocation of "'")

    /* Others */
    [COMBO_end_sentence] = COMBO_ACTION(combo_end_sentence),
    [COMBO_giphy]        = COMBO_ACTION(combo_giphy),
#ifndef NO_SECRETS
    [COMBO_uid]          = COMBO_ACTION(combo_uid),
    [COMBO_product]      = COMBO_ACTION(combo_product),
    [COMBO_p1]           = COMBO_ACTION(combo_p1),
    [COMBO_p2]           = COMBO_ACTION(combo_p2),
#endif
};

/* Values of quadrigrams (must be in same order as in combo_events) */
static const char quadrigrams[][5] PROGMEM = {
    "aire", // COMBO_aire
    "dans", // COMBO_dans
    "elle", // COMBO_elle
    "ette", // COMBO_ette
    "ente", // COMBO_ente
    "ille", // COMBO_ille
    "ique", // COMBO_ique
    "ment", // COMBO_ment
    "omme", // COMBO_omme
    "onne", // COMBO_onne
    "pour", // COMBO_pour
    "quel", // COMBO_quel
    "tion", // COMBO_tion
};

/* Callback (used by core) of custom behavior for combos */
void process_combo_event(uint8_t combo_index, bool pressed) {
    if (pressed) {
        switch(combo_index) {
        /* Quadrigrams */
        case COMBO_aire ... COMBO_tion:
            send_str(quadrigrams[combo_index - COMBO_aire]);
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
        case COMBO_end_sentence:
            send_str(PSTR(". "));
#ifndef NO_ACTION_ONESHOT
            set_oneshot_mods(MOD_LSFT);
#endif
            nb_char_sent = 2;
            break;
        case COMBO_giphy:
            send_str(PSTR("/giphy "));
            nb_char_sent = 7;
            break;
#ifndef NO_SECRETS
        case COMBO_uid ... COMBO_p2:
            send_str(secrets[combo_index - COMBO_uid]);
            nb_char_sent = strlen_P(secrets[combo_index - COMBO_uid]);
            break;
#endif // NO_SECRETS
        }
    }
}

#endif // COMBO_ENABLE
