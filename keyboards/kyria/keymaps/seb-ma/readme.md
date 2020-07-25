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
