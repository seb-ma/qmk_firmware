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

/*

Physical keys representation by default:
 ┌────────────────┐  ▒    Dead key
 │     others     │  #S   with Shift
 │ key      key#S │  #AG  with AltGr
 │ key#AG key#AGS │  #AGS with AltGr + Shift
 └────────────────┘  #H   Holding

//
//                                           Left                                                             Right
//
//              1       2       3       4       5       6                                             1       2       3       4       5       6
//                          ┌───────┬───────┬───────┬───────┐                                     ┌───────┬───────┬───────┬───────┐
//          ┌───────┬───────┤       │       │       │       │                                     │       │       │       │       ├───────┬───────┐
//          │       │       │       │       │       │       │                                     │       │       │       │       │       │       │
//    Row 1 │       │       │       │       │       │       │                                     │       │       │       │       │       │       │
//          │       │       ├───────┼───────┼───────┼───────┤                                     ├───────┼───────┼───────┼───────┤       │       │
//          ├───────┼───────┤       │       │       │       │                                     │       │       │       │       ├───────┼───────┤
//          │       │       │       │       │       │       │                                     │       │       │       │       │       │       │
//    Row 2 │       │       │       │       │       │       │                                     │       │       │       │       │       │       │
//          │       │       ├───────┼───────┼───────┼───────┤    1      2            1      2     ├───────┼───────┼───────┼───────┤       │       │
//          ├───────┼───────┤       │       │       │       │┌───────┬───────┐   ┌───────┬───────┐│       │       │       │       ├───────┼───────┤
//          │       │       │       │       │       │       ││       │       │   │       │       ││       │       │       │       │       │       │
//    Row 3 │       │       │       │       │       │       ││  Thumb│row 1  │   │  Thumb│row 1  ││       │       │       │       │       │       │
//          │       │       ├───────┴───────┴───────┴───────┘│       │       │   │       │       │└───────┴───────┴───────┴───────┤       │       │
//          └───────┴───────┘    ┌───────┬───────┬───────┬───┴───┬───┴───┬───┘   └───┬───┴───┬───┴───┬───────┬───────┬───────┐    └───────┴───────┘
//                               │       │       │       │       │       │           │       │       │       │       │       │
//                   Thumb row 2 │ ENC 1 │       │       │       │       │           │       │       │       │       │ ENC 2 │
//                               │       │       │       │       │       │           │       │       │       │       │       │
//                               └───────┴───────┴───────┴───────┴───────┘           └───────┴───────┴───────┴───────┴───────┘
//                                   1       2       3       4       5                   1       2       3       4       5
//
*/

#pragma once
#include QMK_KEYBOARD_H
#include "keymap_bepo.h"

#include "custom_keys.h"
#include "layers.h"
#include "tap_dance.h"


