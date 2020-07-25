#include QMK_KEYBOARD_H
#include "eeprom_user.h"

/* Data user stored in EEPROM */
user_config_t user_config;

/* called when EEPROM is getting reset! */
void eeconfig_init_user(void) {
    user_config.raw = 0;

    user_config.unicode = false;
    user_config.oled2   = true;
    // Write default value to EEPROM now
    eeconfig_update_user(user_config.raw);
}
