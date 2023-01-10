/* In the case of the device is declared like a joystick,
 *  this code is use, but if is registered like Steering wheel then
 *  deviceHID is used
 */
// Use libudev on the future//
#include "device.h"
#include <fcntl.h>
#include <gtk/gtk.h>
#include <linux/hidraw.h>
#include <linux/joystick.h>
#include <stdbool.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>

const char nameCAE[] = "Steering Wheel CAE32"; // Name device to compare with the file descriptor
int MAXDEVICES = 10;                           // The maximum number to check for device

int searchHIDDevice(const char *path, Device *cae, bool DeviceType) {
  char buffer[256];
  // char buffer[sizeof(&path) + 2];
  int fd, i;

  if (DeviceType)
    g_printerr("Searching for HID Device\n");
  else
    g_printerr("Searching for Joystick Device\n");

  for (i = 0; i <= MAXDEVICES; i++) {
    snprintf(buffer, sizeof(buffer), "%s%d", path, i);
    //  g_printerr("%s\n", buffer);
    fd = open(buffer, O_RDWR | O_NONBLOCK);
    if (fd > 0) {
      g_printerr("\nFound a device on %s\n", buffer);
      g_printerr("Comparing device name...\n");
      if (typeDevice(fd, buffer, cae, DeviceType) == 1) {
        break;
        return 1;
      }
    }
  }

  if (fd < 0) {
    g_printerr("Don't found any device \n");
    return -1;
  }

  close(fd);
  return 0;
}

//@brief Depending the device type it will compare it's name to check if is the steering whell
//@isHID true if it is HID device, false if it is Joystick
int typeDevice(int fd, char name[256], Device *cae, bool isHID) {
  if (isHID == false) {
    ioctl(fd, JSIOCGNAME(60), name);
    if (strcmp(name, nameCAE) == 0) {
      g_printerr("Found joystick %s device \n", nameCAE);
      cae->fd = fd;
      ioctl(fd, JSIOCGAXES, &cae->axis);
      ioctl(fd, JSIOCGBUTTONS, &cae->buttons);
      ioctl(fd, JSIOCGVERSION, &cae->version);
      cae->found = true;
      return 1;
    } else {
      g_printerr("Isn't %s device \n", nameCAE);
      cae->found = false;
      return -1;
    }
  } else {
    ioctl(fd, HIDIOCGRAWNAME(256), name);
    g_printerr("name :%s\n", name);
    if (strcmp(name, nameCAE) == 0) {
      g_printerr("Found HID device\n");
      cae->found = true;
      return 1;
    } else {
      g_printerr("Isn't %s device \n", nameCAE);
      cae->found = false;
      return -1;
    }
  }
}

void showDevInfo(Device *cae) {

  g_printerr("\n-----------------\n");
  g_printerr("File Descriptor %d \n", cae->fd);
  g_printerr("Device Version %d \n", cae->version);
  g_printerr("Axis %d \n", cae->axis);
  g_printerr("Buttons %d \n", cae->buttons);
  g_printerr("Shifter Value %d \n", cae->shifter);
  g_printerr("Acelerator Value %d \n", cae->acelerator);
  g_printerr("Brake Value %d \n", cae->brake);
  g_printerr("Steering Value %d \n", cae->steering);
  g_printerr("-------------------\n");
}
