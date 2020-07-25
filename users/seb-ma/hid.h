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
