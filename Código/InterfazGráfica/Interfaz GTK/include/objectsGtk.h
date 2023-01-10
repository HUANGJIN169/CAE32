// #include "device.h"
#include "cae32_app.h"
#include <gtk/gtk.h>
/*typedef struct ObjectsUI {
  GtkWidget *ventana;
  GtkWidget *visual_status;
  GtkWidget *text_status;
  GtkWidget *boton;
  GtkWidget *etiqueta;
  GtkWidget *barra_acelerador;
  GtkWidget *barra_freno;
  GtkWidget *barra_clutch;
  GtkWidget *output;
  GtkWidget *reconectar;
  GtkWidget *connection_status;
} ObjectsUI;

typedef struct _CAE32AppPrivate CAE32AppPrivate;
typedef struct _CAE32App CAE32App;
typedef struct _CAE32AppClass CAE32AppClass;
// ObjectsUI widgets;
struct _CAE32AppPrivate {
  ObjectsUI *UI;
};

struct _CAE32App {
  GtkApplication parent;
  CAE32AppPrivate *priv;
};

struct _CAE32AppClass {
  GtkApplicationClass parent_class;
};

typedef struct {
  ObjectsUI *obj;
} datas;
*/
void start_gui(void);
ObjectsUI *buildObjects(GtkApplication *app);
void signalsConnection(ObjectsUI *obj, CAE32App *app);
//  #pragma once
