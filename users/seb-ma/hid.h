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
#ifdef RAW_ENABLE
#include QMK_KEYBOARD_H

// Included for RAW_EPSIZE (=32)
#include "usb_descriptor.h"

/* List of command sent to host */
enum {
    HID_STATUS = 0,
} hid_command;

/* Structure of data sent to host through HID */
typedef union {
    uint8_t raw[RAW_EPSIZE];
    struct {
        uint8_t command;
        union {
            uint8_t data[RAW_EPSIZE - 1];
            /* HID_STATUS */
            struct {
                uint8_t layer;
                led_t   state;
            } status;
        };
    };
} hid_to_host_t;

/* Send status of the keyboard over HID interface */
void send_hid_status(const layer_state_t layer_state);

#endif // RAW_ENABLE
