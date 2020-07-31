#pragma once

//-----------------------------
// User features configuration
//-----------------------------

#ifndef FOLLOWER_ONLY
#   define USER_CLOSE_CHAR                 // Store opening chars "(«[{ and get relating close char in reverse order with a special key
#   ifdef USER_CLOSE_CHAR
#       define MAX_CLOSE_CHAR           16 // Max number of closing char to store
#   endif
#endif // FOLLOWER_ONLY

#ifdef DYNAMIC_MACRO_ENABLE
#   define DYNMACRO_STATE_DISPLAY_DURATION 1000 // Duration of displayed information on screen for dynamic macros status
#endif
#ifdef LEADER_ENABLE
#   define LEADER_STATE_DISPLAY_DURATION   1000 // Duration of displayed information on screen for leader key status
#endif

#ifdef OLED_DRIVER_ENABLE
#   define OLED_TIMEOUT         300000 // Delay before swiching off OLED (in ms) 300000 -> 5min
#   define STANDARD_WPM             50 // Number of typed word per minute to consider standard pace of the animation

    // non light version: add animations
#   if !defined(HALVE_BOTH_LIGHT)
        // Include modification of buffer used between master and follower to transmit data (currently a single uint8_t)
        // Thus, it can't work alone, modifications in struct _Serial_m2s_buffer_t (for serial protocol) and functions transport_master and transport_slave are needed
#       define TRANSPORT_USER_DATA
#       define POMODORO_TIMER           25 // If defined: activate a pomodoro timer on follower screen (time in minutes)

#       define BONGOCAT_ANIMATION          // Render bongo cat animation on follower screen
#       define ONEKO_ANIMATION             // Render Oneko (walking cat) animation on follower screen
#       define LIFE_ANIMATION              // Render game of life animation on follower screen
#       if defined(POMODORO_TIMER) && defined(TRANSPORT_USER_DATA)
#           define POMODORO_ANIMATION      // Render pomodoro animation on follower screen
#       endif
#   endif
#endif // OLED_DRIVER_ENABLE


//----------------------------
// QMK features configuration
//----------------------------

#undef LOCKING_SUPPORT_ENABLE           // Usefull only for mechanical lock switches

#define PERMISSIVE_HOLD                 // Makes tap and hold keys work better for fast typists, or when you’ve set TAPPING_TERM to a high value
#define TAPPING_TERM                200 // How long before a tap becomes a hold, if set above 500, a key tapped during the tapping term will turn it into a hold too
//#define IGNORE_MOD_TAP_INTERRUPT      // Prevent normal rollover on alphas from accidentally triggering mods.
//#define TAPPING_FORCE_HOLD            // This prevents accidental repeats of the tap-hold keys when typing quickly.

#define TAPPING_TOGGLE                1 // How many taps before triggering the layer toggle

// Allows media codes to properly register in macros and rotary encoder code
#define TAP_CODE_DELAY               10 // Sets the delay between register_code and unregister_code

// Combo
#ifdef COMBO_ENABLE
#   ifndef NO_SECRETS
#       define NB_COMBO_SECRETS      2 // Number of existing combos related to !NO_SECRETS
#   else
#       define NB_COMBO_SECRETS      0
#   endif

#   define COMBO_COUNT             (27 + NB_COMBO_SECRETS) // Number of existing combos
#   define COMBO_TERM               40 // Set the time out period for combos in ms
#endif // COMBO_ENABLE

// Leader key
#ifdef LEADER_ENABLE
#   define LEADER_PER_KEY_TIMING       // Enable per key timing rather than whole sequence
#   define LEADER_TIMEOUT          250 // Time (in ms) before aborting sequence
#endif // LEADER_ENABLE

// Dynamic macros
#ifdef DYNAMIC_MACRO_ENABLE
#   define DYNAMIC_MACRO_SIZE      64 // Sets the amount of memory that Dynamic Macros can use (default is 128)
#endif // DYNAMIC_MACRO_ENABLE

// One shot tap
#define NO_ACTION_ONESHOT               // Disable one-shot modifiers
#ifndef NO_ACTION_ONESHOT
#   define ONESHOT_TAP_TOGGLE        3 // Tapping this number of times holds the key until tapped once again
#   define ONESHOT_TIMEOUT        3000 // Time (in ms) before the one shot key is released
#endif // NO_ACTION_ONESHOT

#ifdef OLED_DRIVER_ENABLE
#   define OLED_FONT_H   "oled_custom_font.c" // Font code file to use for custom characters
#   define OLED_FONT_END                  199 // Number of characters in custom font
#endif // OLED_DRIVER_ENABLE

#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
#   define UNICODE_SELECTED_MODES UC_LNX, UC_WIN, UC_WINC, UC_MAC // Unicode modes to cycle
#endif

