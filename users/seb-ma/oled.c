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
#ifdef OLED_DRIVER_ENABLE
#include <stdio.h>

#include "custom_keys.h"
#include "dynamic_macros.h"
#include "eeprom_user.h"
#include "layers.h"
#include "leader.h"
#include "oled.h"
#include "oled_custom_font_constants.h"
#include "transport_user.h"


/* Pointers on function to render init frame of each animation */
render_init_frame_fct render_init[] = {
#   ifdef BONGOCAT_ANIMATION
    NULL,
#   endif
#   ifdef LIFE_ANIMATION
    NULL,
#   endif
#   ifdef POMODORO_ANIMATION
    NULL,
#   endif
#   ifdef ONEKO_ANIMATION
    NULL,
#   endif
#   ifdef STARFIELD_ANIMATION
    NULL,
#   endif
};

/* Number of animations available */
#   define NB_ANIMATIONS (sizeof(render_init) / sizeof(render_init_frame_fct))

#ifdef RENDER_ANIMATIONS

/* Declaration of the animation */
t_animation animation;

/* Timer for continuing animation before stopping OLED */
uint32_t timeout_animation = 0;

/* bi-state value used as a trigger to reinit animation */
static bool previous_anim_reinit_state;
/* Last index of animation displayed */
static uint8_t previous_anim_index;

/* Pointers on function to render next frame of each animation */
render_next_frame_fct render_next[NB_ANIMATIONS];

#endif // RENDER_ANIMATIONS

// Define if this compilation is with the pomodoro management
#if defined(POMODORO_TIMER) && ((defined(TRANSPORT_USER_DATA) && defined(FOLLOWER_ONLY)) || (!defined(TRANSPORT_USER_DATA) && !defined(FOLLOWER_ONLY)))
#   define POMODORO_SIDE
#endif

#ifdef POMODORO_SIDE
/* bi-state value used as a trigger to reinit pomodoro */
static bool previous_pomodoro_reinit_state;

uint32_t pomodoro_start_timer = 0;

#endif // POMODORO_SIDE


/* Callback (used by core) at the start of oled_init */
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#ifdef RENDER_ANIMATIONS
    uint8_t i = 0;
#   ifdef BONGOCAT_ANIMATION
    render_init[i]   = bongocat_render_init_frame;
    render_next[i++] = bongocat_render_next_frame;
#   endif
#   ifdef LIFE_ANIMATION
    render_init[i]   = gamelife_render_init_frame;
    render_next[i++] = gamelife_render_next_frame;
#   endif
#   ifdef POMODORO_ANIMATION
    render_init[i]   = pomodoro_render_init_frame;
    render_next[i++] = pomodoro_render_next_frame;
#   endif
#   ifdef ONEKO_ANIMATION
    render_init[i]   = oneko_render_init_frame;
    render_next[i++] = oneko_render_next_frame;
#   endif
#   ifdef STARFIELD_ANIMATION
    render_init[i]   = starfield_render_init_frame;
    render_next[i++] = starfield_render_next_frame;
#   endif

    previous_anim_reinit_state = !user_data_m2s.anim_reinit_toggle;
    previous_anim_index = -1;
#endif // RENDER_ANIMATIONS

#ifdef POMODORO_SIDE
    previous_pomodoro_reinit_state = user_data_m2s.pomodoro_reinit_toggle;
#endif

    return OLED_ROTATION_180;
}

/* Simple call to oled_write_P with nb ' ' */
void oled_write_space_nb(const uint8_t nb) {
    for (uint8_t i = 0; i < nb; ++i) {
       oled_write_P(PSTR(" "), false);
    }
}

#ifndef FOLLOWER_ONLY

/* Check if this is a custom rgb key and process it if true
 (To be called in process_record_user)
*/
bool handle_oled(const uint16_t keycode, keyrecord_t *const record) {
    if (record->event.pressed) {
        switch (keycode) {
#   ifdef TRANSPORT_USER_DATA
        case C_OLED2_STORE_EEPROM:
            user_config.oled2 = user_data_m2s.oled2;
            eeconfig_update_user(user_config.raw);
            return false;
        case C_OLED2_TOGGLE:
            user_data_m2s.oled2 = !user_data_m2s.oled2;
            return false;
        case C_OLED2_ANIMATION_STORE_EEPROM:
            user_config.animation_idx = user_data_m2s.animation_idx;
            eeconfig_update_user(user_config.raw);
            return false;
        case C_OLED2_ANIMATION_CYCLE:
            user_data_m2s.animation_idx = (user_data_m2s.animation_idx + 1) % MAX(1, NB_ANIMATIONS);
            // No break intended to execute next case (C_OLED2_REINIT) and reinit animation too
        case C_OLED2_REINIT:
            user_data_m2s.anim_reinit_toggle = !user_data_m2s.anim_reinit_toggle;
            return false;
#   endif // TRANSPORT_USER_DATA
#   ifdef POMODORO_TIMER
        case C_POMODORO_TOGGLE:
            user_data_m2s.pomodoro_reinit_toggle = !user_data_m2s.pomodoro_reinit_toggle;
            return false;
#   endif // POMODORO_TIMER
        }
    }
    return true;
}

