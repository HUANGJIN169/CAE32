/* In the case of the device is declared like a joystick,
 *  this code is use, but if is registered like Steering wheel then
 *  deviceHID is used
 */
// Use libudev on the future//
#include "device.h"
#include "cae32_app.h"
// #include "cae32_app.h"
//  #include "objectsGtk.h"
#include <fcntl.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <linux/hidraw.h>
#include <linux/joystick.h>
#include <poll.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/poll.h>
#include <unistd.h>
const char nameCAE[] = "Steering Wheel CAE32"; // Name device to compare with the file descriptor
int MAXDEVICES = 10;                           // The maximum number to check for device

// ObjectsUI widgets;
int searchHIDDevice(Device *cae, bool DeviceType) { // Search for a device it can be HID or Joystick device
  memset(cae->path, 0, sizeof(cae->path));
  cae->axis = 0;
  cae->buttons = 0;
  cae->version = 0;
  cae->fd = 0;
  char buffer[256];
  char path[50];
  int fd, i;
  if (DeviceType) {
    g_printerr("Searching for HID Device\n");
    strcpy(path, "/dev/hidraw");
  } else {
    g_printerr("Searching for Joystick Device\n");
    strcpy(path, "/dev/input/js");
  }
  for (i = 0; i <= MAXDEVICES; i++) {
    g_snprintf(buffer, sizeof(buffer), "%s%d", path, i);
    g_printerr("%s\n", buffer);
    fd = open(buffer, O_RDWR);
    if (fd > 0) {
      g_printerr("Found a device on %s\n", buffer);
      g_printerr("Comparing device name...\n");
      strcpy(cae->path, buffer);
      if (typeDevice(fd, buffer, cae, DeviceType) == 1) {
        // strcpy(cae->path, buffer);
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

// Depending the device type it will compare it's name to check if is the steering wheel
// true if it is HID device, false if it is Joystick
int typeDevice(int fd, char name[256], Device *cae, bool isHID) {

  if (isHID == false) {
    ioctl(fd, JSIOCGNAME(60), name);
    if (strcmp(name, nameCAE) == 0) {
      g_printerr("Found joystick %s device \n", nameCAE);
      cae->fd = fd;
      ioctl(fd, JSIOCGAXES, &cae->axis);
      ioctl(fd, JSIOCGBUTTONS, &cae->buttons);
      ioctl(fd, JSIOCGVERSION, &cae->version);
      return 1;
    } else {
      g_printerr("Isn't %s device \n", nameCAE);
      return -1;
    }
  } else {
    ioctl(fd, HIDIOCGRAWNAME(256), name);
    g_printerr("name :%s\n", name);
    if (strcmp(name, nameCAE) == 0) {
      g_printerr("Found HID device\n");
      cae->fd = fd;
      return 1;
    } else {
      g_printerr("Isn't %s device \n", nameCAE);
      return -1;
    }
  }
}

void showDevInfo(Device *cae) { // print all the device data

  g_printerr("\n-----------------\n");
  g_printerr("File Descriptor %d \n", cae->fd);
  g_printerr("Device Version %d \n", cae->version);
  g_printerr("Axis %u \n", cae->axis);
  g_printerr("Buttons %u \n", cae->buttons);
  g_printerr("Path %s \n", cae->path);
  g_printerr("-------------------\n");
}

int searchDevice(gpointer data) {
  CAE32App *app = G_POINTER_TO_CAE32_APP(data);
  ObjectsUI *UI = cae32_app_get_gui(app);
  Device *cae = &CAE32_APP(app)->priv->device;

  if (searchHIDDevice(cae, false) >= 0) {
    g_printerr("Monitoring Joystick device\n");
    cae->found = true;
    cae->isHID = false;
    // mostrar estado actual de conexion
    gtk_label_set_text(GTK_LABEL(UI->text_status), "Conectado (Joystick)"); // Agregar una función para que muestre el estado
    gtk_image_set_from_file(GTK_IMAGE(UI->visual_status), "../src_images/green.png");
    // CAE32_APP(app)->priv->input = g_thread_try_new("input_barras", initCaptureData, app, NULL);
    // initCaptureData(app);
    g_thread_try_new("input_barras", initCaptureData, app, NULL);
    return 1;
  }
  if (searchHIDDevice(cae, true) >= 0) {
    g_printerr("Monitoring HID device\n");
    gtk_label_set_text(GTK_LABEL(UI->text_status), "Conectado (HID)");
    gtk_image_set_from_file(GTK_IMAGE(UI->visual_status), "../src_images/green.png");
    cae->isHID = true;
    cae->found = true;

    return 0;
  }
  gtk_label_set_text(GTK_LABEL(UI->text_status), "Desconectado");
  gtk_image_set_from_file(GTK_IMAGE(UI->visual_status), "../src_images/red.png");

  cae->found = false;
  g_printerr("I can't find the Device\n");
  return -1;
}

// apply poll to use signals and events
// 1. Open file descriptor
// 2. Read file descriptor
//
// void initpoll(Device *cae, struct pollfd *pfd) {
// Checking if was diconnected
// void *updateDevice(Device *cae) {}
void *initCaptureData(gpointer data) {
  CAE32App *app = G_POINTER_TO_CAE32_APP(data);
  ObjectsUI *UI = cae32_app_get_gui(app);
  Device *cae = &CAE32_APP(app)->priv->device;
  // GCond cond=CAE32_APP(app)->priv->input_fd;
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(UI->barra_acelerador), 0.1);
  g_printerr("openning path: %s\n", cae->path);
  int fd;
  struct js_event js;
  fd = open(cae->path, O_RDWR | O_NONBLOCK);
  ssize_t len;
  while (1) {
    usleep(100); // sleep(1);
    len = read(fd, &js, sizeof(js));
    if (len == sizeof(js)) {
      if (js.type & JS_EVENT_AXIS) {

        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(UI->barra_acelerador), js.value / 32000.0);
        g_printerr("Axis: %d, Value: %d\n", js.number, js.value);

        // axis_state[js.number] = js.value;
        // axis_move(js.number, js.value);
      } else if (js.type & JS_EVENT_BUTTON) {

        g_printerr("Button: %d, Value: %d\n", js.number, js.value);

        // button_move(js.number, js.value);
      }
    }
  }
}