//-------------
// Layer _BEPO
//-------------
// bépo adapted:
//  - move of 'w' from row 1 to row 3
//  - replacement of AltGr and AltGr+Shift on 'c' to have 'ç' and 'Ç' (chars becoming unavalable: ©ſ)
//  - swap of `'` and `’`
// holding tab: add nbsp automatically on chars «»!?;:
// Layers NUMBERS/SYMBOLS + NAVIGATION/MOUSE to access layer MEDIA/RGB
//
// some dead code may vary according to OS (official layout: https://bepo.fr/wiki/Accueil)
//
// NB: some standard keys are overridded in custom_keys.c (interpret_keycode) - instead of a clean custom key to save some bytes in key_mod_altgr_map)
//-------------
//
//                                           Left                                                             Right
//
//              1       2       3       4       5       6                                             1       2       3         4       5       6
//                          ┌───────┬───────┬───────┬───────┐                                     ┌───────┬───────┬───────┬───────┐
//          ┌───────┬───────┤       │       │       │       │                                     │       │       │       │       ├───────┬───────┐
//          │       │       │ é   É │ p   P │ o   O │ è   È │                                     │ ^   ! │ v   V │ d   D │ l   L │       │       │
//    Row 1 │Esc    │ b   B │ ´▒  ˝▒│ &   § │ œ   Œ │ `▒  ` │                                     │ ¡     │ ˇ▒    │ ð   Ð │ /▒    │ j   J │ z   Z │
//          │CapLck │ |   ¦ ├───────┼───────┼───────┼───────┤                                     ├───────┼───────┼───────┼───────┤ ĳ   Ĳ │ ə   Ə │
//          ├───────┼───────┤       │       │       │       │                                     │       │       │       │       ├───────┼───────┤
//          │       │       │ u   U │ i   I │ e   E │ ,   ; │                                     │ c   C │ t   T │ s   S │ r   R │       │       │
//    Row 2 │Clo    │ a   A │ ù   Ù │ ¨▒  ˙▒│ €   ¤▒│ ’   ̛ ▒│                                     │ ç   Ç │ þ   Þ │ ß   ẞ │ ®   ™ │ n   N │ m   M │
//          │ClCl#AG│ æ   Æ ├───────┼───────┼───────┼───────┤    1      2            1      2     ├───────┼───────┼───────┼───────┤ ~▒    │ ¯▒  º │
//          ├───────┼───────┤       │       │       │       │┌───────┬───────┐   ┌───────┬───────┐│       │       │       │       ├───────┼───────┤
//          │       │       │ y   Y │ x   X │ .   : │ k   K ││       │       │   │       │       ││ '   ? │ q   Q │ g   G │ h   H │       │       │
//    Row 3 │ ê   Ê │ à   À │ {   ‘ │ }   ’ │ …   · │ ~     ││ Ctrl  │ BckSp │   │  Del  │ Shift ││ ¿    ̉▒│ °▒   ̣▒│ µ▒    │ †   ‡ │ f   F │ w   W │
//          │ /     │ \     ├───────┴───────┴───────┴───────┘│       │       │   │       │       │└───────┴───────┴───────┴───────┤ ˛▒  ª │ ˘▒    │
//          └───────┴───────┘     ▄▄▄▄▄▄▄┌───────┬───────┬───┴───┬───┴───┬───┘   └───┬───┴───┬───┴───┬───────┬───────┐▄▄▄▄▄▄▄     └───────┴───────┘
//                               ▐▲▼Pag#S▌       │(Layer)│[Shift]│[Layer]│           │       │[AltGr]│(Layer)│       ▐◄►Wrd#S▌
//    Thumb row 2                ▐  Gui  ▌  Alt  │       │Sp NbSp│SHRTCUT│           │  Alt  │ Enter │NAV/MOU│ Ctrl  ▐  App  ▌
//                               ▐  ↑↓   ▌       │NUM/SYM│_ NNbSp│  Tab  │           │       │       │       │       ▐  ←→   ▌
//                                ▀▀▀▀▀▀▀└───────┴───────┴───────┴───────┘           └───────┴───────┴───────┴───────┘▀▀▀▀▀▀▀
//                                   1       2       3       4       5                   1       2       3       4       5

// Alphas
#define BEPO_ROW1_LEFT        KC_ESC,       BP_B,    BP_EACU, BP_P, BP_O,   BP_EGRV,
#define BEPO_ROW1_RIGHT       BP_DCIR,      BP_V,    BP_D,    BP_L, BP_J,   BP_Z,
#define BEPO_ROW2_LEFT        C_CLOSE_CHAR, BP_A,    BP_U,    BP_I, BP_E,   BP_COMM,
#define BEPO_ROW2_RIGHT       BP_C,         BP_T,    BP_S,    BP_R, BP_N,   BP_M,
#define BEPO_ROW3_LEFT        BP_ECIR,      BP_AGRV, BP_Y,    BP_X, BP_DOT, BP_K,
#define BEPO_ROW3_RIGHT       BP_RSQU,      BP_Q,    BP_G,    BP_H, BP_F,   BP_W,

