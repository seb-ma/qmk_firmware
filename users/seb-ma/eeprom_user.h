#pragma once
#include QMK_KEYBOARD_H

/* Structure of data user stored in eeprom */
typedef union {
    uint32_t raw;
    struct {
        bool     unicode      : 1; // UNICODE on or off
        bool     oled2        : 1; // OLED 2  on or off
        uint8_t  animation_idx: 3; // Index of animation to display
      //uint32_t unused       :27;
    };
} user_config_t;

/* Data user stored in eeprom */
extern user_config_t user_config;
