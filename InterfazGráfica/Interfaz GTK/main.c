#include "device.h"
#include "objectsGtk.h"
#include <err.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdkx.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <poll.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
Device CAE32;
ObjectsUI obj;
const char pathJoy[] = "/dev/input/js"; // Path to search the device if this is a joystick
const char pathHID[] = "/dev/hidraw";   // Path to search the device if this is a HID

int main(int argc, char *argv[]) {
  Device *p_CAE32 = g_malloc(sizeof(Device));
  if (p_CAE32 != NULL) {
    g_printerr("alocado\n");
  }
  GtkBuilder *constructor;
  p_CAE32 = &CAE32;
  constructor = gtk_builder_new();

  gtk_init(&argc, &argv);
  GError *error = NULL;
  if (gtk_builder_add_from_file(constructor, "../gladeFiles/UI1.glade", &error) == 0) {
    g_printerr("Error no se encontro el archivo :%s \n", error->message);
    g_clear_error(&error);
    return 1;
  }
  initObjects(constructor, &obj);
  signalsConnection(&obj);

  if (searchHIDDevice(pathHID, p_CAE32, true) >= 0) {
    g_printerr("Monitoring device\n");
    initpoll(p_CAE32);
  } else {
    // g_free(&CAE32);
  }
  gtk_main();

  return 0;
}