/* Render logo of each item (from logos_2rows) */
void write_logo(const uint8_t logo, const uint8_t row) {
    oled_write_space_nb(1);
    oled_write_P(logos_2rows[logo][row], false);
    oled_write_space_nb(3);
}

/* Render the layers state */
void render_layer_state(void) {
    led_t state = host_keyboard_led_state();
    uint8_t logo = LOGO_LAYERS;
#   if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    if (user_config.unicode) {
        switch (get_unicode_input_mode()) {
        case UC_LNX:
            logo = LOGO_LINUX;
            break;
        case UC_OSX:
            logo = LOGO_MAC;
            break;
        case UC_WIN:
        case UC_WINC:
            logo = LOGO_WINDOWS;
            break;
        }
    }
#   endif // defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    uint8_t layer_high = get_highest_layer(layer_state);
    for (uint8_t i = 0; i < 2; i++) {
        write_logo(logo, i);
        if (i == 0) {
            oled_write_space_nb(4);
            // Display alpha logo lower or upper according to caps lock
            oled_write_P(logos_layers_lst[(layer_high == 0 && state.caps_lock) ? LAYERS_SIZE : layer_high], false); // 5
        }
        oled_advance_page(true);
    }
}

/* Render the modifiers state */
void render_mod_state(const uint8_t modifiers) {
    for (uint8_t i = 0; i < 2; i++) {
        write_logo(LOGO_MODS, i);
        const uint8_t idx = LOGO_SHIFT + 3 * i;
        oled_write_P(logos_1row[idx], modifiers & modifiers_val[3 * i]); // 3
        oled_write_space_nb(2);
        oled_write_P(logos_1row[idx + 1], modifiers & modifiers_val[3 * i + 1]); // 3
        oled_write_space_nb(2);
        if (i < 1) {
            oled_write_P(logos_1row[idx + 2], modifiers & modifiers_val[3 * i + 2]); // 3
        }
        oled_advance_page(true);
    }
}

/* Render status of leds on screen */
void render_leds_status(void) {
/*
    led_t state = host_keyboard_led_state();

    oled_write_P(PSTR("Lock:"), false);
    oled_write_space();
    oled_write_P(PSTR("Scr"), state.scroll_lock);
    oled_write_space();
    oled_write_ln_P(PSTR("Cmp"), state.compose);
*/
}

void oled_write_char_P(const char* progmemCharAddress, bool invert) {
    oled_write_char(pgm_read_byte(progmemCharAddress), invert);
}

#endif // FOLLOWER_ONLY

#ifdef DYNAMIC_MACRO_ENABLE
/* Render status of dynamic macros on screen */
void render_dynamic_macros(void) {
    for (uint8_t i = 0; i < 2; i++) {
        write_logo(LOGO_MACROS, i);
        oled_write_char_P(&(logos_layers_lst[_FUNC_NUM_SYMB][i]), false); //  Bold numbers "1" and "2" taken from representation of layer num/symb // 1
        // Keep playing only a defined time (no data to identify end of macro playing)
        if (timer_elapsed32(dyn_macros_state[i].timer_played) < DYNMACRO_STATE_DISPLAY_DURATION) {
            oled_write_space_nb(2);
            oled_write_P(logos_1row[LOGO_PLAY], false); // 2
        }
        if (dyn_macros_state[i].recording) {
            oled_write_space_nb(2);
            oled_write_P(logos_1row[LOGO_REC], false); // 2
        }
        // Keep warning only a defined time
        if (timer_elapsed32(dyn_macros_state[i].timer_last_error) < DYNMACRO_STATE_DISPLAY_DURATION) {
            oled_write_space_nb(2);
            oled_write_P(logos_1row[LOGO_WARN], false); // 2
        }
        oled_advance_page(true);
    }
}
#endif // DYNAMIC_MACRO_ENABLE

#ifdef LEADER_ENABLE
/* Render status of leader sequence on screen */
void render_leader(void) {
/*    write_logo(LOGO_LEADER, 0);
    oled_advance_page(true);
    write_logo(LOGO_LEADER, 1);
    if (timer_elapsed(leader_state.timer) < LEADER_STATE_DISPLAY_DURATION) {
        oled_write_P(leader_state.name, false);
        if (!leader_state.is_success) {
            oled_write_space_nb(1);
            oled_write_P(logos_1row[LOGO_WARN], true); // 2
        }
    } else {
        oled_write_P(PSTR("None"), false);
    }
    oled_advance_page(true);
*/}
#endif // LEADER_ENABLE

