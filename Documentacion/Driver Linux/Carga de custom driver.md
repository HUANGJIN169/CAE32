https://stackoverflow.com/questions/37427731/use-custom-driver-over-an-existing-driver
https://docs.kernel.org/driver-api/usb/writing_usb_driver.html
https://docs.kernel.org/driver-api/driver-model/binding.html

## USB Host-Side API Model[¶](https://docs.kernel.org/driver-api/usb/usb.html#usb-host-side-api-model "Permalink to this heading")
Host-side drivers for USB devices talk to the “usbcore”

USB device drivers actually bind to interfaces, not devices. Think of them as “interface drivers”, though you may not see many devices where the distinction is important. _Most USB devices are simple, with only one function, one configuration, one interface, and one alternate setting._

-   The Linux USB API supports synchronous calls for control and bulk messages. It also supports asynchronous calls for all kinds of data transfer, using request structures called “URBs” (USB Request Blocks).

In `include/uapi/linux/usb/ch9.h` you will find the USB data types defined in chapter 9 of the USB specification. These data types are used throughout USB, and in APIs including this host side API, gadget APIs, usb character devices and debugfs interfaces. That file is itself included by `include/linux/usb/ch9.h`, which also contains declarations of a few utility routines for manipulating these data types; the implementations are in `drivers/usb/common/common.c`.

### /dev/bus/usb/BBB/DDD[¶](https://docs.kernel.org/driver-api/usb/usb.html#dev-bus-usb-bbb-ddd "Permalink to this heading")

Use these files in one of these basic ways:

-   _They can be read,_ producing first the device descriptor (18 bytes) and then the descriptors for the current configuration. See the USB 2.0 spec for details about those binary data formats. You’ll need to convert most multibyte values from little endian format to your native host byte order, although a few of the fields in the device descriptor (both of the BCD-encoded fields, and the vendor and product IDs) will be byteswapped for you. Note that configuration descriptors include descriptors for interfaces, altsettings, endpoints, and maybe additional class descriptors.
    
-   _Perform USB operations_ using _ioctl()_ requests to make endpoint I/O requests (synchronously or asynchronously) or manage the device. These requests need the `CAP_SYS_RAWIO` capability, as well as filesystem access permissions. Only one ioctl request can be made on one of these device files at a time. This means that if you are synchronously reading an endpoint from one thread, you won’t be able to write to a different endpoint from another thread until the read completes. This works for _half duplex_ protocols, but otherwise you’d use asynchronous i/o requests.

You could check this by changing your final `grep` into `grep --color=always` and piping into `hexdump`, which will show all the unprintable characters and the ones interpreted by your terminal.

In `include/uapi/linux/usb/ch9.h` you will find the USB data types defined in chapter 9 of the USB specification. These data types are used throughout USB, and in APIs including this host side API, gadget APIs, usb character devices and debugfs interfaces. That file is itself included by `include/linux/usb/ch9.h`, which also contains declarations of a few utility routines for manipulating these data types; the implementations are in `drivers/usb/common/common.c`.