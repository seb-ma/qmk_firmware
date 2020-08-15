# HID interface

## Description

This application is the host interface communicating over HID interface with a keyboard.
It currently only support `kyria:seb-ma` keyboard but may be adapted.

This application is a basic window that displays the layer currently active and the different locks active on keyboard.

It is highly dependant of HID keyboard implementation.
See for [HID device](../readme.md#HID) the device side.

!> Currently WIP: usage_page and usage are not working properly (not filled by enumerate). This application can't work until fix is found.

## Dependencies

This application has following dependencies:

- OS dependencies:
  - python-dev
  - libudev-dev
- Python dependencies:
  - [cython-hidapi](https://github.com/trezor/cython-hidapi) - available on PyPI: sudo pip install --install-option="--without-libusb" hidapi
    - must use the Kernel's hidraw driver - Implementation in libusb prevents from using hid usage pages: https://github.com/libusb/hidapi/blob/master/libusb/hid.c#L598
    - WARN: may be in conflict with [pyhidapi](https://pypi.org/project/hid/) if installed
    - WARN 2: [patch](https://github.com/Foxboron/archlinux-pkgbuilds/blob/master/python-hidapi/revert-hid_get_input_report.patch) due to `missing undefined symbol: hid_get_input_report`
  - [tkinter](https://docs.python.org/library/tk.html)

## Usage as non-root

udev rules must be defined to allow usb communication without being `root`:

- add udev rules:

Create file `/etc/udev/rules.d/80-qmk-hid.rules` with following content

```bash
SUBSYSTEM=="hidraw", ATTRS{idVendor}=="feed", ATTRS{idProduct}=="0000", MODE="0660", TAG+="uaccess" RUN{builtin}+="uaccess"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="feed", ATTRS{idProduct}=="0000", MODE="0660", TAG+="uaccess" RUN{builtin}+="uaccess"
KERNEL=="hidraw*", ATTRS{busnum}=="1", ATTRS{idVendor}=="feed", ATTRS{idProduct}=="0000", MODE="0666"
```

- then reload: ```udevadm control --reload-rules```

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
