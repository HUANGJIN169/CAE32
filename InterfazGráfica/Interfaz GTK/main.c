#include <gtk/gtk.h>
static void aumentarvalor(GtkWidget *widget,gpointer data);

int main (int argc, char *argv[]){
GtkBuilder *constructor;
GObject *ventana;
GObject *boton;
GObject *etiqueta;
GObject *barra_progreso;
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

barra_progreso=gtk_builder_get_object(constructor,"valor_acelerador");
g_signal_connect_object (boton,"clicked",G_CALLBACK(aumentarvalor),barra_progreso,G_CONNECT_AFTER);
gtk_main();
return 0;
}


static void aumentarvalor(GtkWidget *widget,gpointer data){
g_print("funciona \n");
gtk_progress_bar_set_fraction(data,0.5);
}


