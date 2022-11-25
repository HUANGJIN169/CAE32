#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <gdk/gdkkeysyms.h>
#include <err.h>
#include "dispositivo.h"
static void
grab_devices(GtkWidget *window)
{
	GdkGrabStatus status;
	GdkDevice *device;
	/* Grab the current event device */
	device = gtk_get_current_event_device();
	if (device == NULL) {
		g_printerr("Couldn't get current device");
		return;
	}
	/* Grab every seat capabilities */
	status = gdk_seat_grab(gdk_device_get_seat(device),
	                       gtk_widget_get_window(window),
	                       GDK_SEAT_CAPABILITY_ALL, TRUE,
	                       NULL, NULL, NULL, NULL);
	if (status != GDK_GRAB_SUCCESS)
		g_printerr("Could not grab %s", gdk_device_get_name(device));
}
int main (int argc, char *argv[]){
GtkBuilder *constructor;
GObject *ventana;
GObject *boton;
GObject *etiqueta;
GObject *barra_acelerador;
GObject *barra_freno;
GObject *barra_clutch;
GObject *lista;
GError *error=NULL;
gtk_init(&argc,&argv);

constructor=gtk_builder_new();
if (gtk_builder_add_from_file(constructor,"UI1.glade",&error)==0){
g_printerr("Error no se encontro el archivo :%s \n",error->message);
g_clear_error(&error);
return 1;
}
boton=gtk_builder_get_object(constructor,"boton_test");
ventana=gtk_builder_get_object(constructor,"ventana");
g_signal_connect (ventana,"destroy",G_CALLBACK(gtk_main_quit),NULL);

//Barras que reacionan con el valor de entrada 

barra_acelerador=gtk_builder_get_object(constructor,"valor_acelerador");
barra_freno=gtk_builder_get_object(constructor,"valor_freno");
barra_clutch=gtk_builder_get_object(constructor,"valor_clutch");

//---------------------------------------------

//Lista donde se muestra el dispositivo
lista=gtk_builder_get_object(constructor,"lista");
//-----------------------------------
get_device();

gtk_main();
return 0;
}

