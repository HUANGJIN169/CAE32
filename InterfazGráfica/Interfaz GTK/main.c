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
ObjectsUI obj;
int main(int argc, char *argv[]) {
  Device CAE32;
  Device *p_CAE32 = g_malloc0(sizeof(Device));
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
  GtkImage *visual_status = GTK_IMAGE(gtk_builder_get_object(constructor, "visual_status"));   // 1
  GtkLabel *text_status = GTK_LABEL(gtk_builder_get_object(constructor, "connection_status")); // 2
  initObjects(constructor, &obj);
  signalsConnection(&obj);

  g_printerr("Device address %p\n", p_CAE32);
  g_signal_connect_swapped(obj.reconectar, "clicked", G_CALLBACK(searchDevice), (gpointer)p_CAE32);
  searchDevice(p_CAE32);

  // gtk_image_set_from_file(visual_status, "../src_images/gray.png");
  // gtk_label_set_text(text_status, "Desconectado");
  gtk_main();

  return 0;
}
