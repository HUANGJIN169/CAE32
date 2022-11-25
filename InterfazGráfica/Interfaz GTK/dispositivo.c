#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <dispositivo.h>
#include <fcntl.h>
void get_device (){

//loop to find a fd on /dev/input/js*
int fd;
fd=open("/dev/input/js0",O_RDONLY);
close(fd);
/*
for (int i=0;i<30;i++){
	
	ret=open(
}
*/
}
