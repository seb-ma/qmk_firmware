# seb-ma userspace description

## Overview

This is my personal userspace mainly applied to Kyria.
Alphas layer and some features are oriented on french semantic and may be out of point in others languages.
Main layers are based on BÉPO keys so OS must have keyboard set to BÉPO except if used in Unicode/Unicode map mode.

Each extra feature described above is independent and can be enabled/disabled according to needs.

!> Due to limited memory space, all described features cannot be activated simultaneously.
For example, in these implementations, [Combos](#Combos) and [Leader key](#Leader%20key) are nearly equivalents. Choice is a matter of taste; but using specific compilation for each halve will help a lot (see [Compilation and flashing](#Compilation%20and%20flashing) for details).

### TODO

Some features need to be improved/corrected or may be added. Here is my list:

- Known bugs
  - [ ] HID: host application does not see usage page/usage of the device
  - [ ] RGB: RGB_XXX keys do not activate animations (not compatible with layers)
- Evolutions
  - [ ] LAYOUT: add a layout for games (or ALPHA that bypass all processing in custom_keys, deactivate unneeded stuff…)
  - [ ] UNICODE: test UNICODE_ENABLE / UNICODEMAP_ENABLE and fix the FIXME in custom_keys.c

### Supported Keyboards

- [Kyria](../../keyboards/kyria/readme.md). *See [User keymap](../../keyboards/kyria/keymaps/seb-ma/readme.md) for adaptations*

### Table of Contents

1. [Layers](#Layers)
    - [General information](#General%20information)
    1. [Base layer (alphas)](#Base%20(alphabetic))
    1. [Numerics / Symbols / Functions](#Numeric%20/%20Symbols)
    1. [Navigation / Mouse / Dynamic macros / Shortcuts](#Navigation%20/%20Mouse)
    1. [Media / RGB](#Media%20/RGB)
1. [Encoders](#Encoders)
    1. [Left encoder](#Left%20encoder)
    1. [Right encoder](#Right%20encoder)
1. [Special features](#Special%20features)
    1. [Close char](#Close%20Char)
    1. [Pomodoro](#Pomodoro)
1. [Features](#Features)
    1. [Custom keys](#Custom%20keys)
    1. [Combos](#Combos)
    1. [Dynamic macros](#Dynamic%20macros)
    1. [HID](#HID)
    1. [Leader key](#Leader%20key)
    1. [Tap dance](#Tap%20dance)
    1. [Unicode](#Unicode)
1. [Display](#Display)
    1. [Font](#Font)
    1. [Master screen](#Master%20screen)
    1. [Follower screen](#Follower%20screen)
1. [RGB](#RGB)
    1. [LED positions](#LED%20positions)
    1. [RGB modes](#RGB%20modes)
1. [Sources and compilation](#Sources%20and%20compilation)
    1. [Code organization](#Code%20organization)
    1. [Memory footprint](#Memory%20footprint)
    1. [Compilation and flashing](#Compilation%20and%20flashing)
1. [Useful documentation and tools](#Useful%20documentation%20and%20tools)
    1. [QMK documentation](#QMK%20documentation)
    1. [External documentation](#External%20documentation)
    1. [External tools](#External%20tools)

## Layers

### General information

All layers share:

- the same layout for thumbs (except on Media layer for encoders)
- the keys at column 1 of left halve for row 1 and row 2 (except on Media layer)

Encoders are on thumb row 2 at external position (drawn in bold line above).
Behavior is identical in all layers except in [Media / RGB](#Misc)

#### Layers navigation

Base layer is alphabetic.
Accessing other layers is done by:

- key NUM/SYM: hold to temporary access or tap to enter/exit [Numeric / Symbols / Functions](#Numeric) layer
- key NAV/MOU: hold to temporary access or tap to enter/exit [Navigation / Mouse](#Navigation) layer
- keys NUM/SYM + NAV/MOU: hold to temporary access or tap to enter/exit [Media / RGB](#Misc) layer

#### Key representation

Each layer share the same semantic in following descriptions:

```text
Physical keys representation by default:
┌────────────────┐  ▒    = Dead key
│ with other mod │  #S   = with Shift
│ key      key#S │  #AG  = with AltGr
│ key#AG key#AGS │  #AGS = with AltGr + Shift
└────────────────┘  #H   = Holding
```

### Base (alphabetic)

The base layer is the alphabetic layer.

#### Representation

```text
                                       Left                                                             Right

          1       2       3       4       5       6                                             1       2       3         4       5       6
                      ┌───────┬───────┬───────┬───────┐                                     ┌───────┬───────┬───────┬───────┐
      ┌───────┬───────┤       │       │       │       │                                     │       │       │       │       ├───────┬───────┐
      │       │       │ é   É │ p   P │ o   O │ è   È │                                     │ ^   ! │ v   V │ d   D │ l   L │       │       │
Row 1 │Esc    │ b   B │ ´▒  ˝▒│ &   § │ œ   Œ │ `▒  ` │                                     │ ¡     │ ˇ▒    │ ð   Ð │ /▒    │ j   J │ z   Z │
      │CapLck │ |   ¦ ├───────┼───────┼───────┼───────┤                                     ├───────┼───────┼───────┼───────┤ ĳ   Ĳ │ ə   Ə │
      ├───────┼───────┤       │       │       │       │                                     │       │       │       │       ├───────┼───────┤
      │       │       │ u   U │ i   I │ e   E │ ,   ; │                                     │ c   C │ t   T │ s   S │ r   R │       │       │
Row 2 │Clo    │ a   A │ ù   Ù │ ¨▒  ˙▒│ €   ¤▒│ '   ̛ ▒│                                     │ ç   Ç │ þ   Þ │ ß   ẞ │ ®   ™ │ n   N │ m   M │
      │ClCl#AG│ æ   Æ ├───────┼───────┼───────┼───────┤    1      2            1      2     ├───────┼───────┼───────┼───────┤ ~▒    │ ¯▒  º │
      ├───────┼───────┤       │       │       │       │┌───────┬───────┐   ┌───────┬───────┐│       │       │       │       ├───────┼───────┤
      │       │       │ y   Y │ x   X │ .   : │ k   K ││       │       │   │       │       ││ ’   ? │ q   Q │ g   G │ h   H │       │       │
Row 3 │ ê   Ê │ à   À │ {   ‘ │ }   ’ │ …   · │ ~     ││ BckSp │ Ctrl  │   │ AltGr │  Del  ││ ¿    ̉▒│ °▒   ̣▒│ µ▒    │ †   ‡ │ f   F │ w   W │
      │ /     │ \     ├───────┴───────┴───────┴───────┘│       │       │   │       │       │└───────┴───────┴───────┴───────┤ ˛▒  ª │ ˘▒    │
      └───────┴───────┘     ▄▄▄▄▄▄▄┌───────┬───────┬───┴───┬───┴───┬───┘   └───┬───┴───┬───┴───┬───────┬───────┐▄▄▄▄▄▄▄     └───────┴───────┘
                           ▐▲▼Pag#S▌(Layer)│       │       │       │           │       │       │       │(Layer)▐◄►Wrd#S▌
Thumb row 2                ▐  Gui  ▌NAV/MOU│  Tab  │Sp NbSp│ Shift │           │ Shift │ Enter │  Alt  │NUM/SYM▐  App  ▌
                           ▐  ↑↓   ▌       │       │_ NNbSp│       │           │       │       │       │       ▐  ←→   ▌
                            ▀▀▀▀▀▀▀└───────┴───────┴───────┴───────┘           └───────┴───────┴───────┴───────┘▀▀▀▀▀▀▀
                               1       2       3       4       5                   1       2       3       4       5
```

#### Description

This layer is based on [BÉPO](https://bepo.fr) with some adjustments:

- move of `w` from row 1 to row 3
- replacement of AltGr and AltGr+Shift on `c` to have `ç` and `Ç` (chars becoming unavaible: `©` and `ſ`)
- swap of `'` and `’`

Specific keys:
|Code|Description|
|---|---|
|Clo (AltGr + Ld)|Automatically close opened chars `"(«[{` (see [Close char](#Close%20Char) feature for details)|
|Shift + Clo (AltGr + Shift + Ld)|Reset buffer of registered char of Close char feature|
|Ld (Leader)|Leader key for sequence of keys to trigger specific actions|
|AltGr + Esc|Toggle Caps lock|

### Numeric / Symbols

This is the numeric / symbols / functions layer.

#### Representation

```text
                                       Left                                                             Right

          1       2       3       4       5       6                                             1       2       3       4       5       6
                      ┌───────┬───────┬───────┬───────┐                                     ┌───────┬───────┬───────┬───────┐
      ┌───────┬───────┤       │       │       │       │                                     │       │       │       │       ├───────┬───────┐
      │       │       │ 2     │ 3     │ 4     │ 5     │                                     │ 6     │ 7     │ 8     │ 9     │       │       │
Row 1 │  ___  │ 1     │ “     │ ”     │ ≤     │ ≥     │                                     │       │ ¬     │ ¼     │ ½     │ 0     │ ,   ; │
      │       │ „     ├───────┼───────┼───────┼───────┤                                     ├───────┼───────┼───────┼───────┤ ¾     │ .   : │
      ├───────┼───────┤       │       │       │       │                                     │       │       │       │       ├───────┼───────┤
      │       │       │ «     │ »     │ (     │ )     │                                     │ @     │ +     │ -     │ /     │       │       │
Row 2 │  ___  │ "     │ <   “ │ >   ” │ [   ≤ │ ]   ≥ │                                     │ ^     │ ±   ¬ │ −   ¼ │ ÷   ½ │ *     │ =   ° │
      │       │ ─   „ ├───────┼───────┼───────┼───────┤    1      2            1      2     ├───────┼───────┼───────┼───────┤ ×   ¾ │ ≠   ′ │
      ├───────┼───────┤       │       │       │       │┌───────┬───────┐   ┌───────┬───────┐│       │       │       │       ├───────┼───────┤
      │       │       │ F2    │ F3    │ F4    │ F5    ││       │       │   │       │       ││ F6    │ F7    │ F8    │ F9    │       │       │
Row 3 │ $   # │ F1    │ F12   │ F13   │ {     │ }     ││  ___  │  ___  │   │  ___  │  ___  ││ ^▒    │ ˇ▒    │ \     │ /     │ F10   │ %   ` │
      │ –   ¶ │ F11   ├───────┴───────┴───────┴───────┘│       │       │   │       │       │└───────┴───────┴───────┴───────┤       │     ″ │
      └───────┴───────┘     ▄▄▄▄▄▄▄┌───────┬───────┬───┴───┬───┴───┬───┘   └───┬───┴───┬───┴───┬───────┬───────┐▄▄▄▄▄▄▄     └───────┴───────┘
                           ▐       ▌       │       │       │       │           │       │       │       │       ▐       ▌
               Thumb row 2 ▐  ___  ▌  ___  │  ___  │  ___  │  ___  │           │  ___  │  ___  │  ___  │  ___  ▐  ___  ▌
                           ▐       ▌       │       │       │       │           │       │       │       │       ▐       ▌
                            ▀▀▀▀▀▀▀└───────┴───────┴───────┴───────┘           └───────┴───────┴───────┴───────┘▀▀▀▀▀▀▀
                               1       2       3       4       5                   1       2       3       4       5
```

#### Description

Basically:

- Home row is the symbols line
- Top row is the numeric line
- Bottom row is the F(x) line

This is based on BÉPO with some adjustments:

- `F11`, `F12` and `F13` with AltGr on `F1`, `F2` and `F3`
- `{` and `}` with AltGr on `F4` and `F5`
- `^` and `ˇ` (dead keys) with AltGr on `F6` and `F7`
- `\` and `/` with AltGr on `F8` and `F9`
- `,` and `.` (and their Shift association) on right of key `0`

### Navigation / Mouse

This is the navigation / mouse layer.

#### Representation

```text
                                       Left                                                             Right

          1       2       3       4       5       6                                             1       2       3       4       5       6
                      ┌───────┬───────┬───────┬───────┐                                     ┌───────┬───────┬───────┬───────┐
      ┌───────┬───────┤       │       │       │       │                                     │       │       │       │       ├───────┬───────┐
      │       │       │   ▲   │   ↑   │   ▼   │DynStop│                                     │  Cut  │   ▲   │   ↑   │   ▼   │       │       │
Row 1 │  ___  │ Btn3  │(mouse)│(mouse)│(mouse)│       │                                     │       │       │       │       │ Pause │Insert │
      │       │(mouse)├───────┼───────┼───────┼───────┤                                     ├───────┼───────┼───────┼───────┤       │       │
      ├───────┼───────┤       │       │       │       │                                     │       │       │       │       ├───────┼───────┤
      │       │       │   ←   │   ↓   │   →   │DynM1 ►│                                     │ Copy  │   ←   │   ↓   │   →   │       │       │
Row 2 │DynM1 ■│ Btn1  │(mouse)│(mouse)│(mouse)│       │                                     │       │       │       │       │ Find  │ Undo  │
      │       │(mouse)├───────┼───────┼───────┼───────┤    1      2            1      2     ├───────┼───────┼───────┼───────┤       │       │
      ├───────┼───────┤       │       │       │       │┌───────┬───────┐   ┌───────┬───────┐│       │       │       │       ├───────┼───────┤
      │       │       │   ◄   │       │   ►   │DynM2 ►││       │       │   │       │       ││ Paste │   ◄   │       │   ►   │       │       │
Row 3 │DynM2 ■│ Btn2  │(mouse)│       │(mouse)│       ││  ___  │  ___  │   │  ___  │  ___  ││       │       │       │       │Pr.Scr │ Redo  │
      │       │(mouse)├───────┴───────┴───────┴───────┘│       │       │   │       │       │└───────┴───────┴───────┴───────┤       │       │
      └───────┴───────┘     ▄▄▄▄▄▄▄┌───────┬───────┬───┴───┬───┴───┬───┘   └───┬───┴───┬───┴───┬───────┬───────┐▄▄▄▄▄▄▄     └───────┴───────┘
                           ▐       ▌       │       │       │       │           │       │       │       │       ▐       ▌
               Thumb row 2 ▐Bt Ms 1▌  ___  │  ___  │  ___  │  ___  │           │  ___  │  ___  │  ___  │  ___  ▐Bt Ms 2▌
                           ▐Bt Ms 3▌       │       │       │       │           │       │       │       │       ▐Bt Ms 3▌
                            ▀▀▀▀▀▀▀└───────┴───────┴───────┴───────┘           └───────┴───────┴───────┴───────┘▀▀▀▀▀▀▀
                               1       2       3       4       5                   1       2       3       4       5
```

#### Description

Basically:

- Left part is the mouse navigation + dynamic macros playing
- Right part is the arrows navigation + shortcuts

Specific keys:
|Code|Description|
|---|---|
|Axel123|Cycles throw `KC_MS_ACCEL0`, `KC_MS_ACCEL1`, `KC_MS_ACCEL2`|

#### Configuration

Activation of mouse navigation is done in file `rules.mk`:

```c
MOUSEKEY_ENABLE = yes
```

### Media / RGB

This is the Media / RGB layer.

#### Representation

```text
                                       Left                                                             Right

          1       2       3       4       5       6                                             1       2       3       4       5       6
                      ┌───────┬───────┬───────┬───────┐                                     ┌───────┬───────┬───────┬───────┐
      ┌───────┬───────┤       │       │       │       │                                     │       │       │       │       ├───────┬───────┐
      │eepr#AG│       │ Hue↑  │ Sat↑  │ Val↑  │Speed↑ │                                     │ Mode→ │Effect │Effect │Effect │       │eepr#AG│
Row 1 │Toggle │Bright↑│ (RGB) │ (RGB) │ (RGB) │ (RGB) │                                     │ (RGB) │ (RGB) │ (RGB) │ (RGB) │Effect │Toggle │
      │ (RGB) │ (RGB) ├───────┼───────┼───────┼───────┤                                     ├───────┼───────┼───────┼───────┤ (RGB) │(OLED2)│
      ├───────┼───────┤       │       │       │       │                                     │       │       │       │       ├───────┼───────┤
      │       │       │ Hue↓  │ Sat↓  │ Val↓  │Speed↓ │                                     │ Mode← │Effect │Effect │Effect │       │       │
Row 2 │ Plain │Bright↓│ (RGB) │ (RGB) │ (RGB) │ (RGB) │                                     │ (RGB) │ (RGB) │ (RGB) │ (RGB) │       │CyclAni│
      │ (RGB) │ (RGB) ├───────┼───────┼───────┼───────┤    1      2            1      2     ├───────┼───────┼───────┼───────┤       │(OLED2)│
      ├───────┼───────┤       │       │       │       │┌───────┬───────┐   ┌───────┬───────┐│       │       │       │       ├───────┼───────┤
      │       │       │ Unix  │ Win   │ WinC  │ Mac   ││       │       │   │       │       ││       │       │       │       │StrtStp│       │
Row 3 │Toggle │Cycle  │Unicode│Unicode│Unicode│Unicode││  ___  │  ___  │   │  ___  │  ___  ││       │       │       │       │Pomodo │InitAni│
      │Unicode│Unicode├───────┴───────┴───────┴───────┘│       │       │   │       │       │└───────┴───────┴───────┴───────┤(OLED2)│(OLED2)│
      └───────┴───────┘     ▄▄▄▄▄▄▄┌───────┬───────┬───┴───┬───┴───┬───┘   └───┬───┴───┬───┴───┬───────┬───────┐▄▄▄▄▄▄▄     └───────┴───────┘
                           ▐       ▌       │       │       │       │           │       │       │       │       ▐       ▌
               Thumb row 2 ▐ Mute  ▌  ___  │  ___  │  ___  │  ___  │           │  ___  │  ___  │  ___  │  ___  ▐ Play  ▌
                           ▐ ↑↓Vol ▌       │       │       │       │           │       │       │       │       ▐←→Track▌
                            ▀▀▀▀▀▀▀└───────┴───────┴───────┴───────┘           └───────┴───────┴───────┴───────┘▀▀▀▀▀▀▀
                               1       2       3       4       5                   1       2       3       4       5
```

#### Description

Specific keys:
|Code|Description|
|---|---|
|Toggle RGB|Toggle RGB - Store current RGB status in EEPROM with AltGr|
|Toggle OLED2<sup>1</sup>|Toggle OLED of follower halve - Store current status in EEPROM with AltGr|
|Init animation<sup>1</sup>|Reinitialize animation on follower OLED|
|Cycle animations<sup>1</sup>|Cycle throw available animations - Store current animation in EEPROM with AltGr|
|Start/Stop pomodoro|Start (or stop) a timer of 25 minutes|

*<sup>1</sup>: Warn: works only with a light modification in transport layer (in QMK core) and activation of TRANSPORT_USER_DATA*

#### Medias on encoders

On this layer, encoders are used for medias.
See [Encoders](#Encoders) for general behavior.

##### Left encoder

|Code|Description|
|---|---|
|tap|Volume/Mute|
|left|Volume down|
|right|Volume up|

##### Right encoder

|Code|Description|
|---|---|
|tap|Play|
|left|Track previous|
|right|Track next|

#### Configuration

Activation of media navigation is done in file `rules.mk`:

```c
EXTRAKEY_ENABLE = yes
```

## Encoders

Encoders are used the same way to navigate in all layers except Media / RGB layer.

### Left encoder

|Code|Description|
|---|---|
|tap|GUI|
|clockwise|down arrow|
|reverse clockwise|up arrow|
|Altgr + clockwise|page down|
|Altgr + reverse clockwise|page up|

### Right encoder

|Code|Description|
|---|---|
|tap|APP|
|clockwise|right arrow|
|reverse clockwise|left arrow|
|Altgr + clockwise|end|
|Altgr + reverse clockwise|home|

### Configuration

Activation is done in file `rules.mk`:

```c
ENCODER_ENABLE = yes
```

## Special features

Here is a description of user independent-layer features.

### Close Char

This feature registers keys each time one of the following is tapped: `"(«[{`.
When using the Close Key, it outputs the close char related to the opened tapped by reverse order
If the close char is manually typed, it is also removed from the list to output.

#### Configuration

Activation of close char is done in file `config.h`:

```c
#define USER_CLOSE_CHAR
```

### Pomodoro

This feature displays a countdown timer of 25 minutes on OLED. The principle is from [The Pomodoro technique](https://francescocirillo.com/pages/pomodoro-technique).
This feature can be upgraded with a [special animation](#Pomodoro%20animation).

#### Configuration

Activation of pomodoro is done in file `config.h`:

```c
#define POMODORO_TIMER 25 // time of pomodoro in minutes
```

## Features

This section describes QMK features applied.

### Custom keys

|Code|Description|
|---|---|
|C_CLOSE_CHAR|Close lasts opening chars *See [Close Char feature](#Close%20Char)*|
|C_CLOSE_CHAR_CLEAR|Clear buffer of [Close Char feature](#Close%20Char)|
|C_MS_ACCEL|Cycle throw KC_MS_ACCEL_0, KC_MS_ACCEL_1 and KC_MS_ACCEL_2|
|C_TOGGLE_UNICODE|Toggle between standard keymap (based on OS layout) and unicode *See [Unicode](#Unicode)*|

Some standard keycodes are overridden only with AltGr modifier and some custom keycodes are added too:
|Code|Tap|AltGr + Tap|
|---|---|---|
|**Existing keys overridden**|
|KC_ESC|KC_ESC|KC_CAPSLOCK|
|KC_F1|KC_F1|KC_F11|
|KC_F2|KC_F2|KC_F12|
|KC_F3|KC_F3|KC_F13|
|KC_F4|KC_F4|`{`|
|KC_F5|KC_F5|`}`|
|KC_F6|KC_F6|`^` *(dead key)*|
|KC_F7|KC_F7|`ˇ` *(dead key)*|
|KC_F8|KC_F8|`\`|
|KC_F9|KC_F9|`/`|
|**Custom keys**|
|C_OLED2_TOGGLE|C_OLED2_TOGGLE|C_OLED2_TOGGLE_EEPROM|
|C_RGB_TOGGLE|C_RGB_TOGGLE|RGB_TOG|
|C_CLOSE_CHAR|C_CLOSE_CHAR_CLEAR|

Some standard keycodes are fully overridden according to modifiers and some custom keycodes are added too:
|Code|Tap|Shift + Tap|AltGr + Tap|Shift + AltGr + Tap|
|---|---|---|---|---|
|**Existing keys overridden**|
|`c`|`c`|`C`|`ç`|`Ç`|
|**Custom keys**|
|C_COMMA_DOT|`,`| `;`|`.`| `:`|
|C_ENC1_CW|KC_MS_DOWN|KC_MS_WH_DOWN|KC_DOWN|KC_PGDOWN|
|C_ENC1_RCW|KC_MS_UP|KC_MS_WH_UP|KC_UP|KC_PGUP|
|C_ENC2_CW|KC_MS_RIGHT|KC_MS_WH_RIGHT|KC_RIGHT|Ctrl + KC_RIGHT|
|C_ENC2_RCW|KC_MS_LEFT|KC_MS_WH_LEFT|KC_LEFT|Ctrl + KC_LEFT|

### Combos

Cording two or more keys to activate specific actions.
|Cording|Description|Equivalent|
|---|---|---|
|Shortcuts|
|`TAB` + `à`|Close|*Ctrl + w*|
|`TAB` + `a`|Select all|*Ctrl + a*|
|`TAB` + `u`|Cut|*Ctrl + x*|
|`TAB` + `i`|Copy|*Ctrl + c*|
|`TAB` + `e`|Paste|*Ctrl + v*|
|`TAB` + `p`|Undo|*Ctrl + z*|
|`TAB` + `o`|Redo|*Ctrl + y*|
|`TAB` + `t`|Reopen last tab|*Ctrl + Shift + t*|
|Quadrigrams|
|`e` + `l`|Write quadrigram elle|elle|
|`i` + `q`|Write quadrigram ique|ique|
|`m` + `e`|Write quadrigram ment|ment|
|`q` + `u`|Write quadrigram quel|quel|
|`t` + `i`|Write quadrigram tion|tion|
|Non-breaking space|
|`SPACE` + `«`|Append nbsp after «|`« `|
|`SPACE` + `»`|Append nbsp before »|` »`|
|`SPACE` + `u`|Equivalent to char « and append nbsp after «|`« `|
|`SPACE` + `i`|Equivalent to char » and append nbsp before »|` »`|
|`SPACE` + `!`|Append nbsp before !|` !`|
|`SPACE` + `?`|Append nbsp before ?|` ?`|
|`SPACE` + `;`|Append nbsp before ;|` ;`|
|`SPACE` + `:`|Append nbsp before :|` :`|
|`SPACE` + `^`|Shift char ^ and append nbsp before|` !`|
|`SPACE` + `’`|Shift char ’ and append nbsp before|` ?`|
|`SPACE` + `,`|Shift char , and append nbsp before|` ;`|
|`SPACE` + `.`|Shift char . and append nbsp before|` :`|
|Others|
|`SPACE` + `h`|`https://`|`https://`|
|`SPACE` + `g`|`/giphy `|`/giphy `|
||**Sequences using secrets**|
|`s` + `m`|*UID*|*secret*|
|`s` + `k`|*Product*|*secret*|

### Dynamic macros

Recording/playing macros.

#### Configuration

Activation is done in file `rules.mk`:

```c
DYNAMIC_MACRO_ENABLE = yes
```

### HID

Send status of the keyboard over HID interface.
See [hid.h](hid.h) for data structure sent to host.

See for [HID Host](hid_host/readme.md) the host side.

#### Configuration

Activation is done in file `rules.mk`:

```c
RAW_ENABLE = yes
```

### Leader key

The keycode `KC_LEAD` must be dedicated to a single key -- it's a single action key, can't be used for anything else *(see [Leader Key Documentation](../../docs/feature_leader_key.md))*.

Lead followed by one of this sequence:
|Code|Description|Equivalent|
|---|---|---|
|`à`|Close|*Ctrl + w*|
|`a`|Select all|*Ctrl + a*|
|`u`|Cut|*Ctrl + x*|
|`i`|Copy|*Ctrl + c*|
|`e`|Paste|*Ctrl + v*|
|`p`|Undo|*Ctrl + z*|
|`o`|Redo|*Ctrl + y*|
|`t`|Reopen last tab|*Ctrl + Shift + t*|
|`h`|`https://`|`https://`|
|`g`|`/giphy `|`/giphy `|
||**Sequences using secrets**|
|`sm`|*UID*|*secret*|
|`sk`|*Product*|*secret*|

#### Configuration

Activation of leader key is done in file `rules.mk`:

```c
LEADER_ENABLE = yes
```

### Tap dance

|Code|Single tap|Double tap|Triple tap|
|---|---|---|---|
|TD_COMM_QUOTE|`,`|`'`||
|TD_GUIS|KC_LGUI|KC_APP||
|TD_MS_BTNS|KC_MS_BTN1|KC_MS_BTN2||
|TD_MS_ACCEL|KC_MS_ACCEL0|KC_MS_ACCEL1|KC_MS_ACCEL2|

#### Configuration

Activation of tap dance is done in file `rules.mk`:

```c
TAP_DANCE_ENABLE = yes
```

#### Usage

Set a `TD(TD_xxx)` with `TD_xxx` one of the tap dance code in the keymap.

### Unicode

Keyboard can be activated to send unicode instead of simple keycodes.
It must be activated in configuration, then a custom feature permits to switch between unicode and normal keycodes: `C_TOGGLE_UNICODE`.
It is based on defined layouts, thus, unicode activation get a BÉPO layout for alphas.

If Unicode map is enabled instead of "basic" unicode, extended unicode map can be used in keymaps.
|Unicode character|Accessed by|
|---|---|
|‽ *(bang)*|replacement place of `¡`|
|⸮ *(irony)*|replacement of `¿`|

#### Configuration

For basic unicode, activation is done in file `rules.mk`:

```c
UNICODE_ENABLE = yes
```

For extended unicode, activation is done in file `rules.mk`:

```c
UNICODEMAP_ENABLE = yes
```

## Display

OLED used are 128×64.

### Font

A specif font as been created to optimize used memory: table is truncated at last existing char.
Beginning of table is the standard table (symbols, alphabet, numeric).
End of table contains all symbols used to display graphics on master screen (items, layers representation, modifiers…).

![Custom font](https://i.imgur.com/L80Lyqv.png)

### Master screen

The master screen is used to display status of keyboard.
For each item, information are listed and font is reversed if activated.

![Status display](https://i.imgur.com/CJ0vINg.png)

Items:

- Layers
  - Alpha (in uppercase if caps lock is activated)
  - Numerics/Symbols
  - Navigation/Mouse
  - Media/RGB
- Modifiers
  - Shift
  - Ctrl
  - Gui
  - Alt
  - AltGr
- Dynamic macros
  - Macro 1 (Play, Record, Warning)
  - Macro 2 (Play, Record, Warning)

#### Representation

```
  1                   21
 ┌─────────────────────┐
1│ LAY   Alpha  Num/S  │
 │ LAY   Nav/M  Med/R  │
 │                     │
 │ MOD   Sft  Ctl  Gui │
 │ MOD   Alt  AlG      │
 │                     │
 │ DYM   1  Pl  Rc  Wn │
8│ DYM   2  Pl  Rc  Wn │
 └─────────────────────┘
```

### Follower screen

The follower screen is used to display fun animations.
Animations may be included simultaneously and cycle throw with the key C_OLED2_ANIMATION_CYCLE.
!> The cycle can only work with a modification in transport layer in QMK core.

#### Bongo cat

This animation is featuring [bongo cat](https://bongo-cat.glitch.me/) tapping on a 6 keys' keyboard.

![paws up](https://imgur.com/LkryRFS.png) ![left paw on 1st key](https://imgur.com/EkrcZRO.png) ![paws up](https://imgur.com/LkryRFS.png) ![right paw on 5th key](https://imgur.com/cm8Wxla.png) […]

This animation can be synchronized with WPM feature to rythm animation.
Animation is composed of 16 frames randomly displayed:

- paws up
- left paw on 1st key
- left paw on 2nd key
- left paw on 3rd key
- right paw on 4th key
- right paw on 5th key
- right paw on 6th key
- both paws in combination of the 6 previous frame
  - i.e. left paw of one of the 3 first keys and right paw on one of the 3 last keys
  - this frames come always after a "one paw down" and the next frame is always "paws up"

Frames encoding and rendering are done to minimize memory footprint (~1.8KiB)
Algorithm to convert full frames to optimized ones is in [gen_bongocat.c](bongocat/gen_bongocat.c) and may be adapted for others animations

##### Configuration

Activation of oled display is done in file `rules.mk`:

```c
OLED_DRIVER_ENABLE = yes
```

Activation of follower halve animation of bongo cat tapping on a keyboard is done in file `config.h`:

```c
#define BONGOCAT_ANIMATION
```

Optional activation of synchronization of follower halve animation on user currently tapping speed is done in file `rules.mk`:

```c
WPM_ENABLE = yes
```

#### Game of life

This animation is a [Conway's game of life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) with [DotLife](https://conwaylife.com/wiki/OCA:DotLife) rules.
Each cell is a 2×2 square living on a toroidal universe (the whole screen) and living (birth, death, surviving) according to number of neighbors.

##### Configuration

Activation of oled display is done in file `rules.mk`:

```c
OLED_DRIVER_ENABLE = yes
```

Activation of follower halve animation of game of life is done in file `config.h`:

```c
#define LIFE_ANIMATION
```

Optional activation of synchronization of follower halve animation on user currently tapping speed is done in file `rules.mk`:

```c
WPM_ENABLE = yes
```

#### Pomodoro animation

This animation is an abstract representation of the pomodoro feature.
It displays blank pixels to represent the remaining time. Black pixels are randomly placed and their number increments when time goes.

It needs to have following activated features to work: [Pomodoro](#Pomodoro) and transport user data between halves.

##### Configuration

Activation of oled display is done in file `rules.mk`:

```c
OLED_DRIVER_ENABLE = yes
```

Activation of pomodoro animation is done in file `config.h`:

```c
#define TRANSPORT_USER_DATA
#define POMODORO_ANIMATION
```

#### Oneko

This animation is a cat playing and walking around the screen: [Oneko](https://github.com/tie/oneko).

![Oneko awake](https://i.imgur.com/xrOCJOP.png)
![Oneko jare](https://i.imgur.com/jfUK6CF.png)
![Oneko left1](https://i.imgur.com/Z8wDANp.png)
![Oneko left2](https://i.imgur.com/DM66ZOw.png)

##### Configuration

Activation of oled display is done in file `rules.mk`:

```c
OLED_DRIVER_ENABLE = yes
```

Activation of follower halve animation of Oneko is done in file `config.h`:

```c
#define ONEKO_ANIMATION
```

## RGB

### LED positions

Physical leds position (xx) related to keys
Master and follower may be swapped (right / left), 0-9 are always on master, 10-19 on follower.

```text
                                     Master                                                             Follower

          1       2       3       4       5       6                                             1       2       3       4       5       6
                      ┌───────┬──────(04)─────┬───────┐                                     ┌───────┬─────(14)──────┬───────┐
      ┌──(09)─┬─(05)──┤       │       │       │       │                                     │       │       │       │       ├──(15)─┬─(19)──┐
      │       │       │       │       │       │       │                                     │       │       │       │       │       │       │
Row 1 │       │       │       │       │       │       │                                     │       │       │       │       │       │       │
      │       │       ├───────┼───────┼───────┼──(03)─┤                                     ├─(13)──┼───────┼───────┼───────┤       │       │
      ├───────┼───────┤       │       │       │       │                                     │       │       │       │       ├───────┼───────┤
      │       │       │       │       │       │       │                                     │       │       │       │       │       │       │
Row 2 │       │       │       │       │       │       │                                     │       │       │       │       │       │       │
      │       │       ├───────┼───────┼───────┼───────┤    1      2            1      2     ├───────┼───────┼───────┼───────┤       │       │
      ├──(08)─┼──(06)─┤       │       │       │       │┌───────┬───────┐   ┌───────┬───────┐│       │       │       │       ├──(16)─┼─(18)──┤
      │       │       │       │       │       │       ││      (00)     │   │     (10)      ││       │       │       │       │       │       │
Row 3 │       │       │       │       │       │       ││       │       │   │       │       ││       │       │       │       │       │       │
      │       │       ├───────┴───────┴───────┴───────┘│       │       │   │       │       │└───────┴───────┴───────┴───────┤       │       │
      └───────┴───────┘    ┌(07)───┬───(02)┬────(01)───┴───┬───┴───┬───┘   └───┬───┴───┬───┴───(11)────┬(12)───┬───(17)┐    └───────┴───────┘
                           │       │       │       │       │       │           │       │       │       │       │       │
               Thumb row 2 │       │       │       │       │       │           │       │       │       │       │       │
                           │       │       │       │       │       │           │       │       │       │       │       │
                           └───────┴───────┴───────┴───────┴───────┘           └───────┴───────┴───────┴───────┴───────┘
                               1       2       3       4       5                  1       2       3       4       5
```

### RGB modes

Two modes are available: with layers or without (implemented to reduce memory footprint but with less features - *see above*).

#### Both modes

- Each keymap layer has its own color

#### Layers mode

- Caps lock activate one led
- Recording and playing a dynamic macro activate one led
- Playing leader sequence activate one led

#### No layers mode

Nothing else but keymap layers is implemented.

#### Configuration

Activation of RGB underglow is done in file `rules.mk`:

```c
RGBLIGHT_ENABLE = yes
```

Activation of RGB layers is done in file `config.h`:

```c
#define RGBLIGHT_LAYERS
```

## Sources and compilation

### Code organization

Each main feature is coded in a specific file to have code as clean and as independent as possible.

|File|Description|
|---|---|
|**Main files**|
|[rules.mk](rules.mk)|Activation of features|
|[config.h](config.h)|Configuration of features|
|[user_func.c](user_func.c)|Main entry points in user keymap|
|[layers.h](layers.h)|List of layers|
|[custom_keys.h](custom_keys.h)|List of custom keys|
|[custom_keys.c](custom_keys.c)|Central point of custom behaviors (implementation of user features, keycode override, delegation to other features…)|
|**Other files**|
|[combo.c](combo.c)|Definition of combos and their behaviors|
|[dynamic_macros.h](dynamic_macros.h)|Definition of dynamic macros status and external called functions|
|[dynamic_macros.c](dynamic_macros.c)|Implementation of dynamic macros status and external called functions|
|[eeprom_user.h](eeprom_user.h)|Definition of eeprom data|
|[eeprom_user.c](eeprom_user.c)|Implementation of eeprom functions|
|[encoder.c](encoder.c)|Implementation of encoders behavior|
|[hid.h](hid.h)|Definition of data sent over HID|
|[hid.c](hid.c)|Implementation of data sent over HID|
|[leader.h](leader.h)|Definition of leader sequence status and external called functions|
|[leader.c](leader.c)|Implementation of leader sequences|
|[oled_custom_font.h](oled_custom_font.h)|Custom font|
|[oled_custom_font_constants.h](oled_custom_font_constants.h)|Addresses of custom characters in custom font|
|[oled_gfx_bongocat.h](oled_gfx_bongocat.h)|Spites of bongocat animation|
|[oled_gfx_bongocat.c](oled_gfx_bongocat.c)|Implementation of bongocat animation (can be synchronized on WPM feature)|
|[oled_gfx_game_life.c](oled_gfx_game_life.c)|Implementation of game of life animation|
|[oled_gfx_oneko.h](oled_gfx_oneko.h)|Sprites of Oneko animation|
|[oled_gfx_oneko.c](oled_gfx_oneko.c)|Implementation of Oneko animation|
|[oled_gfx_pomodoro.c](oled_gfx_pomodoro.c)|Implementation of pomodoro animation|
|[oled.h](oled.h)|Definition of OLED external called functions|
|[rgb.h](rgb.h)|Definition of RGB external called functions|
|[rgb.c](rgb.c)|Implementation of RGB behavior|
|[tap_dance.h](tap_dance.h)|Definition of tap dance keys|
|[tap_dance.c](tap_dance.c)|Implementation of tap dance keys behavior|
|[transport_user.h](transport_user.h)|Definition of the data transfered between the two halves|
|[transport_user.c](transport_user.c)|Implementation of the data transfered between the two halves|
|[unicode_keys.c](unicode_keys.c)|Implementation of Unicode / Unicode map|
|[user_feature_closechar.h](user_feature_closechar.h)|Definition of feature close char|
|[user_feature_closechar.c](user_feature_closechar.c)|Implementation of feature close char|
|**Special files**|
|[secrets.h](secrets.h)|Not source controlled. Contains non public data *(but not too much private like passwords)*|
|**Kyria specific files**|
|[config.h](../../keyboards/kyria/keymaps/seb-ma/config.h)|Configuration of features/hardware adapted to keyboard|
|[keymap.h](../../keyboards/kyria/keymaps/seb-ma/keymap.h)|Definition of keymaps for each layer|
|[keymap.c](../../keyboards/kyria/keymaps/seb-ma/keymap.c)|Declaration of keymaps|
|[rgb_layers.c](../../keyboards/kyria/keymaps/seb-ma/rgb_layers.c)|Declaration of RGB layers|
|[rules.mk](../../keyboards/kyria/keymaps/seb-ma/rules.mk)|Activation of features|
|[readme.md](../../keyboards/kyria/keymaps/seb-ma/readme.md)|Description of keymap specific to Kyria|

### Memory footprint

Memory footprint is given including QMK code and userspace/keyboard code with LTO activated. Values will vary according to compiler and QMK release.

|Feature|Size when nothing all is activated|Size when all others are activated|
|---|---|---|
|**Base**|12808 *(available=15864)*|41726 *(over=12918) – excluding COMMAND and CONSOLE features*|
|**Features**|
|AUTO_SHIFT_ENABLE|2384|1478|
|COMBO_ENABLE|1480|900|
|COMMAND_ENABLE|388|1150|
|CONSOLE_ENABLE|1448|4864|
|DYNAMIC_MACRO_ENABLE|816|1210|
|ENCODER_ENABLE|626|688|
|EXTRAKEY_ENABLE|502|516|
|GRAVE_ESC_ENABLE|118|114|
|RAW_HID|*tbd*|*tbd*|
|KEY_LOCK_ENABLE|1744|1702|
|LEADER_ENABLE|1722|1262|
|MOUSEKEY_ENABLE|1756|1780|
|NKRO_ENABLE|400|294|
|NO_ACTION_ONESHOT *(by `#define`)*|-316|-472|
|OLED_DRIVER_ENABLE|3860|4030|
|[opt] BONGOCAT_ANIMATION *(option of OLED)* – *(by `#define`)*|2520|1130|
|[opt] LIFE_ANIMATION *(option of OLED)* – *(by `#define`)*|2582|1252|
|[opt] ONEKO_ANIMATION *(option of OLED)* – *(by `#define`)*|3502|*tbd*|
|[opt] POMODORO_ANIMATION *(option of OLED)* – *(by `#define`)*|808|36|
|RGBLIGHT_ENABLE|2206|2738|
|[opt] RGBLIGHT_LAYER + RGBLIGHT_LAYER_BLINK *(options of RGB)* – *(by `#define`)*|840|168|
|[opt] RGBLIGHT_ANIMATIONS *(option of RGB)* –  *(by `#define`)*|3376|3002|
|SPACE_CADET_ENABLE|404|360|
|TAP_DANCE_ENABLE|886|988|
|UNICODE_ENABLE|1432|2172|
|UNICODEMAP_ENABLE|1826|2126|
|VELOCIKEY_ENABLE|212|648|
|WPM_ENABLE|1342|454|
|**User features**|
|USER_CLOSE_CHAR *(by `#define`)*|430|464|
|POMODORO_TIMER *(by `#define`)*|2038|14|

To permit to include more features in firmware, a special `#define` is created: `HALVE_SPECIFIC`.
Basically, it needs to do a specific compilation for each halve (master and follower) by including only needed features for each.
Drawback is that the two halves are no more swappable: the USB cable must always be connected to the chosen master halve.

- For master: all wanted features need to be here except displaying stuff of follower oled.
- For follower: all features can be deactivated except data transmitted between the 2 halves – if activated on master – (backlight, rgb, encoder, wpm) and displaying stuff of follower oled.
See [Compilation and flashing](#Compilation%20and%20flashing) for how to compile a specific halve.

### Compilation and flashing

```bash
# clone/update the repo
#----------------------
git clone https://github.com/qmk/qmk_firmware
# OR update the repo (if already cloned)
git pull

# install submodules and configure
#---------------------------------
# (only one time or when dependencies change)
make git-submodule
# (only the first time)
qmk setup

# compile this layout
#--------------------
qmk compile -kb kyria -km seb-ma
#sometimes, weird things happen, so complete clean and build may help:
#make clean kyria/rev1:seb
# WARN: currently, QMK compilation is not compatible with gcc9 (pay attention to warnings during qmk setup!)

# to compile a specific halve, use one of the following make command then flash it to the corresponding halve
make kyria/rev1:seb-ma HALVE_SPECIFIC=master
# or
make kyria/rev1:seb-ma HALVE_SPECIFIC=follower

# flash this layout
#------------------
qmk flash -kb kyria -km seb-ma
```

## Useful documentation and tools

### QMK documentation and tools

- [Main entry (docs.qmk.fm)](https://docs.qmk.fm/)
- [Troubleshooting (eg "Can't Program on Linux")](https://beta.docs.qmk.fm/faqs/faq_build)
- [Keyboard tester (config.qmk.fm)](https://config.qmk.fm/#/test)

### External documentation

- [Reducing firmware size (thomasbaart.nl)](https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/)
- [Encoder usage ideas (docs.splitkb.com)](https://docs.splitkb.com/hc/en-us/articles/360010513760-How-can-I-use-a-rotary-encoder-)

- [List of shortcuts in most of the existing OS / applications (defkey.com)](https://defkey.com/)
- [Some ideas of modifications in layouts (ke-complex-modifications.pqrs.org)](https://ke-complex-modifications.pqrs.org/)

### Internal tools

- [Helpers to generate sprites animations](gfx_generator/readme.md)

### External tools

- [image2cpp (Convert image to C array)](https://javl.github.io/image2cpp/)
- [Font and Image editor](https://joric.github.io/qle/)
- [Font editor](https://helixfonteditor.netlify.app/)
