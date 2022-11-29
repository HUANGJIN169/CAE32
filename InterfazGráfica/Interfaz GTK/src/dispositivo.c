#include "dispositivo.h"
#include <fcntl.h>
#include <gtk/gtk.h>
#include <linux/joystick.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
const char nameCAE[] = "Steering Wheel CAE32";
Device ctxDevice;
int get_device_name(int fd, char name[60], Device *cae);

int get_device() {
  const char path[] = "/dev/input/js";
  char buffer[sizeof(path) + 2];
  int fd, i;
  for (i = 0; i <= 20; i++) {
    snprintf(buffer, sizeof(buffer), "%s%d", path, i);
    // g_printerr("%s\n",buffer);
    fd = open(buffer, O_RDONLY);
    if (fd > 0) {
      g_printerr("Found a device on %s\n", buffer);
      g_printerr("%d\n", fd);
      break;
      return 1;
    }
  }
  if (fd < 0) {
    g_printerr("Don't found any device \n");
    return -1;
  } else {
    g_printerr("%d\n", fd);
    get_device_name(fd, buffer, &ctxDevice);
  }
  close(fd);
  return 0;
}
int get_device_name(int fd, char name[60], Device *cae) {
  // open device
  // int fd;
  // fd = open(name, O_RDONLY);
  uint8_t ejes, botones;
  ioctl(fd, JSIOCGNAME(sizeof(*name)), name);
  // compare device name
  if (strcmp(name, nameCAE) <= 0) {
    ioctl(fd, JSIOCGAXES, &cae->axis);
    ioctl(fd, JSIOCGAXES, &ejes);
    ioctl(fd, JSIOCGBUTTONS, &cae->buttons);
    ioctl(fd, JSIOCGBUTTONS, &botones);

    g_printerr("Axis %d\n", cae->axis);
    g_printerr("Axis %d\n", ejes);
    g_printerr("buttons %d\n", cae->buttons);
    g_printerr("buttons %d\n", botones);
  }
}
