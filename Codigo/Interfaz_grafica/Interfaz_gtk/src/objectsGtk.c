/*Register of all Widgets objects*/
#include "objectsGtk.h"
#include "cae32_app.h"
#include "signals.h"
#include "updater.h"
#include <cairo.h>
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

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {

  CAE32App *app = G_POINTER_TO_CAE32_APP(data);
  ObjectsUI *UI = cae32_app_get_gui(app);
  cairo_save(cr);
  cairo_translate(cr, gtk_widget_get_allocated_width(widget) / 2.0, gtk_widget_get_allocated_height(widget) / 2.0);
  // cairo_rotate(cr, rotate);
  cairo_rotate(cr, UI->rotation);
  gdk_cairo_set_source_pixbuf(cr, UI->pixbuf, -gdk_pixbuf_get_width(UI->pixbuf) / 2.0, -gdk_pixbuf_get_height(UI->pixbuf) / 2.0);
  cairo_paint(cr);
  cairo_restore(cr);

  return TRUE;
}
/*
static gboolean on_timeout(gpointer data) {
  // CAE32App *app = G_POINTER_TO_CAE32_APP(data);
  // ObjectsUI *UI = cae32_app_get_gui(app);
  rotate += 0.50;
  gtk_widget_queue_draw(GTK_WIDGET(data));
  return TRUE;
}
*/
ObjectsUI *buildObjects(GtkApplication *app) {
  GtkBuilder *constructor = gtk_builder_new();
  gtk_builder_add_from_file(constructor, "../gladeFiles/UI1.glade", NULL);

  ObjectsUI *obj = g_malloc(sizeof(ObjectsUI));
  g_printerr("UI %p \n", obj);
  obj->boton = GTK_WIDGET(gtk_builder_get_object(constructor, "boton_test"));
  obj->ventana = GTK_WIDGET(gtk_builder_get_object(constructor, "ventana"));
  obj->barra_acelerador = GTK_WIDGET(gtk_builder_get_object(constructor, "valor_acelerador"));
  obj->barra_freno = GTK_WIDGET(gtk_builder_get_object(constructor, "valor_freno"));
  obj->barra_clutch = GTK_WIDGET(gtk_builder_get_object(constructor, "valor_clutch"));
  obj->output = GTK_WIDGET(gtk_builder_get_object(constructor, "salida"));
  obj->reconectar = GTK_WIDGET(gtk_builder_get_object(constructor, "reconnect"));
  obj->visual_status = GTK_WIDGET(gtk_builder_get_object(constructor, "visual_status"));
  obj->text_status = GTK_WIDGET(gtk_builder_get_object(constructor, "text_status"));
  obj->swa = GTK_WIDGET(gtk_builder_get_object(constructor, "swa"));
  obj->search_updates = GTK_WIDGET(gtk_builder_get_object(constructor, "actualizar"));
  obj->tv_updatelog = GTK_WIDGET(gtk_builder_get_object(constructor, "tv_updatelog"));
  return obj;
  g_object_unref(G_OBJECT(constructor));
}
void freeElements(gpointer data) {
  CAE32App *app = G_POINTER_TO_CAE32_APP(data);
  ObjectsUI *UI = cae32_app_get_gui(app);
  Device *cae = CAE32_APP(app)->priv->device;
  g_printerr("%p UI\n", UI);
  g_printerr("%p device\n", cae);
  g_free(cae);
  g_free(UI);
  gtk_main_quit();
}
void signalsConnection(ObjectsUI *obj, CAE32App *app) {
  g_signal_connect_swapped(obj->reconectar, "clicked", G_CALLBACK(searchDevice), app);
  g_signal_connect_swapped(obj->ventana, "destroy", G_CALLBACK(freeElements), app);
  g_signal_connect_swapped(obj->search_updates, "clicked", G_CALLBACK(search_update), app);
  g_signal_connect(G_OBJECT(obj->swa), "draw", G_CALLBACK(on_draw), app);
}
