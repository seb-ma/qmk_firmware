#pragma once

#include QMK_KEYBOARD_H

/* Structure of data user transmitted from master halve to follower */
typedef union {
    uint32_t raw;
    struct {
        bool    oled2                 : 1; // OLED 2 on or off
        uint8_t animation_idx         : 3; // Index of animation to display
        bool    anim_reinit_toggle    : 1; // Used as a trigger to reinit animation
        bool    pomodoro_reinit_toggle: 1; // Used as a trigger to reinit pomodoro timer
      //uint8_t unused                :26;
    };
} user_data_m2s_t;

/* Data user transmitted from master halve to follower */
extern user_data_m2s_t user_data_m2s;
