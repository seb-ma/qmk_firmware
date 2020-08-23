#
# Copyright 2020 @seb-ma
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

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
       oled_common.c \
       oled_follower.c \
       oled_master.c \
       oled_gfx_bongocat.c \
       oled_gfx_game_life.c \
       oled_gfx_oneko.c \
       oled_gfx_pomodoro.c \
       oled_gfx_starfield.c \
       rgb.c \
       tap_dance.c \
       transport_user.c \
       user_feature_closechar.c \
       user_func.c

# Libraries
SRC += lib/lib8tion/lib8tion.c

# Set NO_SECRETS if secrets file does not exist or requested in build chain
ifeq ("$(wildcard $(USER_PATH)/secrets.h)", "")
    OPT_DEFS += -DNO_SECRETS
else
    ifeq ($(strip $(NO_SECRETS)), yes)
        OPT_DEFS += -DNO_SECRETS
    endif
endif

# If SPLIT_TRANSPORT is custom, set transport user data feature
ifeq ($(strip $(SPLIT_TRANSPORT)), custom)
    OPT_DEFS += -DTRANSPORT_USER_DATA
    QUANTUM_SRC += transport_custom.c

    # Section copied from common_features.mk to avoid errors duriong ld

    # Functions added via QUANTUM_LIB_SRC are only included in the final binary if they're called.
    # Unused functions are pruned away, which is why we can add multiple drivers here without bloat.
    ifeq ($(PLATFORM),AVR)
        QUANTUM_LIB_SRC += i2c_master.c \
                            i2c_slave.c
    endif

    SERIAL_DRIVER ?= bitbang
    ifeq ($(strip $(SERIAL_DRIVER)), bitbang)
        QUANTUM_LIB_SRC += serial.c
    else
        QUANTUM_LIB_SRC += serial_$(strip $(SERIAL_DRIVER)).c
    endif

    # End of Section copied from common_features.mk
endif

# Link Time Optimization (LTO) when compiling the keyboard (+ automatically set NO_ACTION_MACRO and NO_ACTION_FUNCTION)
LTO_ENABLE = yes


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