#define BEPO_THUMB_ROW1_LEFT                                                         KC_LCTRL,               KC_BSPACE,
#define BEPO_THUMB_ROW2_LEFT  KC_LGUI,   KC_LALT,                TT(_FUNC_NUM_SYMB), MT(MOD_RSFT, KC_SPACE), LT(_SHORTCUTS, KC_TAB),
#define BEPO_THUMB_ROW1_RIGHT KC_DELETE, KC_LSHIFT,
#define BEPO_THUMB_ROW2_RIGHT KC_LALT,   MT(MOD_RALT, KC_ENTER), TT(_NAV_MOUSE),     KC_LCTRL,               KC_APPLICATION

//----------------------
// Layer _FUNC_NUM_SYMB
//----------------------
// bépo adapted: (see custom_keys.c for implementation)
//  - F11, F12 and F13 with AltGr on F1, F2 and F3
//  - BP_LCBR and BP_RCBR with AltGr on F4 and F5
//  - BP_DCIR and BP_CARN with AltGr on F6 and F7
//  - BP_BSLS and BP_SLSH with AltGr on F8 and F9
//  - BP_COMM, BP_DOT (and shift association) on right of key 0
//
//                                           Left                                                             Right
//
//              1       2       3       4       5       6                                             1       2       3       4       5       6
//                          ┌───────┬───────┬───────┬───────┐                                     ┌───────┬───────┬───────┬───────┐
//          ┌───────┬───────┤       │       │       │       │                                     │       │       │       │       ├───────┬───────┐
//          │       │       │ 2     │ 3     │ 4     │ 5     │                                     │ 6     │ 7     │ 8     │ 9     │       │       │
//    Row 1 │  ___  │ 1     │ “     │ ”     │ ≤     │ ≥     │                                     │       │ ¬     │ ¼     │ ½     │ 0     │ ,   ; │
//          │       │ „     ├───────┼───────┼───────┼───────┤                                     ├───────┼───────┼───────┼───────┤ ¾     │ .   : │
//          ├───────┼───────┤       │       │       │       │                                     │       │       │       │       ├───────┼───────┤
//          │       │       │ «     │ »     │ (     │ )     │                                     │ @     │ +     │ -     │ /     │       │       │
//    Row 2 │  ___  │ "     │ <   “ │ >   ” │ [   ≤ │ ]   ≥ │                                     │ ^     │ ±   ¬ │ −   ¼ │ ÷   ½ │ *     │ =   ° │
//          │       │ ─   „ ├───────┼───────┼───────┼───────┤    1      2            1      2     ├───────┼───────┼───────┼───────┤ ×   ¾ │ ≠   ′ │
//          ├───────┼───────┤       │       │       │       │┌───────┬───────┐   ┌───────┬───────┐│       │       │       │       ├───────┼───────┤
//          │       │       │ F2    │ F3    │ F4    │ F5    ││       │       │   │       │       ││ F6    │ F7    │ F8    │ F9    │       │       │
//    Row 3 │ $   # │ F1    │ F12   │ F13   │ {     │ }     ││  ___  │  ___  │   │  ___  │  ___  ││ ^▒    │ ˇ▒    │ \     │ /     │ F10   │ %   ` │
//          │ –   ¶ │ F11   ├───────┴───────┴───────┴───────┘│       │       │   │       │       │└───────┴───────┴───────┴───────┤       │     ″ │
//          └───────┴───────┘     ▄▄▄▄▄▄▄┌───────┬───────┬───┴───┬───┴───┬───┘   └───┬───┴───┬───┴───┬───────┬───────┐▄▄▄▄▄▄▄     └───────┴───────┘
//                               ▐       ▌       │       │       │       │           │       │       │       │       ▐       ▌
//                   Thumb row 2 ▐  ___  ▌  ___  │  ___  │  ___  │  ___  │           │  ___  │  ___  │  ___  │  ___  ▐  ___  ▌
//                               ▐       ▌       │       │       │       │           │       │       │       │       ▐       ▌
//                                ▀▀▀▀▀▀▀└───────┴───────┴───────┴───────┘           └───────┴───────┴───────┴───────┘▀▀▀▀▀▀▀
//                                   1       2       3       4       5                   1       2       3       4       5
//

