/*Register of all Widgets objects*/
#include "objectsGtk.h"
#include "signals.h"
#include <gtk/gtk.h>
void initObjects(GtkBuilder *constructor, ObjectsUI *obj) {

  obj->boton = gtk_builder_get_object(constructor, "boton_test");
  obj->ventana = gtk_builder_get_object(constructor, "ventana");
  obj->barra_acelerador = (gtk_builder_get_object(constructor, "valor_acelerador"));
  obj->barra_freno = gtk_builder_get_object(constructor, "valor_freno");
  obj->barra_clutch = gtk_builder_get_object(constructor, "valor_clutch");
  obj->output = gtk_builder_get_object(constructor, "salida");
}

void signalsConnection(ObjectsUI *obj) { g_signal_connect(obj->ventana, "destroy", G_CALLBACK(gtk_main_quit), NULL); }

void CreateLevelBars(LevelBar *bar) {
  bar->ac = gtk_level_bar_new();
  bar->br = gtk_level_bar_new();
  bar->cl = gtk_level_bar_new();
}