/* Render all the status of the keyboard (21 cols × 8 rows)
It looks like (with inverted color when element is selected):
      1                   21
     ┌─────────────────────┐
    1│ LAY    Hightest     │
     │ LAY   Active Layer  │
     │                     │
     │ MOD   Sft  Ctl  Gui │
     │ MOD   Alt  AlG      │
     │                     │
     │ DYM   1  Pl  Rc  Wn │
    8│ DYM   2  Pl  Rc  Wn │
     └─────────────────────┘
*/
void render_status(void) {
#ifndef FOLLOWER_ONLY
    render_layer_state();
    oled_advance_page(true);
#   ifdef NO_ACTION_ONESHOT
    render_mod_state(get_mods());
#   else
    render_mod_state(get_mods() | get_oneshot_mods());
#   endif
#   ifdef DYNAMIC_MACRO_ENABLE
    oled_advance_page(true);
    render_dynamic_macros();
#   endif
#   ifdef LEADER_ENABLE
    render_leader();
#   endif
    render_leds_status();
#endif // FOLLOWER_ONLY
}

#ifdef RENDER_ANIMATIONS
/* Render the defined animation */
void render_animation(void) {
    if (animation.ratioPerc != -1) {
#   ifdef WPM_ENABLE
        // Compute the ratio to apply to pace animation based on current word per minute typping
        animation.ratioPerc = (get_current_wpm() == 0) ? 0 : MIN(animation.frame_duration_max, MAX(animation.frame_duration_min, 100 * get_current_wpm() / STANDARD_WPM));
#   else
        animation.ratioPerc = -1;
#   endif
    }

#   ifdef WPM_ENABLE
    // Switch off if timeout without key pressed and no pomodoro running
    // XXX: Find a clean way to have key press detection without WPM_ENABLE (add it to custom transport)
    if (get_current_wpm() > 0
#       ifdef POMODORO_SIDE
        || pomodoro_start_timer != 0
#       endif // POMODORO_SIDE
    ) {
        timeout_animation = timer_read32();
    } else if (timer_elapsed32(timeout_animation) > OLED_TIMEOUT) {
        oled_off();
        return;
    }
#   endif

    if (user_data_m2s.anim_reinit_toggle != previous_anim_reinit_state
    || user_data_m2s.animation_idx != previous_anim_index) {
        // Restart animation
        previous_anim_reinit_state = user_data_m2s.anim_reinit_toggle;
        previous_anim_index = user_data_m2s.animation_idx;
        oled_clear();
        render_init[user_data_m2s.animation_idx](&animation);
    } else if ((animation.ratioPerc <= 0 && timer_elapsed32(animation.start_timer) > animation.frame_duration)
            || (animation.ratioPerc > 0  && timer_elapsed32(animation.start_timer) > animation.frame_duration * 100 / animation.ratioPerc)) {
        // Renders next frame of the animation if time's up
        render_next[user_data_m2s.animation_idx](&animation);
    }
}
#endif // RENDER_ANIMATIONS

#ifdef POMODORO_SIDE

/* Display the pomodoro timer */
void render_pomodoro(void) {
    oled_set_cursor(0, 7);
    // Handle the toggle command
    if (previous_pomodoro_reinit_state != user_data_m2s.pomodoro_reinit_toggle) {
        previous_pomodoro_reinit_state = user_data_m2s.pomodoro_reinit_toggle;
        // Reinit display
        render_init[user_data_m2s.animation_idx](&animation);
        if (pomodoro_start_timer == 0) {
            pomodoro_start_timer = timer_read32();
        } else {
            pomodoro_start_timer = 0;
            oled_write_space_nb(7);
        }
    }
    // A timer is running
    if (pomodoro_start_timer != 0) {
        const uint32_t time_s = MAX(0, (POMODORO_TIMER * 60) - (timer_elapsed32(pomodoro_start_timer) / 1000));
        char pomodoro_str[6];
        oled_write_P(logos_1row[LOGO_POMODORO], time_s == 0); // 2
        sprintf(pomodoro_str, "%02lu:%02lu", time_s / 60, time_s % 60);
        oled_write(pomodoro_str, time_s == 0); // 5
        if (time_s == 0) {
            pomodoro_start_timer = 0;
        }
    }
}

#endif // POMODORO_SIDE

/* Callback (used by core) to handle screen displaying */
void oled_task_user(void) {
    if (is_keyboard_master()) {
        // Renders the current keyboard state (layers, modifiers...)
        render_status();
#ifdef POMODORO_SIDE
        render_pomodoro();
#endif
    } else if (user_data_m2s.oled2) {
#ifdef RENDER_ANIMATIONS
        // Renders the animation
        render_animation();
#endif
#ifdef POMODORO_SIDE
        render_pomodoro();
#endif
    } else {
        oled_off();
    }
}

#endif // OLED_DRIVER_ENABLE
