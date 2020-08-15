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

/* Receive data over HID interface */
/*
void raw_hid_receive(uint8_t *data, uint8_t length) {

}
*/

#endif // RAW_ENABLE
