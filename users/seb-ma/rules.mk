#-------------
# Compilation
#-------------

SRC += combo.c \
       custom_keys.c \
       dynamic_macros.c \
       eeprom_user.c \
       encoder.c \
       hid.c \
       leader.c \
       oled.c \
       oled_gfx_bongocat.c \
       oled_gfx_game_life.c \
       oled_gfx_oneko.c \
       oled_gfx_pomodoro.c \
       rgb.c \
       tap_dance.c \
       transport_user.c \
       user_feature_closechar.c \
       user_feature_nbsp.c \
       user_func.c

# Set NO_SECRETS if secrets file does not exist or requested in build chain
ifeq ("$(wildcard $(USER_PATH)/secrets.h)", "")
    OPT_DEFS += -DNO_SECRETS
else
ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif
endif

 # Link Time Optimization (LTO) when compiling the keyboard (+ automatically set NO_ACTION_MACRO and NO_ACTION_FUNCTION)
LINK_TIME_OPTIMIZATION_ENABLE = yes


#----------------------------
# Split specific compilation
#----------------------------

# Specific compilation for each halve - they will not be interchangeable but saves a huge amount of space
#HALVE_SPECIFIC may have values: master, follower
#HALVE_SPECIFIC = master

# Specific compilation to lighten firmware by having a specific firmware for each halve
ifeq ($(strip $(HALVE_SPECIFIC)), master)
    OPT_DEFS += -DMASTER_ONLY
    # Master do all the tasks (except rendering OLED's follower)
    # Thus: all wanted features must be activated except animations that are displayed on follower (done in config.h)
else
ifeq ($(strip $(HALVE_SPECIFIC)), follower)
    OPT_DEFS += -DFOLLOWER_ONLY
    OPT_DEFS += -DNO_SECRETS

    # Most of the features can be desactivated for follower
    # including specific keys processing (done in config.h and with FOLLOWER_ONLY preprocessing macro)
    AUTO_SHIFT_ENABLE    = no
    COMBO_ENABLE         = no
    COMMAND_ENABLE       = no
    CONSOLE_ENABLE       = no
    DYNAMIC_MACRO_ENABLE = no
    EXTRAKEY_ENABLE      = no
    KEY_LOCK_ENABLE      = no
    GRAVE_ESC_ENABLE     = no
    LEADER_ENABLE        = no
    MOUSEKEY_ENABLE      = no
    NKRO_ENABLE          = no
    RAW_ENABLE           = no
    SPACE_CADET_ENABLE   = no
    TAP_DANCE_ENABLE     = no
    UNICODE_ENABLE       = no
    VELOCIKEY_ENABLE     = no

    # Features that must be activated on follower (if activated on master)
    #BACKLIGHT_ENABLE
    #ENCODER_ENABLE
    #OLED_DRIVER_ENABLE
    #RGBLIGHT_ENABLE
    #WPM_ENABLE
else
    # Default compilation
    # Remove all the follower animations (to have a firmware for both halves that fits in memory)
    OPT_DEFS += -DHALVE_BOTH_LIGHT
endif # HALVE_SPECIFIC == follower
endif # HALVE_SPECIFIC == master