// Functions
#define FUNC_NUM_SYMB_ROW1_LEFT        _______, BP_1,    BP_2,    BP_3,    BP_4,    BP_5,
#define FUNC_NUM_SYMB_ROW1_RIGHT       BP_6,    BP_7,    BP_8,    BP_9,    BP_0,    C_COMMA_DOT,
// Numbers
#define FUNC_NUM_SYMB_ROW2_LEFT        _______, BP_DQUO, BP_LDAQ, BP_RDAQ, BP_LPRN, BP_RPRN,
#define FUNC_NUM_SYMB_ROW2_RIGHT       BP_AT,   BP_PLUS, BP_MINS, BP_SLSH, BP_ASTR, BP_EQL,
// Symbols
#define FUNC_NUM_SYMB_ROW3_LEFT        BP_DLR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
#define FUNC_NUM_SYMB_ROW3_RIGHT       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  BP_PERC,

#define FUNC_NUM_SYMB_THUMB_ROW1_LEFT                             _______, _______,
#define FUNC_NUM_SYMB_THUMB_ROW2_LEFT  _______, _______, _______, _______, _______,
#define FUNC_NUM_SYMB_THUMB_ROW1_RIGHT _______, _______,
#define FUNC_NUM_SYMB_THUMB_ROW2_RIGHT _______, _______, _______, _______, _______

//------------------
// Layer _NAV_MOUSE
//------------------
//
//                                           Left                                                             Right
//
//              1       2       3       4       5       6                                             1       2       3       4       5       6
//                          ┌───────┬───────┬───────┬───────┐                                     ┌───────┬───────┬───────┬───────┐
//          ┌───────┬───────┤       │       │       │       │                                     │       │       │       │       ├───────┬───────┐
//          │       │       │   ▼   │   ▲   │   ►   │ Btn3  │                                     │ Shift │   ◄   │   ▼   │   ▲   │       │       │
//    Row 1 │  ___  │   ◄   │(mouse)│(mouse)│(mouse)│(mouse)│                                     │   ◄   │       │       │       │   ►   │ Shift │
//          │       │(mouse)├───────┼───────┼───────┼───────┤                                     ├───────┼───────┼───────┼───────┤       │   ►   │
//          ├───────┼───────┤       │       │       │       │                                     │       │       │       │       ├───────┼───────┤
//          │       │       │   ↓   │   ↑   │   →   │ Btn1  │                                     │ Ctrl  │   ←   │   ↓   │   ↑   │       │       │
//    Row 2 │       │   ←   │(mouse)│(mouse)│(mouse)│(mouse)│                                     │   ←   │       │       │       │   →   │ Ctrl  │
//          │       │(mouse)├───────┼───────┼───────┼───────┤    1      2            1      2     ├───────┼───────┼───────┼───────┤       │   →   │
//          ├───────┼───────┤       │       │       │       │┌───────┬───────┐   ┌───────┬───────┐│ Shift │       │       │       ├───────┼───────┤
//          │       │       │       │       │       │ Btn2  ││       │       │   │       │       ││ Ctrl  │ Shift │ Shift │ Shift │       │ Shift │
//    Row 3 │       │       │       │       │       │(mouse)││  ___  │  ___  │   │  ___  │  ___  ││   ←   │   ←   │   ↓   │   ↑   │ Shift │ Ctrl  │
//          │       │       ├───────┴───────┴───────┴───────┘│       │       │   │       │       │└───────┴───────┴───────┴───────┤   →   │   →   │
//          └───────┴───────┘     ▄▄▄▄▄▄▄┌───────┬───────┬───┴───┬───┴───┬───┘   └───┬───┴───┬───┴───┬───────┬───────┐▄▄▄▄▄▄▄     └───────┴───────┘
//                               ▐       ▌       │       │       │       │           │       │       │       │       ▐       ▌
//                   Thumb row 2 ▐  ___  ▌  ___  │  ___  │ Btn1  │  ___  │           │  ___  │  ___  │  ___  │  ___  ▐  ___  ▌
//                               ▐       ▌       │       │(mouse)│       │           │       │       │       │       ▐       ▌
//                                ▀▀▀▀▀▀▀└───────┴───────┴───────┴───────┘           └───────┴───────┴───────┴───────┘▀▀▀▀▀▀▀
//                                   1       2       3       4       5                   1       2       3       4       5
//

