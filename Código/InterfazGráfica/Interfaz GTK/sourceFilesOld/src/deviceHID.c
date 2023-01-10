/* To take advantage of the HID capabilities it is necessary
 * read the device like a HID device and dont like a joystick
 */

#include <linux/hidraw.h>
#include <linux/input.h>
#include <linux/types.h>
/*
 * Ugly hack to work around failing compilation on systems that don't
 * yet populate new version of hidraw.h to userspace.
 */
#ifndef HIDIOCSFEATURE
#warning Please have your distro update the userspace kernel headers
#define HIDIOCSFEATURE(len) _IOC(_IOC_WRITE | _IOC_READ, 'H', 0x06, len)
#define HIDIOCGFEATURE(len) _IOC(_IOC_WRITE | _IOC_READ, 'H', 0x07, len)
#endif

/* Unix */
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* C */
#include "device.h"
#include "deviceHID.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
int search_HID_Device(const char *path, Device *cae) {
  searchDevice(path, cae);
  return 0;
}
*/
