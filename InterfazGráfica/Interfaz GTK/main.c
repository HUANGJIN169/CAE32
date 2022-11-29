#include "dispositivo.h"
#include <err.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdkx.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
  GtkBuilder *constructor;
  GObject *ventana;
  GObject *boton;
  GObject *etiqueta;
  GObject *barra_acelerador;
  GObject *barra_freno;
  GObject *barra_clutch;
  GObject *lista;
  GError *error = NULL;
  gtk_init(&argc, &argv);

  constructor = gtk_builder_new();
  if (gtk_builder_add_from_file(constructor, "../gladeFiles/UI1.glade",
                                &error) == 0) {
    g_printerr("Error no se encontro el archivo :%s \n", error->message);
    g_clear_error(&error);
    return 1;
  }
  boton = gtk_builder_get_object(constructor, "boton_test");
  ventana = gtk_builder_get_object(constructor, "ventana");
  g_signal_connect(ventana, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // Barras que reacionan con el valor de entrada

  barra_acelerador = gtk_builder_get_object(constructor, "valor_acelerador");
  barra_freno = gtk_builder_get_object(constructor, "valor_freno");
  barra_clutch = gtk_builder_get_object(constructor, "valor_clutch");

  //---------------------------------------------

  // Lista donde se muestra el dispositivo
  lista = gtk_builder_get_object(constructor, "lista");
  //-----------------------------------
  get_device();

  gtk_main();
  return 0;
}