// Mouse
#define NAV_MOUSE_ROW1_LEFT        _______,       KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, KC_MS_BTN3,
#define NAV_MOUSE_ROW2_LEFT        XXXXXXX,       KC_MS_LEFT,    KC_MS_DOWN,    KC_MS_UP,    KC_MS_RIGHT,    KC_MS_BTN1,
#define NAV_MOUSE_ROW3_LEFT        XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        KC_MS_BTN2,
// Navigation
#define NAV_MOUSE_ROW1_RIGHT       S(KC_HOME),    KC_HOME,       KC_PGDOWN,     KC_PGUP,     KC_END,         S(KC_END),
#define NAV_MOUSE_ROW2_RIGHT       C(KC_LEFT),    KC_LEFT,       KC_DOWN,       KC_UP,       KC_RIGHT,       C(KC_RIGHT),
#define NAV_MOUSE_ROW3_RIGHT       S(C(KC_LEFT)), S(KC_LEFT),    S(KC_DOWN),    S(KC_UP),    S(KC_RIGHT),    S(C(KC_RIGHT)),

#define NAV_MOUSE_THUMB_ROW1_LEFT                             _______,    _______,
#define NAV_MOUSE_THUMB_ROW2_LEFT  _______, _______, _______, KC_MS_BTN1, _______,
#define NAV_MOUSE_THUMB_ROW1_RIGHT _______, _______,
#define NAV_MOUSE_THUMB_ROW2_RIGHT _______, _______, _______, _______,    _______

//------------------
// Layer _SHORTCUTS
//------------------
//
//                                           Left                                                             Right
//
//              1       2       3       4       5       6                                             1       2       3       4       5       6
//                          ┌───────┬───────┬───────┬───────┐                                     ┌───────┬───────┬───────┬───────┐
//          ┌───────┬───────┤       │       │       │       │                                     │       │       │       │       ├───────┬───────┐
//          │       │       │  New  │ Pr.Scr│ Undo  │ Redo  │                                     │ Shift │   ◄   │   ▼   │   ▲   │       │       │
//    Row 1 │  ___  │       │  tab  │       │       │       │                                     │   ◄   │       │       │       │   ►   │ Shift │
//          │       │       ├───────┼───────┼───────┼───────┤                                     ├───────┼───────┼───────┼───────┤       │   ►   │
//          ├───────┼───────┤       │       │       │       │                                     │       │       │       │       ├───────┼───────┤
//          │       │       │  Cut  │ Copy  │ Paste │Select │                                     │ Ctrl  │   ←   │   ↓   │   ↑   │       │       │
//    Row 2 │DynM1●■│DynM1 ►│       │       │       │  all  │                                     │   ←   │       │       │       │   →   │ Ctrl  │
//          │       │       ├───────┼───────┼───────┼───────┤    1      2            1      2     ├───────┼───────┼───────┼───────┤       │   →   │
//          ├───────┼───────┤       │       │       │       │┌───────┬───────┐   ┌───────┬───────┐│ Shift │       │       │       ├───────┼───────┤
//          │       │       │ Close │Replace│ Find  │  F3   ││       │       │   │       │       ││ Ctrl  │ Shift │ Shift │ Shift │       │ Shift │
//    Row 3 │DynM2●■│DynM2 ►│       │       │       │       ││  ___  │  ___  │   │  ___  │  ___  ││   ←   │   ←   │   ↓   │   ↑   │ Shift │ Ctrl  │
//          │       │       ├───────┴───────┴───────┴───────┘│       │       │   │       │       │└───────┴───────┴───────┴───────┤   →   │   →   │
//          └───────┴───────┘     ▄▄▄▄▄▄▄┌───────┬───────┬───┴───┬───┴───┬───┘   └───┬───┴───┬───┴───┬───────┬───────┐▄▄▄▄▄▄▄     └───────┴───────┘
//                               ▐       ▌       │       │       │       │           │       │       │       │       ▐       ▌
//                   Thumb row 2 ▐  ___  ▌  ___  │  ___  │  ___  │  ___  │           │  ___  │  ___  │  ___  │  ___  ▐  ___  ▌
//                               ▐       ▌       │       │       │       │           │       │       │       │       ▐       ▌
//                                ▀▀▀▀▀▀▀└───────┴───────┴───────┴───────┘           └───────┴───────┴───────┴───────┘▀▀▀▀▀▀▀
//                                   1       2       3       4       5                   1       2       3       4       5
//

