#ifdef RAW_ENABLE
#include "raw_hid.h"

#include "hid.h"

/* Data sent to host through HID */
hid_to_host_t hid_to_host;

/* Send status of the keyboard over HID interface */
void send_hid_status(const layer_state_t layer_state) {
    hid_to_host.command = HID_STATUS;
    hid_to_host.status.layer = get_highest_layer(layer_state);
    hid_to_host.status.state = host_keyboard_led_state();

    raw_hid_send(hid_to_host.raw, RAW_EPSIZE);
}

#endif // RAW_ENABLE
