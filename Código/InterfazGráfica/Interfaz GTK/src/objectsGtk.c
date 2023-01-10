/*Register of all Widgets objects*/
#include "objectsGtk.h"
#include "cae32_app.h"
// #include "device.h"
#include "signals.h"
#include <gtk/gtk.h>
void start_gui(void) {
  GError *error = NULL;
  GtkBuilder *constructor = gtk_builder_new();
  gtk_init(NULL, NULL); // posible problema

  if (gtk_builder_add_from_file(constructor, "../gladeFiles/UI1.glade", &error) == 0) {
    g_printerr("Error no se encontro el archivo :%s \n", error->message);
    g_clear_error(&error);
  }

  g_set_prgname("CAE32");
  g_object_unref(G_OBJECT(constructor));
  gtk_main();
}

ObjectsUI *buildObjects(GtkApplication *app) {
  GtkBuilder *constructor = gtk_builder_new();
  gtk_builder_add_from_file(constructor, "../gladeFiles/UI1.glade", NULL);

  ObjectsUI *obj = g_malloc(sizeof(ObjectsUI));
  obj->boton = GTK_WIDGET(gtk_builder_get_object(constructor, "boton_test"));
  obj->ventana = GTK_WIDGET(gtk_builder_get_object(constructor, "ventana"));
  obj->barra_acelerador = GTK_WIDGET(gtk_builder_get_object(constructor, "valor_acelerador"));
  obj->barra_freno = GTK_WIDGET(gtk_builder_get_object(constructor, "valor_freno"));
  obj->barra_clutch = GTK_WIDGET(gtk_builder_get_object(constructor, "valor_clutch"));
  obj->output = GTK_WIDGET(gtk_builder_get_object(constructor, "salida"));
  obj->reconectar = GTK_WIDGET(gtk_builder_get_object(constructor, "reconnect"));
  obj->visual_status = GTK_WIDGET(gtk_builder_get_object(constructor, "visual_status"));
  obj->text_status = GTK_WIDGET(gtk_builder_get_object(constructor, "text_status"));
  return obj;
  g_object_unref(G_OBJECT(constructor));
}
void statusconnection(Device *cae32, ObjectsUI *obj) {
  if (cae32->found == true)
    gtk_label_set_text(GTK_LABEL(obj->text_status), "Monitoring");
  else
    gtk_label_set_text(GTK_LABEL(obj->text_status), "Desconectado");
}

void signalsConnection(ObjectsUI *obj, CAE32App *app) {
  g_signal_connect_swapped(obj->reconectar, "clicked", G_CALLBACK(searchDevice), app);
  g_signal_connect(obj->ventana, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  // g_signal_connect(obj->reconectar, "clicked", G_CALLBACK(statusconnection), obj);
}
