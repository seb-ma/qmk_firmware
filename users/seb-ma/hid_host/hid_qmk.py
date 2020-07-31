#!/usr/bin/python3
# -*- coding: utf-8 -*-
"""
HID communication between keyboard Kyria:seb-ma (vendorID = 0xFEED, productID = 0x0000) and host.
This application is a basic window that displays the layer currently active and the different locks active on keyboard.
It is highly dependant of HID keyboard implementation.

NB: default productID of keyboard was changed due to a check on 0 in library pyhidapi.


This application has following dependencies:
- Linux dependencies:
    - libhidapi-hidraw0 or libhidapi-libusb0 or hidapi (according to distribution)
- Python dependencies:
    - [pyhidapi](https://pypi.org/project/hid/) (available on PyPI: pip install hid)
    - [tkinter](https://docs.python.org/library/tk.html)

udev rules must be defined to allow usb communication:
    - add udev rules: see https://beta.docs.qmk.fm/faqs/faq_build
    - then reload: udevadm control --reload-rules

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

    def getLayerName(self) -> str:
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
        else:
            return "unknown"

    def getStateName(self) -> str:
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
        self.stopEvent = threading.Event()
        self.observers: [Observer] = []

    def run(self) -> None:
        """ Thread loop
        """
        while not self.stopEvent.isSet():
            self.handle()

    def stop(self) -> None:
        """ Stop the thread
        """
        self.stopEvent.set()

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
        If the method itself use an infinite loop, handle self.stopEvent.isSet() must be checked to stop properly
        """
        pass


class HidHost(ThreadNotifier):
    """ Thread that handles communication between device and host
    """

    # Size of data received over HID interface
    RAW_EPSIZE = 32
    USAGE_PAGE = 0xFF60
    USAGE = 0x61
    # Waiting delay (in seconds) between to try to connect device over HID interface
    WAITING_DELAY_SEARCH = 5.0

    def __init__(self, vendorID, productID):
        """ Constructor
        """
        ThreadNotifier.__init__(self)
        self.vendorID = vendorID
        self.productID = productID
        self.lastData = {}

    def handle(self) -> None:
        """ Try to connect to device and retrieve data (in infinite loop) if connected
        """
        try:
            path = None
            for d in hid.enumerate():
                if d['vendor_id'] == self.vendorID and d['product_id'] == self.productID and d['usage_page'] == self.USAGE_PAGE and d['usage'] == self.USAGE:
                    print(f"vid: {hex(d['vendor_id'])}, pid: {hex(d['product_id'])}, interface: {d['interface_number']}, usage_page: {hex(d['usage_page'])}, usage: {hex(d['usage'])}, path: {d['path']}")
                    path = d['path']
                    break
            if path:
                with hid.Device(path=path) as dev:
                    print(f"Connected to device: {dev.manufacturer} {dev.product} (serial: {dev.serial}) - vid: {self.vendorID} pid: {self.productID}")

                    while not self.stopEvent.isSet():
                        # Read data
                        data = dev.read(self.RAW_EPSIZE)
                        #print(f"received data: {data}")
                        if data:
                            if data[0] == HidCommand.HID_STATUS.value:
                                self.processCommand(HidStatus, data[1:])
                            else:
                                print(f"Unknown command: {data[0]}")
        except hid.HIDException as e:
            print(f"Searching for device... ({e})")
            self.stopEvent.wait(self.WAITING_DELAY_SEARCH)

    def processCommand(self, clsData: HidCommand, data) -> None:
        """ Handle data related to command and notify observers on changed value
        """
        newData = clsData.decode(data)
        if self.lastData.get(clsData, None) != newData:
            self.lastData[clsData] = newData
            self.notify(newData)


class GuiHidHost(tkinter.Frame, Observer):
    """ Graphical interface that handles communication between device and host
    """

    master: tkinter.Tk = None
    # HID communication handler
    hidHost: HidHost = None

    def __init__(self, master: tkinter.Tk = None, argv = sys.argv):
        """ Constructor
        Create frame and parse arguments
        """
        # Initialize frame
        super().__init__(master)
        self.master = master
        master.protocol("WM_DELETE_WINDOW", self.stop)

        self.pack()
        self.createWidgets()

        # Define arguments
        parser = argparse.ArgumentParser(description="HID listener", add_help=True)
        parser.add_argument("-v", "--vendorID", action="store", dest="vendorID", type=int, default=0xFEED,
                            help="Vendor ID (default : %(default)s)")
        parser.add_argument("-p", "--productID", action="store", dest="productID", type=int, default=0x0000,
                            help="Product ID (default : %(default)s)")
        # Parse arguments
        self.arguments = parser.parse_args(argv[1:])

    def createWidgets(self) -> None:
        """ Add widgets to frame
        """
        self.lbl_layer = tkinter.Label(self, text="Initializing")
        self.lbl_layer.pack()
        self.lbl_states = tkinter.Label(self, text="Initializing")
        self.lbl_states.pack()

    def run(self) -> None:
        """ Start HID thread communication handler and frame
        """
        self.hidHost = HidHost(self.arguments.vendorID, self.arguments.productID)
        self.hidHost.attach(self)
        self.hidHost.start()

        self.mainloop()

    def stop(self) -> None:
        """ Stop HID thread communication handler and close frame
        """
        print("Stop")
        if self.hidHost:
            self.hidHost.detach(self)
            self.hidHost.stop()
        self.destroy()
        sys.exit(0)

    def signalHandler(self, signal_received, frame):
        self.stop()

    def update(self, observable, data) -> None:
        """ Update interface according to received data from device
        """
        if isinstance(data, HidStatus):
            self.lbl_layer['text'] = data.getLayerName()
            self.lbl_states['text'] = data.getStateName()
        else:
            print(f"Unknown data type: {type(data).__name__}")


# Main
if __name__ == "__main__":
    root = tkinter.Tk()
    hidHost = GuiHidHost(master = root)
    # Set signal before starting
    signal.signal(signal.SIGINT, hidHost.signalHandler)

    hidHost.run()
