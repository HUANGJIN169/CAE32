#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
typedef struct {
	gint wheel; 
	gint accel;
	gint brake;
	gint clutch;
	gint shifter;
	GdkDevice* device;
} DeviceData;

void get_device(){
const char path[]="/dev/input/js";
char buffer[sizeof(path)+2];
int fd;
//char tempPath[sizeof(path+3)];
for(int i=0; i<=20; i++){

snprintf(buffer,sizeof(buffer),"/dev/input/js%d",i);
//strcpy(tempPath,path);
//strcat(tempPath,buffer);
g_printerr("%s\n",buffer);
}
/*fd=open(path,O_RDONLY);

if(fd=>0){
break;
}

}
close(fd);*/
}