// RGB
#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_LAYERS             // Lets define lighting layers that can be toggled on or off. Great for showing the current keyboard layer or caps lock state.
#   ifdef RGBLIGHT_LAYERS
#       define RGBLIGHT_MAX_LAYERS   7 // Can be expanded up to 32 if more lighting layers are needed.
#       if (RGBLIGHT_MAX_LAYERS <= 8)  // Reduce structures size of rgb layers from 32 to 16 or 8 bits if possible
#           define LAYER_STATE_8BIT
#       elif (RGBLIGHT_MAX_LAYERS <= 16)
#           define LAYER_STATE_16BIT
#       endif

#       define RGBLIGHT_LAYER_BLINK    // Ability to blink a lighting layer for a duration
#   endif // RGBLIGHT_LAYERS

#   define RGBLIGHT_SLEEP              // If defined, the RGB lighting will be switched off when the host goes to sleep
#   define RGBLIGHT_HUE_STEP         8 // The number of steps to cycle through the hue by
#   define RGBLIGHT_SAT_STEP         8 // The number of steps to increment the saturation by
#   define RGBLIGHT_VAL_STEP         8 // The number of steps to increment the brightness by
//# define RGBLIGHT_LIMIT_VAL      255 // The maximum brightness level

#   ifndef HALVE_BOTH_LIGHT
#       define RGBLIGHT_ANIMATIONS     // Enable all additional animation modes (!! high memory footprint !! - undef it and use selective define RGBLIGHT_EFFECT_xxxx to reduce space used)
#   endif
#endif // RGBLIGHT_ENABLE

#ifdef FOLLOWER_ONLY
#   define NO_ACTION_LAYER             // Disable layers
#   define NO_ACTION_TAPPING           // Disable tap dance and other tapping features
#   define NO_ACTION_ONESHOT           // Disable one-shot modifiers
#endif // FOLLOWER_ONLY

// Mouse
#ifdef MOUSEKEY_ENABLE
    /* Adjust the cursor and scrolling acceleration */
    // Set the mouse settings to a comfortable speed/accuracy trade-off
    // Assume the screen refresh rate is 60 Htz or higher
    // The default is 50. This makes the mouse ~3 times faster and more accurate
#   define MOUSEKEY_INTERVAL            16 // Time between cursor movements
//#   define MOUSEKEY_MAX_SPEED         10 // Maximum cursor speed at which acceleration stops
    // The default is 20. Since we made the mouse about 3 times faster with the previous setting,
    // give it more time to accelerate to max speed to retain precise control over short distances.
#   define MOUSEKEY_TIME_TO_MAX         40 // Time until maximum cursor speed is reached
#   define MOUSEKEY_DELAY              100 // Delay between pressing a movement key and cursor movement
#   define MOUSEKEY_WHEEL_DELAY        100 // Delay between pressing a wheel key and wheel movement (use the same delay than mousekey)
#   define MOUSEKEY_WHEEL_INTERVAL      50 // Time between wheel movements (The default is 100)
//#   define MOUSEKEY_WHEEL_MAX_SPEED    8 // Maximum number of scroll steps per scroll action
#   define MOUSEKEY_WHEEL_TIME_TO_MAX  100 // Time until maximum scroll speed is reached (The default is 40)

/* Adjust cursor movement or scrolling */
//#   define MK_3_SPEED                    // Enable constant cursor speeds
//#   define MK_MOMENTARY_ACCEL            // Enable momentary speed selection
//#   define MK_C_OFFSET_UNMOD          16 // Cursor offset per movement (unmodified)
//#   define MK_C_INTERVAL_UNMOD        16 // Time between cursor movements (unmodified)
//#   define MK_C_OFFSET_0               1 // Cursor offset per movement (KC_ACL0)
//#   define MK_C_INTERVAL_0            32 // Time between cursor movements (KC_ACL0)
//#   define MK_C_OFFSET_1               4 // Cursor offset per movement (KC_ACL1)
//#   define MK_C_INTERVAL_1            16 // Time between cursor movements (KC_ACL1)
//#   define MK_C_OFFSET_2              32 // Cursor offset per movement (KC_ACL2)
//#   define MK_C_INTERVAL_2            16 // Time between cursor movements (KC_ACL2)
//#   define MK_W_OFFSET_UNMOD           1 // Scroll steps per scroll action (unmodified)
//#   define MK_W_INTERVAL_UNMOD        40 // Time between scroll steps (unmodified)
//#   define MK_W_OFFSET_0               1 // Scroll steps per scroll action (KC_ACL0)
//#   define MK_W_INTERVAL_0           360 // Time between scroll steps (KC_ACL0)
//#   define MK_W_OFFSET_1               1 // Scroll steps per scroll action (KC_ACL1)
//#   define MK_W_INTERVAL_1           120 // Time between scroll steps (KC_ACL1)
//#   define MK_W_OFFSET_2               1 // Scroll steps per scroll action (KC_ACL2)
//#   define MK_W_INTERVAL_2            20 // Time between scroll steps (KC_ACL2)
#endif // MOUSEKEY_ENABLE
