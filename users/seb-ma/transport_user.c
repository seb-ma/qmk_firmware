#include QMK_KEYBOARD_H
#include "transport_user.h"

/* Data user transmitted from master halve to follower */
user_data_m2s_t user_data_m2s;

#ifdef TRANSPORT_USER_DATA

/* To be called in transport layer (function transport_master) to transmit user data from master to follower */
uint32_t get_user_data_m2s_user(void) {
    return user_data_m2s.raw;
}

/* To be called in transport layer (function transport_slave) to store user data from master to follower */
void set_user_data_m2s_user(uint32_t user_data) {
    user_data_m2s.raw = user_data;
}

#endif // TRANSPORT_USER_DATA
