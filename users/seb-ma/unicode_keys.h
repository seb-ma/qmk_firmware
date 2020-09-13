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
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)

#include "custom_keys.h"

#ifdef UNICODEMAP_ENABLE
    // Call to UNICODEMAP macro X() instead of UNICODE macro UC() when UNICODEMAP_ENABLE is enabled
#   define UC(k) X(k)

/* List of unicode-extended characters */
enum unicode_names {
    BANG,
    IRONY,
};

/* Code of unicode-extended characters */
const uint32_t unicode_map[] PROGMEM = {
    [BANG]        = 0x203D, // ‽
    [IRONY]       = 0x2E2E, // ⸮
    [ARRAY_LEFT]  = 0x2190, // ←
    [ARRAY_RIGHT] = 0x2192, // →
};

#endif // UNICODEMAP_ENABLE

/* List of mapping between keys in layout and related UNICODE characters */
key_mod_full_map_t unicode_mod_full_map[] PROGMEM = {
    //keycode, key, key_shift, key_altgr, key_shift_altgr

    // Row 1
    {BP_DLR,  UC(L'$'),  UC(L'#'), UC(L'–'),  UC(L'¶')}, // $        #        –        ¶
    {BP_DQUO, UC(L'"'),  UC_1,     UC(L'—'),  UC(L'„')}, // "        1        —        „
    {BP_LDAQ, UC(L'«'),  UC_2,     UC(L'<'),  UC(L'“')}, // «        2        <        “
    {BP_RDAQ, UC(L'»'),  UC_3,     UC(L'>'),  UC(L'”')}, // »        3        >        ”
    {BP_LPRN, UC(L'('),  UC_4,     UC(L'['),  UC(L'≤')}, // (        4        [        ≤
    {BP_RPRN, UC(L')'),  UC_5,     UC(L']'),  UC(L'≥')}, // )        5        ]        ≥
    {BP_AT,   UC(L'@'),  UC_6,     UC(L'^'),  C_DUMMY }, // @        6        ^
    {BP_PLUS, UC(L'+'),  UC_7,     UC(L'±'),  UC(L'¬')}, // +        7        ±        ¬
    {BP_MINS, UC(L'-'),  UC_8,     UC(L'−'),  UC(L'¼')}, // -        8        −        ¼
    {BP_SLSH, UC(L'/'),  UC_9,     UC(L'÷'),  UC(L'½')}, // /        9        ÷        ½
    {BP_ASTR, UC(L'*'),  UC_0,     UC(L'×'),  UC(L'¾')}, // *        0        ×        ¾
    {BP_EQL,  UC(L'='),  UC(L'°'), UC(L'≠'),  UC(L'′')}, // =        °        ≠        ′
    {BP_PERC, UC(L'%'),  UC(L'`'), UC(L'‰'),  UC(L'″')}, // %        `        ‰        ″
    // Row 2
    {BP_B,    UC_b,      UC_B,     UC(L'|'),  UC(L'¦')}, // b        B        |        ¦
    {BP_EACU, UC(L'é'),  UC(L'É'), UC(L'´'),  UC(L'˝')}, // é        É        ´ (dead) ˝ (dead)
    {BP_P,    UC_P,      UC_P,     UC(L'&'),  UC(L'§')}, // p        P        &        §
    {BP_O,    UC_o,      UC_O,     UC(L'œ'),  UC(L'Œ')}, // o        O        œ        Œ
    {BP_EGRV, UC(L'è'),  UC(L'È'), UC(L'`'),  C_DUMMY }, // è        È        ` (dead)
    {BP_DCIR, UC(L'^'),  UC(L'!'), X(BANG),   C_DUMMY }, // ^ (dead) !        ‽
    {BP_V,    UC_v,      UC_V,     UC(L'ˇ'),  C_DUMMY }, // v        V        ˇ (dead)
    {BP_D,    UC_d,      UC_D,     UC(L'ð'),  UC(L'Ð')}, // d        D        ð        Ð
    {BP_L,    UC_l,      UC_L,     UC(L'/'),  C_DUMMY }, // l        L        / (dead)
    {BP_J,    UC_j,      UC_J,     UC(L'ĳ'),  UC(L'Ĳ')}, // j        J        ĳ        Ĳ
    {BP_Z,    UC_z,      UC_Z,     UC(L'ə'),  UC(L'Ə')}, // z        Z        ə        Ə
    {BP_W,    UC_w,      UC_W,     UC(L'˘'),  C_DUMMY }, // w        W        ˘ (dead)
    // Row 3
    {BP_A,    UC_a,      UC_A,     UC(L'æ'),  UC(L'Æ')}, // a        A        æ        Æ
    {BP_U,    UC_u,      UC_U,     UC(L'ù'),  UC(L'Ù')}, // u        U        ù        Ù
    {BP_I,    UC_i,      UC_I,     UC(L'¨'),  UC(L'˙')}, // i        I        ¨ (dead) ˙ (dead)
    {BP_E,    UC_e,      UC_E,     UC(L'€'),  UC(L'¤')}, // e        E        €        ¤ (dead)
    {BP_COMM, UC_COMM,   UC(L';'), UC(L'’'),  UC(L' ')}, // ,        ;        ’        ̛  (dead)
    {BP_C,    UC_c,      UC_C,     UC(L'©'),  UC(L'ſ')}, // c        C        ©        ſ
    {BP_T,    UC_t,      UC_T,     UC(L'Þ'),  C_DUMMY }, // t        T        Þ
    {BP_S,    UC_s,      UC_S,     UC(L'ẞ'),  C_DUMMY }, // s        S        ẞ
    {BP_R,    UC_r,      UC_R,     UC(L'®'),  UC(L'™')}, // r        R        ®        ™
    {BP_N,    UC_n,      UC_N,     UC(L'~'),  C_DUMMY }, // n        N        ~ (dead)
    {BP_M,    UC_m,      UC_M,     UC(L'¯'),  UC(L'º')}, // m        M        ¯ (dead) º
    {BP_CCED, UC(L'ç'),  UC(L'Ç'), UC(L'¸'),  UC(L',')}, // ç        Ç        ¸ (dead) , (dead)
    // Row 4
    {BP_ECIR, UC(L'ê'),  UC(L'Ê'), UC(L'/'),  C_DUMMY }, // ê        Ê        /
    {BP_AGRV, UC(L'à'),  UC(L'À'), UC(L'\\'), C_DUMMY }, // à        À        \ (backslash)
    {BP_Y,    UC_y,      UC_Y,     UC(L'{'),  UC(L'‘')}, // y        Y        {        ‘
    {BP_X,    UC_x,      UC_X,     UC(L'}'),  UC(L'’')}, // x        X        }        ’
    {BP_DOT,  UC_DOT,    UC(L':'), UC(L'…'),  UC(L'·')}, // .        :        …        ·
    {BP_K,    UC_k,      UC_K,     UC(L'~'),  UC(L'⌨')}, // k        K        ~        ⌨
    {BP_QUOT, UC_QUOT,   UC(L'?'), X(IRONY),  C_DUMMY }, // '        ?        ⸮          ̉ (dead)
    {BP_Q,    UC_q,      UC_Q,     UC(L'°'),  C_DUMMY }, // q        Q        ° (dead)  ̣ (dead)
    {BP_G,    UC_g,      UC_G,     UC(L'µ'),  C_DUMMY }, // g        G        µ (dead Greek key)
    {BP_H,    UC_h,      UC_H,     UC(L'†'),  UC(L'‡')}, // h        H        †        ‡
    {BP_F,    UC_f,      UC_F,     UC(L'˛'),  UC(L'ª')}, // f        F        ˛ (dead) ª
    // Row 5 & misc
    {KC_SPACE,UC_SPC,    UC(L' '), UC(L'_'),  UC(L' ')}, // (space) (non-breaking space) _  (narrow non-breaking space)
    {KC_BSPC, UC_BSPC,   C_DUMMY,  C_DUMMY,   C_DUMMY},
    {KC_TAB,  UC(L'\t'), C_DUMMY,  C_DUMMY,   C_DUMMY},
    {KC_DEL,  UC_DEL,    C_DUMMY,  C_DUMMY,   C_DUMMY},
};

#endif // defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
