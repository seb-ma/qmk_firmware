#pragma once
#ifdef USER_CLOSE_CHAR
#include QMK_KEYBOARD_H

/* Handle the keys corresponding to an opening char: "(«[{
 Return the key itself or the first closing key if this is the special close key
*/
uint16_t handle_open_close_char(const uint16_t keycode, const bool ignore_mods, const keyrecord_t *const record, const uint16_t previous_keycode);

/* If keycode is a close char, push it to the buffer */
void closechar_push(const uint16_t keycode);

/* Pop the last close char from buffer */
uint16_t closechar_pop(void);

#endif // USER_CLOSE_CHAR
