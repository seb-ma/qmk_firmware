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
#ifdef OLED_DRIVER_ENABLE

/* List of position of first char of each item */
#define FONT_OFF_LINE      0x20 // Number of chars on 1 line
// First custom line in font
#define FONT_POS_LAYERS_1  0x80
#define FONT_POS_WIN_1     (FONT_POS_LAYERS_1  + 3)
#define FONT_POS_LINUX_1   (FONT_POS_WIN_1   + 2)
#define FONT_POS_MAC_1     (FONT_POS_LINUX_1   + 2)
#define FONT_POS_MODS_1    (FONT_POS_MAC_1     + 2)
#define FONT_POS_MACROS_1  (FONT_POS_MODS_1    + 3)
#define FONT_POS_ALPHA_L   (FONT_POS_MACROS_1  + 3)
#define FONT_POS_NUMS      (FONT_POS_ALPHA_L   + 5)
#define FONT_POS_NAV       (FONT_POS_NUMS      + 5)
#define FONT_POS_MEDIAS    (FONT_POS_NAV       + 4)
// Second custom line in font
#define FONT_POS_LAYERS_2  (FONT_POS_LAYERS_1  + FONT_OFF_LINE)
#define FONT_POS_WIN_2     (FONT_POS_WIN_1     + FONT_OFF_LINE)
#define FONT_POS_LINUX_2   (FONT_POS_LINUX_1   + FONT_OFF_LINE)
#define FONT_POS_MAC_2     (FONT_POS_MAC_1     + FONT_OFF_LINE)
#define FONT_POS_MODS_2    (FONT_POS_MODS_1    + FONT_OFF_LINE)
#define FONT_POS_MACROS_2  (FONT_POS_MACROS_1  + FONT_OFF_LINE)
#define FONT_POS_ALPHA_H   (FONT_POS_ALPHA_L   + FONT_OFF_LINE)
#define FONT_POS_SHORTCUTS (FONT_POS_ALPHA_H   + 5)
#define FONT_POS_WARN      (FONT_POS_SHORTCUTS + 4)
#define FONT_POS_PLAY      (FONT_POS_WARN      + 2)
#define FONT_POS_REC       (FONT_POS_PLAY      + 2)
#define FONT_POS_SHIFT     (FONT_POS_REC       + 2)
#define FONT_POS_ALT       (FONT_POS_SHIFT     + 2)
#define FONT_POS_GUI       (FONT_POS_ALT       + 2)
// Third custom line in font
#define FONT_POS_CTRL      (FONT_POS_GUI       + 2)
#define FONT_POS_ALTGR     (FONT_POS_CTRL      + 3)
#define FONT_POS_POMODORO  (FONT_POS_ALTGR     + 3)


#ifndef FOLLOWER_ONLY

/* List of logos drawn on 2 rows */
enum logos_2rows {
    LOGO_LAYERS = 0,
    LOGO_MODS,
    LOGO_MACROS,
#   if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    LOGO_LINUX,
    LOGO_MAC,
    LOGO_WINDOWS,
#   endif

    LOGO_SIZE_2R
};

/* Representation of each item (on 2 rows) - must be in same order as in enum logos_2rows
 Values are char position in oled_custom_font.c */
static const char logos_2rows[][LOGO_SIZE_2R][4] PROGMEM = {
    {{FONT_POS_LAYERS_1, FONT_POS_LAYERS_1 + 1, FONT_POS_LAYERS_1 + 2, 0}, {FONT_POS_LAYERS_2, FONT_POS_LAYERS_2 + 1, FONT_POS_LAYERS_2 + 2, 0}}, // Layers
    {{FONT_POS_MODS_1,   FONT_POS_MODS_1   + 1, FONT_POS_MODS_1   + 2, 0}, {FONT_POS_MODS_2,   FONT_POS_MODS_2   + 1, FONT_POS_MODS_2   + 2, 0}}, // Modifiers
    {{FONT_POS_MACROS_1, FONT_POS_MACROS_1 + 1, FONT_POS_MACROS_1 + 2, 0}, {FONT_POS_MACROS_2, FONT_POS_MACROS_2 + 1, FONT_POS_MACROS_2 + 2, 0}}, // Dynamic macros
#   if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    {{FONT_POS_LINUX_1,  FONT_POS_LINUX_1 + 1,  0,                     0}, {FONT_POS_LINUX_2,  FONT_POS_LINUX_2  + 1, 0,                     0}}, // Layers
    {{FONT_POS_MAC_1,    FONT_POS_MAC_1   + 1,  0,                     0}, {FONT_POS_MAC_2,    FONT_POS_MAC_2    + 1, 0,                     0}}, // Layers
    {{FONT_POS_WIN_1,    FONT_POS_WIN_1   + 1,  0,                     0}, {FONT_POS_WIN_2,    FONT_POS_WIN_2    + 1, 0,                     0}}, // Layers
#   endif
};


