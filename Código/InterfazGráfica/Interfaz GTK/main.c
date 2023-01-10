#include "cae32_app.h"
// #include "device.h"
// #include "objectsGtk.h"
#include <gtk/gtk.h>

/*static void activate(GtkApplication *app, gpointer userdata) {

  Device CAE32;
  Device *p_CAE32 = g_malloc(sizeof(Device));
  p_CAE32 = &CAE32;
  ObjectsUI obj;
  GError *error = NULL;
  GtkBuilder *constructor = gtk_builder_new();
  if (gtk_builder_add_from_file(constructor, "../gladeFiles/UI1.glade", &error) == 0) {
    g_printerr("Error no se encontro el archivo :%s \n", error->message);
    g_clear_error(&error);
    //  return 1;
  }
  GObject *window = gtk_builder_get_object(constructor, "ventana");
  gtk_window_set_application(GTK_WINDOW(window), app);
  initObjects(constructor, &obj);
  signalsConnection(&obj);

  g_signal_connect(obj.reconectar, "clicked", G_CALLBACK(searchDevice), (gpointer)p_CAE32);
  gtk_widget_show(GTK_WIDGET(window));
  g_object_unref(constructor);
}*/

int main(int argc, char *argv[]) {
  GtkApplication *app;
  app = cae32_app_new();

  return g_application_run(G_APPLICATION(app), argc, argv);
}

/*
GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
*/
