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
  - [ ] HID: host application does not work
- Evolutions
  - [ ] HID: send time from host to have an accurate timer (to use on pomodoro + display time if pomodoro is inactive)
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
    1. [Media / RGB](#Media%20/%20RGB)
    1. [Shortcuts](#Shortcuts)
1. [Encoders](#Encoders)
    1. [Left encoder](#Left%20encoder)
    1. [Right encoder](#Right%20encoder)
1. [Special features](#Special%20features)
    1. [Close char](#Close%20Char)
    1. [Pomodoro](#Pomodoro)
    1. [Custom transport](#Custom%20transport)
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
    1. [QMK documentation](#QMK%20documentation%20and%20tools)
    1. [External documentation](#External%20documentation)
    1. [External tools](#External%20tools)
1. [License](#License)

## Layers

### General information

All layers share:

- the same layout for thumbs (except on Media layer for encoders)
- the keys at column 1 of left halve for row 1 and row 2 (except on Media layer)

Encoders are on thumb row 2 at external position (drawn in bold line above).
Behavior is identical in all layers except in [Media / RGB](#Media%20/%20RGB)

#### Layers navigation

Base layer is alphabetic.
Accessing other layers is done by:

- key NUM/SYM: hold to temporary access or tap to enter/exit [Numeric / Symbols / Functions](#Numeric%20/%20Symbols) layer
- key NAV/MOU: hold to temporary access or tap to enter/exit [Navigation / Mouse / Dynamic macros / Shortcuts](#Navigation%20/%20Mouse) layer
- keys NUM/SYM + NAV/MOU: hold to temporary access or tap to enter/exit [Media / RGB](#Media%20/%20RGB) layer
- key TAB: hold to temporary access [Shortcuts](#Shortcuts) layer

### Base (alphabetic)

The base layer is the alphabetic layer.

#### Representation

![keyboard-layout-editor - Base (alphabetic)](https://i.imgur.com/08RNpZs.png)
[keyboard-layout-editor - Base (alphabetic)](http://www.keyboard-layout-editor.com/##@_backcolor=%23ffffff&name=Kyria%3B&@_x:18.75&c=%23f1f1f1&t=%23646464&fa@:1&:1&:1&:1%3B%3B&=Shift%0Akey%0AAltGr%20Shift%0AAltGr%3B&@_y:-0.75&x:3&c=%23cccccc&t=%23000000&p=R1&f:3%3B&=P%0Ap%0A%C2%A7%0A%2F&&_x:9&f:3%3B&=D%0Ad%0A%C3%90%0A%C3%B0%3B&@_y:-0.75&x:2&f:3%3B&=%C3%89%0A%C3%A9%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23779%2F%3B%3C%2F%2Fspan%3E%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23769%2F%3B%3C%2F%2Fspan%3E&_x:1&f:3%3B&=O%0Ao%0A%C5%92%0A%C5%93&_x:7&f:3%3B&=V%0Av%0A%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23780%2F%3B%3C%2F%2Fspan%3E&_x:1&f:3%3B&=L%0Al%0A%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23823%2F%3B%3C%2F%2Fspan%3E%3B&@_y:-0.875&x:5&f:3%3B&=%C3%88%0A%C3%A8%0A%60%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23768%2F%3B%3C%2F%2Fspan%3E&_x:5&f:3%3B&=!%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23770%2F%3B%3C%2F%2Fspan%3E%0A%0A%C2%A1%3B&@_y:-0.625&f:3%3B&=%0A%0A%0A%3Ci%20class%2F='kb%20kb-Unicode-Lock-Closed-1'%3E%3C%2F%2Fi%3E%E2%87%A7%0A%0A%0AEsc&_f:3%3B&=B%0Ab%0A%C2%A6%0A%7C&_x:13&f:3%3B&=J%0Aj%0A%C4%B2%0A%C4%B3&_f:3%3B&=Z%0Az%0A%C6%8F%0A%C9%99%3B&@_y:-0.75&x:3&p=R2&f:3%3B&=I%0Ai%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23775%2F%3B%3C%2F%2Fspan%3E%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23776%2F%3B%3C%2F%2Fspan%3E&_x:9&f:3%3B&=S%0As%0A%E1%BA%9E%0A%C3%9F%3B&@_y:-0.75&x:2&f:3%3B&=U%0Au%0A%C3%99%0A%C3%B9&_x:1&f:3&n:true%3B&=E%0Ae%0A%C2%A4%E2%96%92%0A%E2%82%AC&_x:7&f:3&n:true%3B&=T%0At%0A%C3%9E%0A%C3%BE&_x:1&f:3%3B&=R%0Ar%0A%E2%84%A2%0A%C2%AE%3B&@_y:-0.875&x:5&f:3%3B&=%2F%3B%0A,%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23806%2F%3B%3C%2F%2Fspan%3E%0A'&_x:5&f:3%3B&=C%0Ac%0A%C3%87%0A%C3%A7%3B&@_y:-0.625&c=%23dec29d&fa@:1&:1&:1&:1&:0&:0&:6%3B%3B&=%0A%0A%0AClear%20%3Ci%20class%2F='kb%20kb-Undo-2'%3E%3C%2F%2Fi%3E%0A%0A%0A%3Ci%20class%2F='kb%20kb-Undo-2'%3E%3C%2F%2Fi%3E&_c=%23cccccc&f:3%3B&=A%0Aa%0A%C3%86%0A%C3%A6&_x:13&f:3%3B&=N%0An%0A%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23834%2F%3B%3C%2F%2Fspan%3E&_f:3%3B&=M%0Am%0A%C2%BA%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23772%2F%3B%3C%2F%2Fspan%3E%3B&@_y:-0.75&x:3&p=R3&f:3%3B&=X%0Ax%0A%E2%80%99%0A%7D&_x:9&f:3%3B&=G%0Ag%0A%0A%C2%B5%E2%96%92%3B&@_y:-0.75&x:2&f:3%3B&=Y%0Ay%0A%E2%80%98%0A%7B&_x:1&f:3%3B&=%2F:%0A.%0A%C2%B7%0A%E2%80%A6&_x:7&f:3%3B&=Q%0Aq%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23787%2F%3B%3C%2F%2Fspan%3E%0A%C2%B0&_x:1&f:3%3B&=H%0Ah%0A%E2%80%A1%0A%E2%80%A0%3B&@_y:-0.875&x:5&f:3%3B&=K%0Ak%0A%0A~&_x:5&f:3%3B&=%3F%0A%E2%80%99%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23803%2F%3B%3C%2F%2Fspan%3E%0A%C2%BF%3B&@_y:-0.625&f:3%3B&=%C3%8A%0A%C3%AA%0A%0A%2F%2F&_f:3%3B&=%C3%80%0A%C3%A0%0A%0A%5C&_x:13&f:3%3B&=F%0Af%0A%C2%AA%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23808%2F%3B%3C%2F%2Fspan%3E&_f:3%3B&=W%0Aw%0A%0A%3Cspan%20class%2F='cd'%3E%2F&%239676%2F%3B%2F&%23774%2F%3B%3C%2F%2Fspan%3E%3B&@_y:-0.5&x:2.5&c=%23616161&f:3%3B&=%3Ci%20class%2F='kb%20kb-Unicode-Page-Up-3'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Down-3'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-logo-linux-tux'%3E%3C%2F%2Fi%3E&_x:10&fa@:0&:0&:0&:0&:0&:0&:6&:0&:0&:1%3B%3B&=%3Ci%20class%2F='kb%20kb-Line-Start'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Line-End'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Hamburger-Menu'%3E%3C%2F%2Fi%3E%3B&@_rx:4&ry:8.175&y:-4.675&x:-0.5&c=%23a5afff&a:7%3B&=Nav%20Mouse%3B&@_rx:13&y:-4.675&x:-0.5%3B&=Num%20Symb%3B&@_r:15&rx:4&y:-4.675&x:-0.5&c=%23bfc7ff&a:4&fa@:0&:0&:0&:0&:0&:0&:6&:0&:2%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Tab-1'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0AShorcuts%20(hold)%3B&@_r:30&y:-2&x:-0.5&c=%23cccccc&a:7%3B&=%3Ci%20class%2F='mss%20mss-Unicode-BackSpace-DeleteLeft-Big-2'%3E%3C%2F%2Fi%3E%3B&@_x:-0.5&a:4&fa@:1&:0&:1%3B%3B&=nb%2F&%239251%2F%3B%0A%2F&%239251%2F%3B%0Annb%2F&%239251%2F%3B%0A%2F_%3B&@_r:45&y:-2&x:-0.5&a:7&f:3%3B&=Ctrl%3B&@_x:-0.5&f:3%3B&=%E2%87%A7%3B&@_r:-45&rx:13&y:-5.675&x:-0.5&f:3%3B&=AltGr%3B&@_x:-0.5&f:3%3B&=%E2%87%A7%3B&@_r:-30&y:-2&x:-0.5&f:3%3B&=Del%3B&@_x:-0.5&f:3%3B&=%3Ci%20class%2F='kb%20kb-Return-2'%3E%3C%2F%2Fi%3E%3B&@_r:-15&y:-1&x:-0.5&f:3%3B&=Alt)

#### Description

This layer is based on [BÉPO](https://bepo.fr) with some adjustments:

- move of `w` from row 1 to row 3
- replacement of AltGr and AltGr+Shift on `c` to have `ç` and `Ç` (chars becoming unavailable: `©` and `ſ`)
- swap of `'` and `’`

Specific keys:
|Code|Description|
|---|---|
|Clo|Automatically close opened chars `"(«[{` (see [Close char](#Close%20Char) feature for details)|
|AltGr + Clo|Reset buffer of registered char of Close char feature|
|AltGr + Esc|Toggle Caps lock|

### Numeric / Symbols

This is the numeric / symbols / functions layer.

#### Representation

![keyboard-layout-editor - Numeric / Symbols](https://i.imgur.com/F3cp8ZD.png)
[keyboard-layout-editor - Numeric / Symbols](http://www.keyboard-layout-editor.com/##@_backcolor=%23ffffff&name=Kyria%3B&@_x:18.75&c=%23f1f1f1&t=%23646464&fa@:1&:1&:1&:1%3B%3B&=Shift%0Akey%0AAltGr%20Shift%0AAltGr%3B&@_y:-0.75&x:3&c=%23add1ad&t=%23000000&p=R1&fa@:1&:0&:1&:1&:0&:0&:0&:0&:0&:1%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:9&c=%23cccccc%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%3B&@_y:-0.75&x:2&c=%23add1ad%3B&=%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Up-3'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:1%3B&=%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Down-3'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:7&c=%23cccccc%3B&=%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Up-3'%3E%3C%2F%2Fi%3E&_x:1%3B&=%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Down-3'%3E%3C%2F%2Fi%3E%3B&@_y:-0.875&x:5&c=%23add1ad%3B&=%0ABtn%203%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:5&c=%23cccccc%3B&=%0A%3Ci%20class%2F='fa%20fa-cut'%3E%3C%2F%2Fi%3E%3B&@_y:-0.625&f:3%3B&=%0A%0A%0A%3Ci%20class%2F='kb%20kb-Unicode-Lock-Closed-1'%3E%3C%2F%2Fi%3E%E2%87%A7%0A%0A%0AEsc&_a:7%3B&=&_x:13&a:4%3B&=%0A%3Ci%20class%2F='kb%20kb-Unicode-PrintScreen-1'%3E%3C%2F%2Fi%3E&=%0AInsert%3B&@_y:-0.75&x:3&c=%23add1ad&p=R2%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:9&c=%23cccccc%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%3B&@_y:-0.75&x:2&c=%23add1ad%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:1&n:true%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:7&c=%23cccccc&n:true%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E&_x:1%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E%3B&@_y:-0.875&x:5&c=%23add1ad%3B&=%0ABtn%201%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:5&c=%23cccccc%3B&=%0A%3Ci%20class%2F='fa%20fa-copy'%3E%3C%2F%2Fi%3E%3B&@_y:-0.625&fa@:1&:0&:1&:1&:0&:0&:1&:0&:0&:1%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Record'%3E%3C%2F%2Fi%3E%2F%2F%3Ci%20class%2F='kb%20kb-Multimedia-Stop'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AM1%0A%0A%0A%3Ci%20class%2F='fa%20fa-list-ol'%3E%3C%2F%2Fi%3E&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Play'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AM1%0A%0A%0A%3Ci%20class%2F='fa%20fa-list-ol'%3E%3C%2F%2Fi%3E&_x:13&fa@:1&:1&:1&:1%3B%3B&=%0Anext%0A%0Anew%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Search-2'%3E%3C%2F%2Fi%3E&_f:3%3B&=%0A%3Ci%20class%2F='mss%20mss-Undo-5'%3E%3C%2F%2Fi%3E%3B&@_y:-0.75&x:3&p=R3&a:7%3B&=&_x:9%3B&=%3B&@_y:-0.75&x:2&c=%23add1ad&a:4&fa@:1&:0&:1&:1&:0&:0&:0&:0&:0&:1%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Left-Circle-Filled'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:1%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Right-Circle-Filled'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:7&c=%23cccccc%3B&=%0A%3Ci%20class%2F='kb%20kb-Line-Start'%3E%3C%2F%2Fi%3E&_x:1%3B&=%0A%3Ci%20class%2F='kb%20kb-Line-End'%3E%3C%2F%2Fi%3E%3B&@_y:-0.875&x:5&c=%23add1ad%3B&=%0ABtn%202%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:5&c=%23cccccc%3B&=%0A%3Ci%20class%2F='fa%20fa-paste'%3E%3C%2F%2Fi%3E%3B&@_y:-0.625&fa@:1&:0&:1&:1&:0&:0&:1&:0&:0&:1%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Record'%3E%3C%2F%2Fi%3E%2F%2F%3Ci%20class%2F='kb%20kb-Multimedia-Stop'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AM2%0A%0A%0A%3Ci%20class%2F='fa%20fa-list-ol'%3E%3C%2F%2Fi%3E&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Play'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AM2%0A%0A%0A%3Ci%20class%2F='fa%20fa-list-ol'%3E%3C%2F%2Fi%3E&_x:13&fa@:1&:2%3B%3B&=%0AReplace&_f:3%3B&=%0A%3Ci%20class%2F='mss%20mss-Redo-2'%3E%3C%2F%2Fi%3E%3B&@_y:-0.5&x:2.5&c=%23616161&f:3%3B&=%3Ci%20class%2F='kb%20kb-Unicode-Page-Up-3'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Down-3'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-logo-linux-tux'%3E%3C%2F%2Fi%3E&_x:10&fa@:0&:0&:0&:0&:0&:0&:0&:0&:0&:1%3B%3B&=%3Ci%20class%2F='kb%20kb-Line-Start'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Line-End'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Hamburger-Menu'%3E%3C%2F%2Fi%3E%3B&@_rx:4&ry:8.175&y:-4.675&x:-0.5&c=%23a5afff&a:7%3B&=Alpha%3B&@_rx:13&y:-4.675&x:-0.5%3B&=Media%20RGB%3B&@_r:15&rx:4&y:-4.675&x:-0.5&c=%23bfc7ff&a:4&fa@:0&:0&:0&:0&:0&:0&:0&:0&:2%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Tab-1'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0AShortcuts%20(hold)%3B&@_r:30&y:-2&x:-0.5&c=%23cccccc&a:7%3B&=%3Ci%20class%2F='mss%20mss-Unicode-BackSpace-DeleteLeft-Big-2'%3E%3C%2F%2Fi%3E%3B&@_x:-0.5&a:4&fa@:1&:0&:1%3B%3B&=nb%2F&%239251%2F%3B%0A%2F&%239251%2F%3B%0Annb%2F&%239251%2F%3B%0A%2F_%3B&@_r:45&y:-2&x:-0.5&a:7&f:3%3B&=Ctrl%3B&@_x:-0.5&f:3%3B&=%E2%87%A7%3B&@_r:-45&rx:13&y:-5.675&x:-0.5&f:3%3B&=AltGr%3B&@_x:-0.5&f:3%3B&=%E2%87%A7%3B&@_r:-30&y:-2&x:-0.5&f:3%3B&=Del%3B&@_x:-0.5&f:3%3B&=%3Ci%20class%2F='kb%20kb-Return-2'%3E%3C%2F%2Fi%3E%3B&@_r:-15&y:-1&x:-0.5&f:3%3B&=Alt)

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

![keyboard-layout-editor - Navigation / Mouse](https://i.imgur.com/57bvUTB.png)
[keyboard-layout-editor - Navigation / Mouse](http://www.keyboard-layout-editor.com/##@_backcolor=%23ffffff&name=Kyria%3B&@_x:18.75&c=%23f1f1f1&t=%23646464&fa@:1&:1&:1&:1%3B%3B&=Shift%0Akey%0AAltGr%20Shift%0AAltGr%3B&@_y:-0.75&x:3&c=%23add1ad&t=%23000000&p=R1&fa@:1&:0&:1&:1&:0&:0&:0&:0&:0&:1%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:9&c=%23cccccc%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%3B&@_y:-0.75&x:2&c=%23add1ad%3B&=%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Up-3'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:1%3B&=%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Down-3'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:7&c=%23cccccc%3B&=%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Up-3'%3E%3C%2F%2Fi%3E&_x:1%3B&=%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Down-3'%3E%3C%2F%2Fi%3E%3B&@_y:-0.875&x:5&c=%23add1ad%3B&=%0ABtn%203%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:5&c=%23cccccc%3B&=%0A%3Ci%20class%2F='fa%20fa-cut'%3E%3C%2F%2Fi%3E%3B&@_y:-0.625&f:3%3B&=%0A%0A%0A%3Ci%20class%2F='kb%20kb-Unicode-Lock-Closed-1'%3E%3C%2F%2Fi%3E%E2%87%A7%0A%0A%0AEsc&_a:7%3B&=&_x:13&a:4%3B&=%0A%3Ci%20class%2F='kb%20kb-Unicode-PrintScreen-1'%3E%3C%2F%2Fi%3E&=%0AInsert%3B&@_y:-0.75&x:3&c=%23add1ad&p=R2%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:9&c=%23cccccc%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%3B&@_y:-0.75&x:2&c=%23add1ad%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:1&n:true%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:7&c=%23cccccc&n:true%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E&_x:1%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E%3B&@_y:-0.875&x:5&c=%23add1ad%3B&=%0ABtn%201%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:5&c=%23cccccc%3B&=%0A%3Ci%20class%2F='fa%20fa-copy'%3E%3C%2F%2Fi%3E%3B&@_y:-0.625&fa@:1&:0&:1&:1&:0&:0&:1&:0&:0&:1%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Record'%3E%3C%2F%2Fi%3E%2F%2F%3Ci%20class%2F='kb%20kb-Multimedia-Stop'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AM1%0A%0A%0A%3Ci%20class%2F='fa%20fa-list-ol'%3E%3C%2F%2Fi%3E&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Play'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AM1%0A%0A%0A%3Ci%20class%2F='fa%20fa-list-ol'%3E%3C%2F%2Fi%3E&_x:13&fa@:1&:1&:1&:1%3B%3B&=%0Anext%0A%0Anew%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Search-2'%3E%3C%2F%2Fi%3E&_f:3%3B&=%0A%3Ci%20class%2F='mss%20mss-Undo-5'%3E%3C%2F%2Fi%3E%3B&@_y:-0.75&x:3&p=R3&a:7%3B&=&_x:9%3B&=%3B&@_y:-0.75&x:2&c=%23add1ad&a:4&fa@:1&:0&:1&:1&:0&:0&:0&:0&:0&:1%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Left-Circle-Filled'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:1%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Right-Circle-Filled'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:7&c=%23cccccc%3B&=%0A%3Ci%20class%2F='kb%20kb-Line-Start'%3E%3C%2F%2Fi%3E&_x:1%3B&=%0A%3Ci%20class%2F='kb%20kb-Line-End'%3E%3C%2F%2Fi%3E%3B&@_y:-0.875&x:5&c=%23add1ad%3B&=%0ABtn%202%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='fa%20fa-mouse-pointer'%3E%3C%2F%2Fi%3E&_x:5&c=%23cccccc%3B&=%0A%3Ci%20class%2F='fa%20fa-paste'%3E%3C%2F%2Fi%3E%3B&@_y:-0.625&fa@:1&:0&:1&:1&:0&:0&:1&:0&:0&:1%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Record'%3E%3C%2F%2Fi%3E%2F%2F%3Ci%20class%2F='kb%20kb-Multimedia-Stop'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AM2%0A%0A%0A%3Ci%20class%2F='fa%20fa-list-ol'%3E%3C%2F%2Fi%3E&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Play'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AM2%0A%0A%0A%3Ci%20class%2F='fa%20fa-list-ol'%3E%3C%2F%2Fi%3E&_x:13&fa@:1&:2%3B%3B&=%0AReplace&_f:3%3B&=%0A%3Ci%20class%2F='mss%20mss-Redo-2'%3E%3C%2F%2Fi%3E%3B&@_y:-0.5&x:2.5&c=%23616161&f:3%3B&=%3Ci%20class%2F='kb%20kb-Unicode-Page-Up-3'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Down-3'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-logo-linux-tux'%3E%3C%2F%2Fi%3E&_x:10&fa@:0&:0&:0&:0&:0&:0&:0&:0&:0&:1%3B%3B&=%3Ci%20class%2F='kb%20kb-Line-Start'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Line-End'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Hamburger-Menu'%3E%3C%2F%2Fi%3E%3B&@_rx:4&ry:8.175&y:-4.675&x:-0.5&c=%23a5afff&a:7%3B&=Alpha%3B&@_rx:13&y:-4.675&x:-0.5%3B&=Media%20RGB%3B&@_r:15&rx:4&y:-4.675&x:-0.5&c=%23bfc7ff&a:4&fa@:0&:0&:0&:0&:0&:0&:0&:0&:2%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Tab-1'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0AShortcuts%20(hold)%3B&@_r:30&y:-2&x:-0.5&c=%23cccccc&a:7%3B&=%3Ci%20class%2F='mss%20mss-Unicode-BackSpace-DeleteLeft-Big-2'%3E%3C%2F%2Fi%3E%3B&@_x:-0.5&a:4&fa@:1&:0&:1%3B%3B&=nb%2F&%239251%2F%3B%0A%2F&%239251%2F%3B%0Annb%2F&%239251%2F%3B%0A%2F_%3B&@_r:45&y:-2&x:-0.5&a:7&f:3%3B&=Ctrl%3B&@_x:-0.5&f:3%3B&=%E2%87%A7%3B&@_r:-45&rx:13&y:-5.675&x:-0.5&f:3%3B&=AltGr%3B&@_x:-0.5&f:3%3B&=%E2%87%A7%3B&@_r:-30&y:-2&x:-0.5&f:3%3B&=Del%3B&@_x:-0.5&f:3%3B&=%3Ci%20class%2F='kb%20kb-Return-2'%3E%3C%2F%2Fi%3E%3B&@_r:-15&y:-1&x:-0.5&f:3%3B&=Alt)

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

![keyboard-layout-editor - Media / RGB](https://i.imgur.com/dXLznnC.png)
[keyboard-layout-editor - Media / RGB](http://www.keyboard-layout-editor.com/##@_backcolor=%23ffffff&name=Kyria%3B&@_x:18.75&c=%23f1f1f1&t=%23646464&fa@:1&:1&:1&:1%3B%3B&=Shift%0Akey%0AAltGr%20Shift%0AAltGr%3B&@_y:-0.75&x:3&c=%23a5c3e6&t=%23000000&p=R1&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0ASat&_x:9&fa@:1&:2%3B%3B&=%0ASnake%0A%0A%0A%0A%0AMode%3B&@_y:-0.75&x:2&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0AHue&_x:1&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0AValue&_x:7&f:3%3B&=%0ABreath%0A%0A%0A%0A%0AMode&_x:1&f:3%3B&=%0AGradient%0A%0A%0A%0A%0AMode%3B&@_y:-0.875&x:5&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0ASpeed&_x:5&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AMode%3B&@_y:-0.625&c=%23cccccc&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Unicode-Screen-Bright'%3E%3C%2F%2Fi%3E&_c=%23a5c3e6&fa@:1&:2&:0&:1%3B%3B&=%0A%0A%0Aeepr%0A%0A%0AToggle&_x:13%3B&=%0ARainbow%0A%0A%0A%0A%0AMode&_c=%23d192d9%3B&=%0A%0A%0Atgl%C2%A0eepr%0A%0A%0AToggle%3B&@_y:-0.75&x:3&c=%23a5c3e6&p=R2&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0ASat&_x:9&f:3%3B&=%0ASwirl%0A%0A%0A%0A%0AMode%3B&@_y:-0.75&x:2&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0AHue&_x:1&f:3&n:true%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0AValue&_x:7&f:3&n:true%3B&=%0AKnight%0A%0A%0A%0A%0AMode&_x:1&f:3%3B&=%0AXmas%0A%0A%0A%0A%0AMode%3B&@_y:-0.875&x:5&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0ASpeed&_x:5&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AMode%3B&@_y:-0.625&c=%23cccccc&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Unicode-Screen-Bright'%3E%3C%2F%2Fi%3E&_c=%23a5c3e6&f:3%3B&=%0APlain&_x:13&c=%23cccccc&a:7%3B&=&_c=%23d192d9&a:4%3B&=%0A%0A%0Aeepr%0A%0A%0ACycle%20animat.%3B&@_y:-0.75&x:3&c=%23f2ac9d&p=R3&fa@:1&:0&:0&:1&:0&:0&:0&:0&:0&:1%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-logo-windows-8'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0AUnicode&_x:9&c=%23cccccc&a:7%3B&=%3B&@_y:-0.75&x:2&c=%23f2ac9d&a:4%3B&=%0A%3Ci%20class%2F='kb%20kb-logo-linux-tux'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0AUnicode&_x:1%3B&=%0A%3Ci%20class%2F='kb%20kb-logo-windows-8'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0AUnicode&_x:7&c=%23cccccc&a:7%3B&=&_x:1%3B&=%3B&@_y:-0.875&x:5&c=%23f2ac9d&a:4%3B&=%0A%3Ci%20class%2F='kb%20kb-logo-apple'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0AUnicode&_x:5&c=%23cccccc&a:7%3B&=%3B&@_y:-0.625&c=%23f2ac9d&a:4%3B&=%0AToggle%0A%0A%0A%0A%0A%0A%0A%0AUnicode&=%0ACycle%0A%0A%0A%0A%0A%0A%0A%0AUnicode&_x:13&c=%23d192d9&fa@:1&:1%3B%3B&=%0AStart%2F%2Fstop%20Pomodoro&_f:3%3B&=%0AInit%20animat.%3B&@_y:-0.5&x:2.5&c=%23616161&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Volume-Down-1'%3E%3C%2F%2Fi%3E%0A%0A%3Ci%20class%2F='kb%20kb-Multimedia-Volume-Up-2'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Multimedia-Mute-2'%3E%3C%2F%2Fi%3E&_x:10&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Rewind-Start'%3E%3C%2F%2Fi%3E%0A%0A%3Ci%20class%2F='kb%20kb-Multimedia-FastForward-End'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Multimedia-Play-Pause'%3E%3C%2F%2Fi%3E%3B&@_rx:4&ry:8.175&y:-4.675&x:-0.5&c=%23a5afff&a:7&f:3%3B&=Alpha%3B&@_rx:13&y:-4.675&x:-0.5&f:3%3B&=Num%20Symb%3B&@_r:15&rx:4&y:-4.675&x:-0.5&c=%23bfc7ff&a:4&fa@:1&:0&:0&:0&:0&:0&:0&:0&:2%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Tab-1'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0AShortcuts%20(hold)%3B&@_r:30&y:-2&x:-0.5&c=%23cccccc&a:7&f:3%3B&=%3Ci%20class%2F='mss%20mss-Unicode-BackSpace-DeleteLeft-Big-2'%3E%3C%2F%2Fi%3E%3B&@_x:-0.5&a:4&fa@:1&:0&:1%3B%3B&=nb%2F&%239251%2F%3B%0A%2F&%239251%2F%3B%0Annb%2F&%239251%2F%3B%0A%2F_%3B&@_r:45&y:-2&x:-0.5&a:7&f:3%3B&=Ctrl%3B&@_x:-0.5&f:3%3B&=%E2%87%A7%3B&@_r:-45&rx:13&y:-5.675&x:-0.5&f:3%3B&=AltGr%3B&@_x:-0.5&f:3%3B&=%E2%87%A7%3B&@_r:-30&y:-2&x:-0.5&f:3%3B&=Del%3B&@_x:-0.5&f:3%3B&=%3Ci%20class%2F='kb%20kb-Return-2'%3E%3C%2F%2Fi%3E%3B&@_r:-15&y:-1&x:-0.5&f:3%3B&=Alt)

#### Description

Specific keys:
|Code|Description|
|---|---|
|Toggle RGB|Toggle RGB - Store current RGB status in EEPROM with AltGr|
|Toggle OLED2<sup>1</sup>|Toggle OLED of follower halve - Store current status in EEPROM with AltGr|
|Init animation<sup>1</sup>|Reinitialize animation on follower OLED|
|Cycle animations<sup>1</sup>|Cycle throw available animations - Store current animation in EEPROM with AltGr|
|Start/Stop pomodoro|Start (or stop) a timer of 25 minutes|

*<sup>1</sup>: Warn: works only with the implementation of custom transport between halves*

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

### Shortcuts

This is the shortcuts layer.

#### Representation

![keyboard-layout-editor - Shortcuts](https://i.imgur.com/T48J47Z.png)
[keyboard-layout-editor - Shortcuts](http://www.keyboard-layout-editor.com/##@_backcolor=%23ffffff&name=Kyria%3B&@_x:18.75&c=%23f1f1f1&t=%23646464&fa@:1&:1&:1&:1%3B%3B&=Shift%0Akey%0AAltGr%20Shift%0AAltGr%3B&@_y:-0.75&x:3&c=%23cccccc&t=%23000000&p=R1&a:7%3B&=&_x:9&a:4&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%3B&@_y:-0.75&x:2&f:3%3B&=%0ANew%20tab&_x:1&f:3%3B&=%0A%3Ci%20class%2F='mss%20mss-Undo-5'%3E%3C%2F%2Fi%3E&_x:7&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Up-3'%3E%3C%2F%2Fi%3E&_x:1&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Down-3'%3E%3C%2F%2Fi%3E%3B&@_y:-0.875&x:5&f:3%3B&=%0A%3Ci%20class%2F='mss%20mss-Redo-2'%3E%3C%2F%2Fi%3E&_x:5&f:3%3B&=%0AShift%20word%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E%3B&@_y:-0.625&f:3%3B&=%0A%0A%0A%3Ci%20class%2F='kb%20kb-Unicode-Lock-Closed-1'%3E%3C%2F%2Fi%3E%E2%87%A7%0A%0A%0AEsc&_a:7%3B&=&_x:13&a:4&f:3%3B&=%0AShift%20word%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E&_a:7%3B&=%3B&@_y:-0.75&x:3&p=R2&a:4&f:3%3B&=%0A%3Ci%20class%2F='fa%20fa-copy'%3E%3C%2F%2Fi%3E&_x:9&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%3B&@_y:-0.75&x:2&f:3%3B&=%0A%3Ci%20class%2F='fa%20fa-cut'%3E%3C%2F%2Fi%3E&_x:1&f:3&n:true%3B&=%0A%3Ci%20class%2F='fa%20fa-paste'%3E%3C%2F%2Fi%3E&_x:7&f:3&n:true%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E&_x:1&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E%3B&@_y:-0.875&x:5&a:7%3B&=&_x:5&a:4&f:3%3B&=%0Aword%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E%3B&@_y:-0.625&fa@:1&:0&:1&:1&:0&:0&:1&:0&:0&:1%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Record'%3E%3C%2F%2Fi%3E%2F%2F%3Ci%20class%2F='kb%20kb-Multimedia-Stop'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AM1%0A%0A%0A%3Ci%20class%2F='fa%20fa-list-ol'%3E%3C%2F%2Fi%3E&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Play'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AM1%0A%0A%0A%3Ci%20class%2F='fa%20fa-list-ol'%3E%3C%2F%2Fi%3E&_x:13%3B&=%0Aword%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E&_a:7%3B&=%3B&@_y:-0.75&x:3&p=R3&a:4&fa@:1&:2%3B%3B&=%0AReplace&_x:9&a:7%3B&=%3B&@_y:-0.75&x:2&a:4&f:3%3B&=%0AClose&_x:1&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Search-2'%3E%3C%2F%2Fi%3E&_x:7&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Line-Start'%3E%3C%2F%2Fi%3E&_x:1&f:3%3B&=%0A%3Ci%20class%2F='kb%20kb-Line-End'%3E%3C%2F%2Fi%3E%3B&@_y:-0.875&x:5%3B&=%0ANext%20%3Ci%20class%2F='kb%20kb-Search-2'%3E%3C%2F%2Fi%3E&_x:5&f:3%3B&=%0AShift%20%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E%3B&@_y:-0.625&fa@:1&:0&:0&:0&:0&:0&:1&:0&:0&:1%3B%3B&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Record'%3E%3C%2F%2Fi%3E%2F%2F%3Ci%20class%2F='kb%20kb-Multimedia-Stop'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AM2%0A%0A%0A%3Ci%20class%2F='fa%20fa-list-ol'%3E%3C%2F%2Fi%3E&=%0A%3Ci%20class%2F='kb%20kb-Multimedia-Play'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0AM2%0A%0A%0A%3Ci%20class%2F='fa%20fa-list-ol'%3E%3C%2F%2Fi%3E&_x:13%3B&=%0AShift%20%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E&_a:7%3B&=%3B&@_y:-0.5&x:2.5&c=%23616161&a:4&f:3%3B&=%3Ci%20class%2F='kb%20kb-Unicode-Page-Up-3'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Unicode-Page-Down-3'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-logo-linux-tux'%3E%3C%2F%2Fi%3E&_x:10&fa@:0&:0&:0&:0&:0&:0&:1&:0&:0&:1%3B%3B&=%3Ci%20class%2F='kb%20kb-Line-Start'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Line-End'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Hamburger-Menu'%3E%3C%2F%2Fi%3E%3B&@_rx:4&ry:8.175&y:-4.675&x:-0.5&c=%23a5afff&a:7%3B&=Nav%20Mouse%3B&@_rx:13&y:-4.675&x:-0.5%3B&=Num%20Symb%3B&@_r:15&rx:4&y:-4.675&x:-0.5&c=%23bfc7ff&a:5&fa@:2%3B%3B&=Shortcuts%20(hold)%3B&@_r:30&y:-2&x:-0.5&c=%23cccccc&a:7&f:3%3B&=%3Ci%20class%2F='mss%20mss-Unicode-BackSpace-DeleteLeft-Big-2'%3E%3C%2F%2Fi%3E%3B&@_x:-0.5&a:4&fa@:1&:0&:1%3B%3B&=nb%2F&%239251%2F%3B%0A%2F&%239251%2F%3B%0Annb%2F&%239251%2F%3B%0A%2F_%3B&@_r:45&y:-2&x:-0.5&a:7&f:3%3B&=Ctrl%3B&@_x:-0.5&f:3%3B&=%E2%87%A7%3B&@_r:-45&rx:13&y:-5.675&x:-0.5&f:3%3B&=AltGr%3B&@_x:-0.5&f:3%3B&=%E2%87%A7%3B&@_r:-30&y:-2&x:-0.5&f:3%3B&=Del%3B&@_x:-0.5&f:3%3B&=%3Ci%20class%2F='kb%20kb-Return-2'%3E%3C%2F%2Fi%3E%3B&@_r:-15&y:-1&x:-0.5&f:3%3B&=Alt)

#### Description

All the classic shortcuts in direct access on left halve, thus, shortcuts can be done one hand.

Navigation keys are on right halve.

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

!> It is not based on a real-time tick, so the countdown is not fully accurate.

#### Configuration

Activation of pomodoro is done in file `config.h`:

```c
#define POMODORO_TIMER 25 // time of pomodoro in minutes
```

### Custom transport

Custom transport between halves is used to transfer commands from master to follower.
Implementation is a simple overload of standard implementation only adding a data sent from master to follower.

Commands sent *(if related feature is activated)*:

- set OLED follower on or off
- change animation to display
- re-start animation
- start/stop pomodoro timer

#### Configuration

Activation is done in file `rules.mk`:

```c
SPLIT_TRANSPORT = custom
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
|Quadrigrams|
|`a` + `i`|Write quadrigram: aire|`aire`|
|`d` + `a`|Write quadrigram: dans|`dans`|
|`e` + `l`|Write quadrigram: elle|`elle`|
|`e` + `t`|Write quadrigram: ette|`ette`|
|`e` + `n`|Write quadrigram: ente|`ente`|
|`i` + `l`|Write quadrigram: ille|`ille`|
|`i` + `q`|Write quadrigram: ique|`ique`|
|`m` + `e`|Write quadrigram: ment|`ment`|
|`o` + `m`|Write quadrigram: omme|`omme`|
|`o` + `n`|Write quadrigram: onne|`onne`|
|`p` + `o`|Write quadrigram: pour|`pour`|
|`q` + `u`|Write quadrigram: quel|`quel`|
|`t` + `i`|Write quadrigram: tion|`tion`|
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
|`t` + `.`|Write `. ` and hold shift for next key |`. ` + hold Shift until next key *(if OSM is enabled)*|
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

See [HID Host](hid_host/readme.md) for the host side.

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
For each item, information are listed and font is reversed on activate modifiers.

Items:

- Layers
  - Hightest active layer (in uppercase for alpha if caps lock is activated)
- Modifiers
  - Shift
  - Ctrl
  - Gui
  - Alt
  - AltGr
- Dynamic macros
  - Macro 1 (Play/Record, Warning)
  - Macro 2 (Play/Record, Warning)

#### Representation

![Status display](https://i.imgur.com/hfVNJ3K.png)

### Follower screen

The follower screen is used to display fun animations.
Animations may be included simultaneously and cycle throw with the key C_OLED2_ANIMATION_CYCLE.

!> The cycle can only work with custom transport enabled.

#### Bongo cat

This animation is featuring [bongo cat](https://bongo-cat.glitch.me/) tapping on a 6 keys' keyboard.

![paws up](https://imgur.com/LkryRFS.png) ![left paw on 1st key](https://imgur.com/EkrcZRO.png) ![paws up](https://imgur.com/LkryRFS.png) ![right paw on 5th key](https://imgur.com/cm8Wxla.png) […]

This animation can be synchronized with WPM feature to rhythm animation.
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

!> If WPM is not enabled, the screen never goes off.

##### Configuration

Activation of oled display is done in file `rules.mk`:

```c
OLED_DRIVER_ENABLE = yes
```

Activation of follower halve animation of game of life is done in file `config.h`:

```c
#define LIFE_ANIMATION
```

#### Starfield

This animation is featuring a starfield animation.
It was first developed by @GauthamYerroju

##### Configuration

Activation of oled display is done in file `rules.mk`:

```c
OLED_DRIVER_ENABLE = yes
```

Activation of follower halve animation of starfield is done in file `config.h`:

```c
#define STARLIGHT_ANIMATION
```

Optional activation of synchronization of follower halve animation on user currently tapping speed is done in file `rules.mk`:

```c
WPM_ENABLE = yes
```

#### Pomodoro animation

This animation is an abstract representation of the pomodoro feature.
It displays blank pixels to represent the remaining time. Black pixels are randomly placed and their number increments when time goes.

It needs to have following activated features to work: [Pomodoro](#Pomodoro) and custom transport data between halves.

##### Configuration

Activation of oled display is done in file `rules.mk`:

```c
OLED_DRIVER_ENABLE = yes
```

Activation of pomodoro animation is done in file `config.h`:

```c
#define POMODORO_ANIMATION
```

#### Oneko

This animation is a cat playing and walking around the screen: [Oneko](https://github.com/tie/oneko).

![Oneko awake](https://i.imgur.com/xrOCJOP.png)
![Oneko jare](https://i.imgur.com/jfUK6CF.png)
![Oneko left1](https://i.imgur.com/Z8wDANp.png)
![Oneko left2](https://i.imgur.com/DM66ZOw.png)

!> If WPM is not enabled, the screen never goes off.

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

Physical LEDs position related to keys
Master and follower may be swapped (right / left), 0-9 are always on master, 10-19 on follower.

![keyboard-layout-editor - LEDs](https://i.imgur.com/z5mO3Db.png)
[keyboard-layout-editor - LEDs](http://www.keyboard-layout-editor.com/##@_name=Kyria%3B&@_y:0.25&x:3&g:true&a:7%3B&=&_x:-0.25&c=%23ff0000&g:false&w:0.5&h:0.5%3B&=4&_x:8.5&w:0.5&h:0.5%3B&=14&_x:-0.25&c=%23cccccc&g:true%3B&=%3B&@_y:-0.75&x:0.25&c=%23ff0000&g:false&w:0.5&h:0.5%3B&=9&_x:0.5&w:0.5&h:0.5%3B&=5&_x:0.25&c=%23cccccc&g:true%3B&=&_x:1%3B&=&_x:7%3B&=&_x:1%3B&=&_x:0.25&c=%23ff0000&g:false&w:0.5&h:0.5%3B&=19&_x:0.5&w:0.5&h:0.5%3B&=15%3B&@_y:-0.875&x:5&c=%23cccccc&g:true%3B&=&_x:5%3B&=%3B&@_y:-0.625%3B&=&=&_x:13%3B&=&=%3B&@_y:-0.75&x:3%3B&=&_x:1.25&c=%23ff0000&g:false&w:0.5&h:0.5%3B&=3&_x:5.5&w:0.5&h:0.5%3B&=13&_x:1.25&c=%23cccccc&g:true%3B&=%3B&@_y:-0.75&x:2%3B&=&_x:1%3B&=&_x:7%3B&=&_x:1%3B&=%3B&@_y:-0.875&x:5%3B&=&_x:5%3B&=%3B&@_y:-0.625%3B&=&=&_x:13%3B&=&=%3B&@_y:-0.75&x:3%3B&=&_x:9%3B&=%3B&@_y:-0.75&x:2%3B&=&_x:1%3B&=&_x:7%3B&=&_x:1%3B&=%3B&@_y:-0.875&x:5%3B&=&_x:5%3B&=%3B&@_y:-0.875&x:0.25&c=%23ff0000&g:false&w:0.5&h:0.5%3B&=8&_x:0.5&w:0.5&h:0.5%3B&=6&_x:13.5&w:0.5&h:0.5%3B&=18&_x:0.5&w:0.5&h:0.5%3B&=16%3B&@_y:-0.75&c=%23cccccc&g:true%3B&=&=&_x:13%3B&=&=%3B&@_y:-0.75&x:2.5&c=%23ff0000&g:false&w:0.5&h:0.5%3B&=7&_x:1.25&w:0.5&h:0.5%3B&=2&_x:7.5&w:0.5&h:0.5%3B&=12&_x:1.25&w:0.5&h:0.5%3B&=17%3B&@_y:-0.75&x:2.5&c=%23cccccc&g:true%3B&=&_x:2&c=%23ff0000&g:false&w:0.5&h:0.5%3B&=1&_x:5&w:0.5&h:0.5%3B&=11&_x:2&c=%23cccccc&g:true%3B&=%3B&@_y:-0.75&x:7&c=%23ff0000&g:false&w:0.5&h:0.5%3B&=0&_x:2&w:0.5&h:0.5%3B&=10%3B&@_rx:4&ry:8.175&y:-4.675000000000001&x:-0.5&c=%23cccccc&g:true%3B&=%3B&@_rx:13&y:-4.675000000000001&x:-0.5%3B&=%3B&@_r:15&rx:4&y:-4.675000000000001&x:-0.5%3B&=%3B&@_r:30&y:-2&x:-0.5%3B&=%3B&@_x:-0.5%3B&=%3B&@_r:45&y:-2&x:-0.5%3B&=%3B&@_x:-0.5%3B&=%3B&@_r:-45&rx:13&y:-5.675000000000001&x:-0.5%3B&=%3B&@_x:-0.5%3B&=%3B&@_r:-30&y:-2&x:-0.5%3B&=%3B&@_x:-0.5%3B&=%3B&@_r:-15&y:-1&x:-0.5%3B&=)

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
|[oled_gfx_starfield.c](oled_gfx_starfield.c)|Implementation of starfield animation|
|[oled.h](oled.h)|Definition of OLED external called functions|
|[rgb.h](rgb.h)|Definition of RGB external called functions|
|[rgb.c](rgb.c)|Implementation of RGB behavior|
|[tap_dance.h](tap_dance.h)|Definition of tap dance keys|
|[tap_dance.c](tap_dance.c)|Implementation of tap dance keys behavior|
|[transport_custom.c](transport_custom.c)|Implementation of custom protocol between the two halves|
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
|[opt] STARFIELD_ANIMATION *(option of OLED)* – *(by `#define`)*|*tbd*|*tbd*|
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
- [keyboard layout editor (link for Kyria)](http://www.keyboard-layout-editor.com/##@_name=Kyria%3B&@_y:0.25&x:3&a:7%3B&=&_x:9%3B&=%3B&@_y:-0.75&x:2%3B&=&_x:1%3B&=&_x:7%3B&=&_x:1%3B&=%3B&@_y:-0.875&x:5%3B&=&_x:5%3B&=%3B&@_y:-0.625%3B&=&=&_x:13%3B&=&=%3B&@_y:-0.75&x:3%3B&=&_x:9%3B&=%3B&@_y:-0.75&x:2%3B&=&_x:1%3B&=&_x:7%3B&=&_x:1%3B&=%3B&@_y:-0.875&x:5%3B&=&_x:5%3B&=%3B&@_y:-0.625%3B&=&=&_x:13%3B&=&=%3B&@_y:-0.75&x:3%3B&=&_x:9%3B&=%3B&@_y:-0.75&x:2%3B&=&_x:1%3B&=&_x:7%3B&=&_x:1%3B&=%3B&@_y:-0.875&x:5%3B&=&_x:5%3B&=%3B&@_y:-0.625%3B&=&=&_x:13%3B&=&=%3B&@_y:-0.5&x:2.5%3B&=&_x:10%3B&=%3B&@_rx:4&ry:8.175&y:-4.675000000000001&x:-0.5%3B&=%3B&@_rx:13&y:-4.675000000000001&x:-0.5%3B&=%3B&@_r:15&rx:4&y:-4.675000000000001&x:-0.5%3B&=%3B&@_r:30&y:-2&x:-0.5%3B&=%3B&@_x:-0.5%3B&=%3B&@_r:45&y:-2&x:-0.5%3B&=%3B&@_x:-0.5%3B&=%3B&@_r:-45&rx:13&y:-5.675000000000001&x:-0.5%3B&=%3B&@_x:-0.5%3B&=%3B&@_r:-30&y:-2&x:-0.5%3B&=%3B&@_x:-0.5%3B&=%3B&@_r:-15&y:-1&x:-0.5%3B&=)

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
