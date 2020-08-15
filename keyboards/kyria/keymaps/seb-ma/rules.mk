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

#---------------
# Configuration
#---------------

#AUTO_SHIFT_ENABLE   = yes # Auto shift
COMBO_ENABLE         = yes    # Combos
COMMAND_ENABLE       = no     # Commands for debug and configuration
CONSOLE_ENABLE       = no     # Console for debug
DYNAMIC_MACRO_ENABLE = yes    # Dynamic macros
ENCODER_ENABLE       = yes    # Encoders
EXTRAKEY_ENABLE      = yes    # Audio control and System control
GRAVE_ESC_ENABLE     = no     # Grave escape (share a key for ` and ~ and Escape)
#KEY_LOCK_ENABLE     = yes    # Hold down the next key pressed, until the key is pressed again
#LEADER_ENABLE       = yes    # Leader key sequences
MOUSEKEY_ENABLE      = yes    # Mouse keys
#NKRO_ENABLE         = yes    # USB Nkey Rollover
OLED_DRIVER_ENABLE   = yes    # OLED displays
RGBLIGHT_ENABLE      = yes    # Keyboard RGB underglow
#RAW_ENABLE          = yes    # HID (bidirectional communication between QMK and the host computer over an HID interface)
SPACE_CADET_ENABLE   = no     # Space cadet (left/right shift/ctrl/alt keys to open/close parenthesis)
SPLIT_TRANSPORT      = custom # Replace the standard split communication routines with a custom one
#TAP_DANCE_ENABLE    = yes    # Tap dance
#UNICODE_ENABLE      = yes    # Unicode
#UNICODEMAP_ENABLE   = yes    # Unicode extended
VELOCIKEY_ENABLE     = no     # Control the speed of lighting effects (like the Rainbow Swirl effect) with the speed of typing
WPM_ENABLE           = yes    # Word Per Minute (WPM) calculcation


#-------------
# Compilation
#-------------

# Definition of RGB layers (cf. rgb.h)
SRC += rgb_layers.c