// Shortcuts
#define SHORTCUTS_ROW1_LEFT        _______,        XXXXXXX,         C_SC_NEW_TAB, KC_PSCREEN,   C_SC_UNDO,      C_SC_REDO,
#define SHORTCUTS_ROW2_LEFT        DYN_REC_START1, DYN_MACRO_PLAY1, C_SC_CUT,     C_SC_COPY,    C_SC_PASTE,     C_SC_SELECT_ALL,
#define SHORTCUTS_ROW3_LEFT        DYN_REC_START2, DYN_MACRO_PLAY2, C_SC_CLOSE,   C_SC_REPLACE, C_SC_FIND,      KC_F3,
// Navigation
#define SHORTCUTS_ROW1_RIGHT       S(KC_HOME),     KC_HOME,         KC_PGDOWN,    KC_PGUP,      KC_END,         S(KC_END),
#define SHORTCUTS_ROW2_RIGHT       C(KC_LEFT),     KC_LEFT,         KC_DOWN,      KC_UP,        KC_RIGHT,       C(KC_RIGHT),
#define SHORTCUTS_ROW3_RIGHT       S(C(KC_LEFT)),  S(KC_LEFT),      S(KC_DOWN),   S(KC_UP),     S(KC_RIGHT),    S(C(KC_RIGHT)),

#define SHORTCUTS_THUMB_ROW1_LEFT                             _______,                _______,
#define SHORTCUTS_THUMB_ROW2_LEFT  _______, _______, _______, MT(MOD_RSFT, KC_SPACE), _______,
#define SHORTCUTS_THUMB_ROW1_RIGHT _______, _______,
#define SHORTCUTS_THUMB_ROW2_RIGHT _______, _______, _______, _______, _______

//------------------
// Layer _MEDIA_RGB
// Volume and track on encoders
//------------------
//
//                                           Left                                                             Right
//
//              1       2       3       4       5       6                                             1       2       3       4       5       6
//                          ┌───────┬───────┬───────┬───────┐                                     ┌───────┬───────┬───────┬───────┐
//          ┌───────┬───────┤       │       │       │       │                                     │       │       │       │       ├───────┬───────┐
//          │eepr#AG│       │ Hue↑  │ Sat↑  │ Val↑  │Speed↑ │                                     │Bright↑│       │       │       │       │eepr#AG│
//    Row 1 │Toggle │ Mode→ │ (RGB) │ (RGB) │ (RGB) │ (RGB) │                                     │       │       │       │       │       │Toggle │
//          │ (RGB) │ (RGB) ├───────┼───────┼───────┼───────┤                                     ├───────┼───────┼───────┼───────┤       │(OLED2)│
//          ├───────┼───────┤       │       │       │       │                                     │       │StrtStp│eepr#AG│       ├───────┼───────┤
//          │       │       │ Hue↓  │ Sat↓  │ Val↓  │Speed↓ │                                     │Bright↓│Pomodo │CyclAni│       │       │       │
//    Row 2 │ Plain │ Mode← │ (RGB) │ (RGB) │ (RGB) │ (RGB) │                                     │       │(OLED2)│(OLED2)│       │       │InitAni│
//          │ (RGB) │ (RGB) ├───────┼───────┼───────┼───────┤    1      2            1      2     ├───────┼───────┼───────┼───────┤       │(OLED2)│
//          ├───────┼───────┤       │       │       │       │┌───────┬───────┐   ┌───────┬───────┐│       │       │       │       ├───────┼───────┤
//          │       │       │ Unix  │ Win   │ WinC  │ Mac   ││       │       │   │       │       ││       │       │       │       │       │       │
//    Row 3 │Toggle │Cycle  │Unicode│Unicode│Unicode│Unicode││  ___  │  ___  │   │  ___  │  ___  ││       │       │       │       │       │Reset  │
//          │Unicode│Unicode├───────┴───────┴───────┴───────┘│       │       │   │       │       │└───────┴───────┴───────┴───────┤       │eeprom │
//          └───────┴───────┘     ▄▄▄▄▄▄▄┌───────┬───────┬───┴───┬───┴───┬───┘   └───┬───┴───┬───┴───┬───────┬───────┐▄▄▄▄▄▄▄     └───────┴───────┘
//                               ▐       ▌       │       │       │       │           │       │       │       │       ▐       ▌
//                   Thumb row 2 ▐ Mute  ▌  ___  │  ___  │  ___  │  ___  │           │  ___  │  ___  │  ___  │  ___  ▐ Play  ▌
//                               ▐ ↑↓Vol ▌       │       │       │       │           │       │       │       │       ▐←→Track▌
//                                ▀▀▀▀▀▀▀└───────┴───────┴───────┴───────┘           └───────┴───────┴───────┴───────┘▀▀▀▀▀▀▀
//                                   1       2       3       4       5                   1       2       3       4       5
//

