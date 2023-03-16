// search for a device with the name of "Cae32"

#ifndef __DEVICE_H__
#define __DEVICE_H__
#include <gtk/gtk.h>
#include <poll.h>
#include <stdbool.h>
#include <stdint.h>
typedef struct Device {
  int fd;
  char path[50];
  bool isHID;
  bool found;
  guint32 version;
  guint8 axis;
  guint8 buttons;
} Device;

int typeDevice(int fd, char name[60], Device *cae, bool isHID);
int searchHIDDevice(Device *cae, bool DeviceType);
void showDevInfo(Device *cae);
int searchDevice(gpointer data);
// gboolean CaptureEvents(gpointer data);
#endif
// #pragma once
