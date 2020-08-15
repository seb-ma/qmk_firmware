#!/usr/bin/python3
# -*- coding: utf-8 -*-
"""
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
"""

from __future__ import annotations # only needed to specify return type of class itself
import abc
import argparse
import enum
import hid
import tkinter
import threading
import signal
import sys

"""
HID communication between keyboard Kyria:seb-ma (vendorID = 0xFEED, productID = 0x0000) and host.
This application is a basic window that displays the layer currently active and the different locks active on keyboard.
It is highly dependant of HID keyboard implementation.

!> Currently WIP: usage_page and usage are not working properly (not filled by enumerate). This application can't work until fix is found.

This application has following dependencies:
- OS dependencies:
  - python-dev
  - libudev-dev
- Python dependencies:
  - [cython-hidapi](https://github.com/trezor/cython-hidapi) - available on PyPI: sudo pip install --install-option="--without-libusb" --install-option="--with-system-hidapi" hidapi
    - must use the Kernel's hidraw driver - Linux implementation in libusb prevents from using hid usage pages: https://github.com/libusb/hidapi/blob/master/libusb/hid.c#L598
    - WARN: may be in conflict with [pyhidapi](https://pypi.org/project/hid/) if installed
  - [tkinter](https://docs.python.org/library/tk.html)

udev rules must be defined to allow usb communication:
  - add udev rules: see https://beta.docs.qmk.fm/faqs/faq_build
  - then reload: udevadm control --reload-rules

"""

class HidCommand(enum.Enum):
    """ List of commands sent between device and host over HID interface
    This is dependant to HID implemantation on device
    """

    # Status of device
    HID_STATUS = 0


class HidData:
    @classmethod
    @abc.abstractmethod
    def decode(cls, data) -> cls:
        """ Convert received raw data into object
        """
        pass

class HidStatus(HidData):
    """ Data received for a command :HidCommand:`HID_STATUS`
    This is dependant to keyboard keymap.
    """

    def __init__(self):
        """ Constructor
        """
        self.layer = None
        self.state = None

    @classmethod
    def decode(cls, data) -> cls:
        """ Convert raw data into HidStatus
        """
        inst = HidStatus()
        inst.layer = data[0]
        inst.state = data[1]
        return inst

    def get_layer_name(self) -> str:
        """ Get the name of the layer associated to retrieved integer
        """
        if self.layer == 0:
            return "alpha"
        elif self.layer == 1:
            return "num/symb"
        elif self.layer == 2:
            return "navigation"
        elif self.layer == 3:
            return "media/rgb/oled"
        elif self.layer == 3:
            return "shortcuts"
        else:
            return "unknown"

    def get_state_name(self) -> str:
        """ Get the name of the locks associated to retrieved integer
        """
        result = []
        if 1 & (self.state >> 0):
            result.append("num lock")
        if 1 & (self.state >> 1):
            result.append("caps lock")
        if 1 & (self.state >> 2):
            result.append("scroll lock")
        if 1 & (self.state >> 3):
            result.append("compose")
        return " / ".join(result)

    def __eq__(self, other):
        """ Equality
        """
        if isinstance(other, HidStatus):
            return other and self.layer == other.layer and self.state == other.state
        return NotImplemented

    def __hash__(self):
        """ Hash
        """
        return hash(tuple(sorted(self.__dict__.items())))


class Observer(abc.ABC):
    """ Abstract class to identify observer of data changed
    """

    @abc.abstractmethod
    def update(self, observable, data) -> None:
        """ Method called by observable to notify a data changed
        """
        pass


class ThreadNotifier(threading.Thread, abc.ABC):
    """ Thread with Observable management
    """

    def __init__(self):
        """ Constructor
        """
        threading.Thread.__init__(self)
        self.stop_event = threading.Event()
        self.observers: [Observer] = []

    def run(self) -> None:
        """ Thread loop
        """
        while not self.stop_event.isSet():
            self.handle()

    def stop(self) -> None:
        """ Stop the thread
        """
        self.stop_event.set()

    def attach(self, observer: Observer) -> None:
        """ Add an observer to the list of observers
        """
        self.observers.append(observer)

    def detach(self, observer: Observer) -> None:
        """ Remove an observer from the list of observers
        """
        self.observers.remove(observer)

    def notify(self, data) -> None:
        """ Notify all the observers that there is a data change
        """
        for observer in self.observers:
            observer.update(self, data)

    @abc.abstractmethod
    def handle(self) -> None:
        """ Method implementing the core of the action
        This method is called in an infinite loop when thread is running
        If the method itself use an infinite loop, handle self.stop_event.isSet() must be checked to stop properly
        """
        pass


