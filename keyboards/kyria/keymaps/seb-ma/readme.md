# Kyria keymap of seb-ma

This is [my personal userspace](../../../../users/seb-ma/readme.md) applied to [Kyria](../../readme.md).

All layers and features are detailed in [my userspace](../../../../users/seb-ma/readme.md)

## Hardware configuration

### Handedness by EEPROM

Allow to use either side as the master. See [QMK Setting handness](https://docs.qmk.fm/#/config_options?id=setting-handedness).
It needs to flash eeprom-lefthand.eep/eeprom-righthand.eep to respective halves.

Adding:

```c
#define EE_HANDS
```

Flashing can be done with:

```bash
# Build and flash left halve
make kyria/rev1:seb-ma:dfu-split-left
# Build and flash right halve
make kyria/rev1:seb-ma:dfu-split-right
```

To do compilation and flash with specific halve target, following lines respectively compile and flash:

- master specific features on left halve
- follower specific features on right halve

```bash
# Build and flash left halve
make kyria/rev1:seb-ma:dfu-split-left HALVE_SPECIFIC=master
# Build and flash right halve
make kyria/rev1:seb-ma:dfu-split-right HALVE_SPECIFIC=follower
```

### Elite C on both sides

Adding:

```c
#define SPLIT_USB_DETECT
#define NO_USB_STARTUP_CHECK
```

### OLED 128×64

Adding:

```c
#define OLED_DISPLAY_128X64
```

### Encoders EC11K

Adding:

```c
#define ENCODER_RESOLUTION 2
```

## Features

### RGB underglow

See [QMK RGB](https://docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgblight)

- Defining LED order
- Deactivating all effects to activate only specifics

Adding:

```c
#define RGBLIGHT_LED_MAP {…}

#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_… // According to animations to activate
#define RGBLIGHT_EFFECT_…
```

## License

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