#define MEDIA_RGB_ROW1_LEFT        C_RGB_TOGGLE,       RGB_MODE_FORWARD,     RGB_HUI,            RGB_SAI,          RGB_VAI,           RGB_SPI,
#define MEDIA_RGB_ROW2_LEFT        RGB_MODE_PLAIN,     RGB_MODE_REVERSE,     RGB_HUD,            RGB_SAD,          RGB_VAD,           RGB_SPD,
#define MEDIA_RGB_ROW3_LEFT        C_TOGGLE_UNICODE,   UNICODE_MODE_FORWARD, UNICODE_MODE_LNX,   UNICODE_MODE_WIN, UNICODE_MODE_WINC, UNICODE_MODE_MAC,

#define MEDIA_RGB_ROW1_RIGHT       KC_BRIGHTNESS_UP,   XXXXXXX,              XXXXXXX,            XXXXXXX,          XXXXXXX,           C_OLED2_TOGGLE,
#define MEDIA_RGB_ROW2_RIGHT       KC_BRIGHTNESS_DOWN, C_POMODORO_TOGGLE,    C_OLED2_ANIM_CYCLE, XXXXXXX,          XXXXXXX,           C_OLED2_REINIT,
#define MEDIA_RGB_ROW3_RIGHT       XXXXXXX,            XXXXXXX,              XXXXXXX,            XXXXXXX,          XXXXXXX,           C_RESET_EEPROM,

#define MEDIA_RGB_THUMB_ROW1_LEFT                                   _______, _______,
#define MEDIA_RGB_THUMB_ROW2_LEFT  KC_AUDIO_MUTE, _______, _______, _______, _______,
#define MEDIA_RGB_THUMB_ROW1_RIGHT _______,       _______,
#define MEDIA_RGB_THUMB_ROW2_RIGHT _______,       _______, _______, _______, KC_MEDIA_PLAY_PAUSE

/*
//----------------
// Layer TEMPLATE
//----------------
#define TEMPLATE_ROW1_LEFT        _______, _______, _______, _______, _______, _______,
#define TEMPLATE_ROW2_LEFT        _______, _______, _______, _______, _______, _______,
#define TEMPLATE_ROW3_LEFT        _______, _______, _______, _______, _______, _______,

#define TEMPLATE_ROW1_RIGHT       _______, _______, _______, _______, _______, _______,
#define TEMPLATE_ROW2_RIGHT       _______, _______, _______, _______, _______, _______,
#define TEMPLATE_ROW3_RIGHT       _______, _______, _______, _______, _______, _______,

#define TEMPLATE_THUMB_ROW1_LEFT                             _______, _______,
#define TEMPLATE_THUMB_ROW2_LEFT  _______, _______, _______, _______, _______,
#define TEMPLATE_THUMB_ROW1_RIGHT _______, _______,
#define TEMPLATE_THUMB_ROW2_RIGHT _______, _______, _______, _______, _______
*/