class HidHost(ThreadNotifier):
    """ Thread that handles communication between device and host
    """

    # Size of data received over HID interface
    RAW_EPSIZE = 32
    # Default usage page / usage in QMK
    USAGE_PAGE = 0xFF60
    USAGE = 0x61
    # Waiting delay (in seconds) between to try to connect device over HID interface
    WAITING_DELAY_SEARCH = 5.0

    def __init__(self, vendor_id, product_id):
        """ Constructor
        """
        ThreadNotifier.__init__(self)
        self.vendor_id = vendor_id
        self.product_id = product_id
        self.last_data = {}

    def handle(self) -> None:
        """ Try to connect to device and retrieve data (in infinite loop) if connected
        """
        try:
            path = None
            device = hid.device()
            for d in hid.enumerate():
                if d['vendor_id'] == self.vendor_id and d['product_id'] == self.product_id and d['usage_page'] == self.USAGE_PAGE and d['usage'] == self.USAGE:
                    print(f"vid={hex(d['vendor_id'])}, pid={hex(d['product_id'])}, sn={d['serial_number']}, release={hex(d['release_number'])}, manufacturer={d['manufacturer_string']}, product={d['product_string']}, interface={d['interface_number']}, usage_page={hex(d['usage_page'])}, usage={hex(d['usage'])}, path={d['path']}")
                    path = d['path']
                    break
            if path:
                device.open_path(path)
                print(f"Connected to device: vid={self.vendor_id} pid={self.product_id} usage_page={self.USAGE_PAGE} usage={self.USAGE}")
                while not self.stop_event.isSet():
                    # Read data
                    data = device.read(self.RAW_EPSIZE)
                    #print(f"received data: {data}")
                    if data:
                        if data[0] == HidCommand.HID_STATUS.value:
                            self.process_command(HidStatus, data[1:])
                        else:
                            print(f"Unknown command: {data[0]}")
                device.close()
        except IOError as e:
            device.close()
            print(f"Searching for device... ({e})")
            self.stop_event.wait(self.WAITING_DELAY_SEARCH)

    def process_command(self, clsData: HidCommand, data) -> None:
        """ Handle data related to command and notify observers on changed value
        """
        new_data = clsData.decode(data)
        if self.last_data.get(clsData, None) != new_data:
            self.last_data[clsData] = new_data
            self.notify(new_data)


class GuiHidHost(tkinter.Frame, Observer):
    """ Graphical interface that handles communication between device and host
    """
    FRAME_TITLE = "QMK HID"

    master: tkinter.Tk = None
    # HID communication handler
    hid_host: HidHost = None

    def __init__(self, master: tkinter.Tk = None, argv = sys.argv):
        """ Constructor
        Create frame and parse arguments
        """
        # Initialize frame
        super().__init__(master)
        self.master = master
        master.protocol("WM_DELETE_WINDOW", self.stop)

        master.title(self.FRAME_TITLE)
        master.geometry("300x50")
        master.resizable(width=False, height=False)
        #master.wm_attributes('-fullscreen','true')

        self.pack()
        self.create_widgets()

        # Define arguments
        parser = argparse.ArgumentParser(description="HID listener", add_help=True)
        parser.add_argument("-v", "--vendor_id", action="store", dest="vendor_id", type=int, required=True,
                            help="Vendor ID (default : %(default)s)")
        parser.add_argument("-p", "--product_id", action="store", dest="product_id", type=int, required=True,
                            help="Product ID (default : %(default)s)")
        # Parse arguments
        self.arguments = parser.parse_args(argv[1:])

    def create_widgets(self) -> None:
        """ Add widgets to frame
        """
        self.lbl_layer = tkinter.Label(self, text="Initializing")
        self.lbl_layer.pack()
        self.lbl_states = tkinter.Label(self, text="Initializing")
        self.lbl_states.pack()

    def run(self) -> None:
        """ Start HID thread communication handler and frame
        """
        self.hid_host = HidHost(self.arguments.vendor_id, self.arguments.product_id)
        self.hid_host.attach(self)
        self.hid_host.start()

        self.mainloop()

    def stop(self) -> None:
        """ Stop HID thread communication handler and close frame
        """
        print("Stop")
        if self.hid_host:
            self.hid_host.detach(self)
            self.hid_host.stop()
        self.destroy()
        sys.exit(0)

    def signal_handler(self, signal_received, frame):
        self.stop()

    def update(self, observable, data) -> None:
        """ Update interface according to received data from device
        """
        if isinstance(data, HidStatus):
            self.lbl_layer['text'] = data.get_layer_name()
            self.lbl_states['text'] = data.get_state_name()
        else:
            print(f"Unknown data type: {type(data).__name__}")


# Main
if __name__ == "__main__":
    root = tkinter.Tk()
    #gui_hid_host = GuiHidHost(master=root)
    gui_hid_host = GuiHidHost(master=root, argv=["", "--vendor_id", f"{0xFEED}", "--product_id", f"{0x0000}"])
    # Set signal before starting
    signal.signal(signal.SIGINT, gui_hid_host.signal_handler)

    gui_hid_host.run()
