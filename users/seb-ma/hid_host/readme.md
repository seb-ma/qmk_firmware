# HID interface

## Description

This application is the host interface communicating over HID interface with a keyboard.
It currently only support `kyria:seb-ma` keyboard but may be adapted.

This application is a basic window that displays the layer currently active and the different locks active on keyboard.

It is highly dependant of HID keyboard implementation.
See for [HID device](../readme.md#HID) the device side.

## Dependencies

This application has following dependencies:

- Linux dependencies:
  - `libhidapi-hidraw0` or `libhidapi-libusb0` or `hidapi` (according to distribution)
- Python dependencies:
  - [pyhidapi](https://pypi.org/project/hid/) (available on PyPI: pip install hid)
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
