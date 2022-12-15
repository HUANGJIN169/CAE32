#include "device.h"
#include "objectsGtk.h"
#include "signals.h"
#include <err.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdkx.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

Device DeviceCae; // Struct with information about the device
Device *p_DeviceCae = &DeviceCae;
LevelBar indicators;
LevelBar *p_indicators = &indicators;

const char pathJoy[] = "/dev/input/js"; // Path to search the device if this is a joystick
const char pathHID[] = "/dev/hidraw";   // Path to search the device if this is a HID

ObjectsUI objects;
int main(int argc, char *argv[]) {
  ObjectsUI *p_objects = NULL;
  GtkBuilder *constructor;
  constructor = gtk_builder_new();

  p_objects = &objects;
  p_indicators = g_malloc(sizeof(LevelBar));

  gtk_init(&argc, &argv);
  GError *error = NULL;
  if (gtk_builder_add_from_file(constructor, "../gladeFiles/UI1.glade", &error) == 0) {
    g_printerr("Error no se encontro el archivo :%s \n", error->message);
    g_clear_error(&error);
    return 1;
  }

  initObjects(constructor, p_objects);
  // g_malloc(sizeof(ObjectsUI));
  // p_objects = g_malloc(sizeof(ObjectsUI));
  searchHIDDevice(pathHID, p_DeviceCae, true);
  signalsConnection(p_objects);
  CreateLevelBars(p_indicators);
  g_signal_connect_swapped(p_objects->boton, "clicked", G_CALLBACK(updateLevelBarValue), (gpointer)p_indicators);
  //  g_signal_connect_swapped(G_OBJECT(p_objects->boton), "clicked", G_CALLBACK(levelBarValue), (gpointer)p_objects);
  gtk_main();
  return 0;
}
