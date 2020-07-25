#pragma once
#ifdef USER_ADDING_NBSP
#include QMK_KEYBOARD_H

/* Indicates if a non-breakable space must be added (according to holding modifier) */
extern bool mod_hold_nb_sp;

/* Add a non breaking space when typping some chars: ;:!?«» */
uint16_t handle_adding_non_breaking_space(const uint16_t keycode, const bool ignore_mods, const keyrecord_t *const record);

#endif // USER_ADDING_NBSP