/* Representation of layers (must be in same order as in enum layers)
 Values are char position in oled_custom_font.c */
static const char logos_layers_lst[LAYERS_SIZE + 1][6] PROGMEM = {
    // Layers
    {FONT_POS_ALPHA_L,   FONT_POS_ALPHA_L   + 1, FONT_POS_ALPHA_L   + 2, FONT_POS_ALPHA_L + 3,   FONT_POS_ALPHA_L + 4, 0}, // alpha
    {FONT_POS_NUMS,      FONT_POS_NUMS      + 1, FONT_POS_NUMS      + 2, FONT_POS_NUMS    + 3,   FONT_POS_NUMS    + 4, 0}, // num/symb
    {FONT_POS_NAV,       FONT_POS_NAV       + 1, FONT_POS_NAV       + 2, FONT_POS_NAV     + 3,   0x20,                 0}, // nav/mouse
    {FONT_POS_MEDIAS,    FONT_POS_MEDIAS    + 1, FONT_POS_MEDIAS    + 2, 0x20,                   0x20,                 0}, // media/rgb
    {FONT_POS_SHORTCUTS, FONT_POS_SHORTCUTS + 1, FONT_POS_SHORTCUTS + 2, FONT_POS_SHORTCUTS + 3, 0x20,                 0}, // shortcuts

    // Extras
    {FONT_POS_ALPHA_H, FONT_POS_ALPHA_H + 1, FONT_POS_ALPHA_H + 2, FONT_POS_ALPHA_H + 3, FONT_POS_ALPHA_H + 4, 0}, // alpha caps lock (at index LAYER_SIZE)
};

/* List of modifiers mask to check (modifiers must be in same order as logos_1row from LOGO_SHIFT) */
static const uint8_t modifiers_val[] PROGMEM = {
    MOD_MASK_SHIFT, MOD_MASK_CTRL, MOD_MASK_GUI, MOD_BIT(KC_LALT), MOD_BIT(KC_RALT),
};

#endif // FOLLOWER_ONLY


/* List of logos drawn on 1 row */
enum logos_1row {
#ifndef FOLLOWER_ONLY
    // Modifiers
    LOGO_SHIFT = 0,
    LOGO_CTRL,
    LOGO_GUI,
    LOGO_ALT,
    LOGO_ALTGR,
    // Others
#   ifdef DYNAMIC_MACRO_ENABLE
    LOGO_WARN,
    LOGO_PLAY,
    LOGO_REC,
#   endif // DYNAMIC_MACRO_ENABLE
#endif // FOLLOWER_ONLY
#ifdef POMODORO_TIMER
    LOGO_POMODORO,
#endif // POMODORO_TIMER
    LOGO_SIZE_1R
};


#if !defined(FOLLOWER_ONLY) || defined(POMODORO_TIMER)
/* Representation of modifiers (and others symbols) (must be same in order as in logos_1row)
 Values are char position in oled_custom_font.c */
static const char logos_1row[LOGO_SIZE_1R][4] PROGMEM = {
#   ifndef FOLLOWER_ONLY
    // Modifiers
    {FONT_POS_SHIFT, FONT_POS_SHIFT + 1, 0,                  0}, // shift
    {FONT_POS_CTRL,  FONT_POS_CTRL  + 1, FONT_POS_CTRL  + 2, 0}, // ctrl
    {FONT_POS_GUI,   FONT_POS_GUI   + 1, 0,                  0}, // gui
    {FONT_POS_ALT,   FONT_POS_ALT   + 1, 0,                  0}, // alt
    {FONT_POS_ALTGR, FONT_POS_ALTGR + 1, FONT_POS_ALTGR + 2, 0}, // altgr
    // Others
#       ifdef DYNAMIC_MACRO_ENABLE
    {FONT_POS_WARN,  FONT_POS_WARN  + 1, 0,                  0}, // Warn
    {FONT_POS_PLAY,  FONT_POS_PLAY  + 1, 0,                  0}, // Play
    {FONT_POS_REC,   FONT_POS_REC   + 1, 0,                  0}, // Rec
#       endif // DYNAMIC_MACRO_ENABLE
#   endif // FOLLOWER_ONLY
#   ifdef POMODORO_TIMER
    {FONT_POS_POMODORO, FONT_POS_POMODORO + 1, 0,            0}, // Pomodoro
#   endif // POMODORO_TIMER
};
#endif // !defined(FOLLOWER_ONLY) || defined(POMODORO_TIMER)

#endif // OLED_DRIVER_ENABLE
