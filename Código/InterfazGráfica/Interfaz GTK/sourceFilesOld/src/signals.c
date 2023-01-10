/* Signals to handle events
 *
 *
 * */
#include "signals.h"
#include <gdk/gdkx.h>
#include <glib.h>
#include <gtk/gtk.h>
void updateLevelBarValue(LevelBar *bar) {
  // test connection
  g_printerr("Callback Function \t%p \n", bar);
  gtk_level_bar_set_value(GTK_LEVEL_BAR(bar->ac), 90);
}
void printgtk(ObjectsUI obj) {
  g_printerr("test\n");
  // levelBarValue(obj);
}
