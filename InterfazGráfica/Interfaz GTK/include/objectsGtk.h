#include <gdk/gdkx.h>
#include <gtk/gtk.h>
typedef struct ObjectsUI {
  GObject *ventana;
  GObject *visual_status;
  GObject *text_status;
  GObject *boton;
  GObject *etiqueta;
  GObject *barra_acelerador;
  GObject *barra_freno;
  GObject *barra_clutch;
  GObject *output;
  GObject *reconectar;
} ObjectsUI;

typedef struct LevelBar {
  GtkWidget *ac;
  GtkWidget *br;
  GtkWidget *cl;
} LevelBar;

void CreateLevelBars(LevelBar *bar);
void initObjects(GtkBuilder *constructor, ObjectsUI *obj);
void signalsConnection(ObjectsUI *obj);
#pragma once
