/* In the case of the device is declared like a joystick,
 *  this code is use, but if is registered like Steering wheel then
 *  deviceHID is used
 */
#include "device.h"
#include "cae32_app.h"
#include "glibconfig.h"
#include <fcntl.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <linux/hidraw.h>
#include <linux/joystick.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char nameCAE[] = "CAE32 Steering Wheel"; // Name device to compare with the file descriptor
int MAXDEVICES = 10;                           // The maximum number to check for device
struct udev_source *source;

// gboolean CaptureEvent(gpointer data);
void updateAxisBar(ObjectsUI *UI, guint8 number, guint16 value);
// ObjectsUI widgets;
int searchHIDDevice(Device *cae, bool DeviceType) { // Search for a device it can be HID or Joystick device
  memset(cae->path, 0, sizeof(cae->path));
  /*
  cae->axis = 0;
  cae->buttons = 0;
  cae->version = 0;
  cae->fd = 0;
  */

  char buffer[256];
  char path[50];
  int fd, i;

  if (DeviceType) {
    g_printerr("Searching for HID Device\n");
    strcpy(path, "/dev/hidraw"); // search on hid path
  } else {
    g_printerr("Searching for Joystick Device\n");
    strcpy(path, "/dev/input/js"); // search on joystick path
  }
  for (i = 0; i <= MAXDEVICES; i++) {
    g_snprintf(buffer, sizeof(buffer), "%s%d", path, i); // gived format to open the specified device
    g_printerr("%s\n", buffer);                          // print of specified device
    fd = open(buffer, O_RDWR);                           // open to check if exist a device
    if (fd > 0) {
      g_printerr("Found a device on %s\n", buffer);
      g_printerr("Comparing device name...\n");
      strcpy(cae->path, buffer); // save the path to read later
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

static gboolean CaptureEvent(gpointer data) {
  // get all the components (device,UI elements)
  CAE32App *app = G_POINTER_TO_CAE32_APP(data);
  ObjectsUI *UI = cae32_app_get_gui(app);
  Device *cae = CAE32_APP(app)->priv->device;
  //-------------------------------------------
  struct js_event js; // create a struct to save all the events

  open(cae->path, O_RDWR | O_NONBLOCK);         // open the path to read on nonblocking mode
  ssize_t len = read(cae->fd, &js, sizeof(js)); // read the data from the device

  if (len < 0) {
    // detach device from the threadand update the visual state
    g_printerr("Error\n");
    g_source_destroy((GSource *)source);
    gtk_label_set_text(GTK_LABEL(UI->text_status), "Desconectado");
    gtk_image_set_from_file(GTK_IMAGE(UI->visual_status), "../src_images/red.png");
    return TRUE;
  }

  if (len == sizeof(js)) {
    if (js.type & JS_EVENT_AXIS) {
      updateAxisBar(UI, js.number, js.value);
      g_printerr("Axis: %d, Value: %d\n", js.number, js.value);
    } else if (js.type & JS_EVENT_BUTTON) {

      g_printerr("Button: %d, Value: %d\n", js.number, js.value);
    }
  }
  return TRUE;
}

// Depending the device type it will compare it's name to check if is the steering wheel
// true if it is HID device, false if it is Joystick
int typeDevice(int fd, char name[256], Device *cae, bool isHID) {

  if (isHID == false) {
    ioctl(fd, JSIOCGNAME(60), name);  // get the joystick name
    if (strcmp(name, nameCAE) == 0) { // compare name
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
    ioctl(fd, HIDIOCGRAWNAME(256), name); // get the HID name
    g_printerr("name :%s\n", name);
    if (strcmp(name, nameCAE) == 0) { // compare name
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

void showStatusConnection(Device *cae, ObjectsUI *UI) {
  if (cae->found) {
    if (cae->isHID) {

      gtk_label_set_text(GTK_LABEL(UI->text_status), "Conectado (HID)");
      gtk_image_set_from_file(GTK_IMAGE(UI->visual_status), "../src_images/green.png");
    } else {
      gtk_label_set_text(GTK_LABEL(UI->text_status), "Conectado (Joystick)");
      gtk_image_set_from_file(GTK_IMAGE(UI->visual_status), "../src_images/green.png");
    }
  } else {

    gtk_label_set_text(GTK_LABEL(UI->text_status), "Desconectado");
    gtk_image_set_from_file(GTK_IMAGE(UI->visual_status), "../src_images/red.png");
  }
}
//
struct udev_source {
  GSource base;
  gpointer tag;
};

static gboolean udev_source_prepare(G_GNUC_UNUSED GSource *source, gint *timeout) {
  *timeout = -1;
  return FALSE;
}

static gboolean udev_source_check(GSource *source) {
  struct udev_source *usrc = (struct udev_source *)source;
  return (g_source_query_unix_fd(source, usrc->tag) > 0);
}

static gboolean udev_source_dispatch(GSource *source, GSourceFunc callback, gpointer user_data) {
  struct udev_source *usrc = (struct udev_source *)source;
  GIOCondition revents = g_source_query_unix_fd(source, usrc->tag);

  if (revents & G_IO_IN | G_IO_HUP) {
    if (callback == NULL)
      return FALSE;
    return callback(user_data);
  }

  return TRUE;
}

GSourceFuncs udev_source_funcs = {
    .prepare = udev_source_prepare,
    .check = udev_source_check,
    .dispatch = udev_source_dispatch,
};
//

void configGSource(Device *cae, CAE32App *app) {

  source = (struct udev_source *)g_source_new(&udev_source_funcs, sizeof(*source));
  // struct udev_source *source;
  // source = (struct udev_source *)g_source_new(&udev_source_funcs, sizeof(*source));
  g_source_set_callback(&source->base, CaptureEvent, app, NULL); /* destroy_notify */
  source->tag = g_source_add_unix_fd(&source->base, cae->fd, G_IO_IN | G_IO_HUP);
  g_source_attach(&source->base, g_main_context_default());
  g_source_unref(&source->base);
}

int searchDevice(gpointer data) {
  CAE32App *app = G_POINTER_TO_CAE32_APP(data);
  ObjectsUI *UI = cae32_app_get_gui(app);
  Device *cae = CAE32_APP(app)->priv->device;
  if (searchHIDDevice(cae, false) >= 0) { // Searching for a Joystick device
    g_printerr("Monitoring Joystick device\n");
    cae->found = true;
    cae->isHID = false;
    showStatusConnection(cae, UI);
    configGSource(cae, app);
    return 1;
  }
  if (searchHIDDevice(cae, true) >= 0) { // Searching for a HID device
    g_printerr("Monitoring HID device\n");
    cae->isHID = true;
    cae->found = true;
    showStatusConnection(cae, UI);
    return 0;
  }

  cae->found = false;
  showStatusConnection(cae, UI);
  g_printerr("I can't find the Device\n");
  return -1;
}

void updateSteeringWheel(ObjectsUI *UI, guint16 value) {

  // UI->rotation += 0.50;
  UI->rotation = (value / 32000.0) * 8;
  gtk_widget_queue_draw(UI->swa);
}
void updateAxisBar(ObjectsUI *UI, guint8 number, guint16 value) {
  switch (number) {
  case 0: {
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(UI->barra_freno), value / 32000.0);
    break;
  }
  case 3: {
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(UI->barra_clutch), value / 32000.0);
    break;
  }
  case 2: {
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(UI->barra_acelerador), value / 32000.0);
    break;
  }
  case 1: {
    updateSteeringWheel(UI, value);

    break;
  }
  }
}
