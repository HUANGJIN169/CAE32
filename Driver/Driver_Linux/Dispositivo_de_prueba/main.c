#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <linux/uhid.h>
#include <linux/joystick.h>
#include <string.h>
int xd;
char buffer[10];
/***
Este código tiene como objetivo probar la configuración del descriptor HID y 
la correcta conexión con la interfaz grafica de configuración


*/

/*
 Información de las diferentes ID (sirve para identificar que dispositivo se conecto)
 https://usb.org/sites/default/files/hut1_3_0.pdf

 Ejemplo: en el bit 0x01 en Generic Desktop Page
 Se puede indentificar un mouse=0x02
			teclado=0x06				
		       joystick=0x04
--En base a la documentación--
Hay un apartado especial para simulador de deportes, ahí se encuentra uno especial para autos
este cuenta con los campos ya preparados como: 
Volante(wheel)
Freno
Clutch 
Palanca de cambio(shifter)
Pero quizas sea mejor mantenerlo como Joystick para tener una buena compatibilidad



 HID Report Descriptor
 Se emularan 7 botones para la palanca de cambios
             4 Ejes para volante y pedales
*/

//Configuración del descriptor HID

static unsigned char HidDesc[] = {
/*0x05, 0x01, 	//Usage_Page (Generic Desktop)
0x09, 0x04,	//Usage (Joystick)
0xA1, 0x01,	//Collection (Application)
0X85, 0x01,	//Report_Id (1)
0x05, 0x09, 	//Usage_Page (Buttons)
0x19, 0x01,	//Usage_minimum (0)
0x29, 0x08,	//Usage_maximum (8)
0x15, 0x00, 	//Logical_minimum (0)
0x25, 0x01, 	//Logical_maximum (1)
0x95, 0x09, 	//Report_Count (9)
0x75, 0x01,	//Report_Size (1)
0x81, 0x02,	//Input (abs)
0xC0*/
         0x05, 0x01,     /* USAGE_PAGE (Generic Desktop) */
         0x09, 0x04,     /* USAGE (Joystick) */
 //      0xa1, 0x01,     /* COLLECTION (Application) */
 //      0x09, 0x01,             /* USAGE (Pointer) */
         0xa1, 0x01,             /* COLLECTION (Physical) */
         0x85, 0x01,                     /* REPORT_ID (1) */
         0x05, 0x09,                     /* USAGE_PAGE (Button) */
         0x19, 0x01,                     /* USAGE_MINIMUM (Button 1) */
         0x29, 0x08,                     /* USAGE_MAXIMUM (Button 3) */
         0x15, 0x00,                     /* LOGICAL_MINIMUM (0) */
         0x25, 0x01,                     /* LOGICAL_MAXIMUM (1) */
         0x95, 0x08,                     /* REPORT_COUNT (3) */
         0x75, 0x01,                     /* REPORT_SIZE (1) */
         0x81, 0x02,                     /* INPUT (Data,Var,Abs) */
 //      0x95, 0x01,                     /* REPORT_COUNT (1) */
 //      0x75, 0x05,                     /* REPORT_SIZE (5) */
 //      0x81, 0x01,                     /* INPUT (Cnst,Var,Abs) */
 //      0x85, 0x02,                     /* REPORT_ID (1) */
         0x05, 0x01,                     /* USAGE_PAGE (Generic Desktop) */
         0x09, 0x30,                     /* USAGE (X) */
         0x09, 0x31,                     /* USAGE (Y) */
         0x09, 0x32,                     /* USAGE (WHEEL) */
         0x09, 0x33,
         0x15, 0x81,                     /* LOGICAL_MINIMUM (-127) */
         0x25, 0x7f,                     /* LOGICAL_MAXIMUM (127) */
         0x35, 0xc9,
         0x45, 0xc8,
         0x75, 0x08,                     /* REPORT_SIZE (8) */
         0x95, 0x04,                     /* REPORT_COUNT (3) */
         0x82, 0x02,0x01,                        /* INPUT (Data,Var,Rel) */
         0xc0

};

static int uhid_write(int fd,const struct uhid_event *ev){

ssize_t ret;

ret=write(fd ,ev,sizeof(*ev));
if (ret<0){
	fprintf(stderr, "Cannot write to uhid: %m\n");
	return -errno;
} else if (ret!=sizeof(*ev)){
	fprintf(stderr, "Wrong size written to uhid_ %zd != %zu\n",
		ret,sizeof(*ev));
	return -EFAULT;
} else {
	return 0;
}
}

static int create (int fd){
	
	struct uhid_event ev;
	memset(&ev,0,sizeof(ev));
	ev.type=UHID_CREATE2;
	ev.u.create2.rd_data[sizeof(HidDesc)];
	strcpy((char *) ev.u.create2.name, "Steering Wheel CAE32");
	strcpy(ev.u.create2.rd_data, HidDesc);
	ev.u.create2.rd_size=sizeof(HidDesc);
	ev.u.create2.vendor=0x15d9;
	ev.u.create2.product=0x0a37;
	ev.u.create2.version=0;
	ev.u.create2.country=0;
	return uhid_write(fd, &ev);
}

static void destroy(int fd)

{
	struct uhid_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.type=UHID_DESTROY;
	uhid_write(fd,&ev);
}
 static int event(int fd)
 {
         struct uhid_event ev;
         ssize_t ret;
 
         memset(&ev, 0, sizeof(ev));
         ret = read(fd, &ev, sizeof(ev));
         if (ret == 0) {
                 fprintf(stderr, "Read HUP on uhid-cdev\n");
                 return -EFAULT;
         } else if (ret < 0) {
                 fprintf(stderr, "Cannot read uhid-cdev: %m\n");
                 return -errno;
         } else if (ret != sizeof(ev)) {
                 fprintf(stderr, "Invalid size read from uhid-dev: %zd != %zu\n",
                         ret, sizeof(ev));
                 return -EFAULT;
         }
 
         switch (ev.type) {
         case UHID_START:
                 fprintf(stderr, "UHID_START from uhid-dev\n");
                 break;
         case UHID_STOP:
                 fprintf(stderr, "UHID_STOP from uhid-dev\n");
                 break;
         case UHID_OPEN:
                 fprintf(stderr, "UHID_OPEN from uhid-dev\n");
                 break;
         case UHID_CLOSE:
                 fprintf(stderr, "UHID_CLOSE from uhid-dev\n");
                 break;
         case UHID_OUTPUT:
                 fprintf(stderr, "UHID_OUTPUT from uhid-dev\n");
                 //handle_output(&ev);
                 break;
         case UHID_OUTPUT_EV:
                 fprintf(stderr, "UHID_OUTPUT_EV from uhid-dev\n");
                 break;
         default:
                 fprintf(stderr, "Invalid event from uhid-dev: %u\n", ev.type);
         }
 
         return 0;
 }


int main(int argc, char **argv){
	int fd;
	const char *path="/dev/uhid";
	struct pollfd pfds[2];
	int ret;
	struct termios state;
	
         ret = tcgetattr(STDIN_FILENO, &state);
        if (ret) {
                fprintf(stderr, "Cannot get tty state\n");
        } else {
                state.c_lflag &= ~ICANON;
                state.c_cc[VMIN] = 1;
                ret = tcsetattr(STDIN_FILENO, TCSANOW, &state);
                if (ret)
                        fprintf(stderr, "Cannot set tty state\n");
        }

        if (argc >= 2) {
                if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
                        fprintf(stderr, "Usage: %s [%s]\n", argv[0], path);
                        return EXIT_SUCCESS;
                } else {
                        path = argv[1];
                }
        }

        fprintf(stderr, "Open uhid-cdev %s\n", path);
        fd = open(path, O_RDWR | O_CLOEXEC);
        if (fd < 0) {
                fprintf(stderr, "Cannot open uhid-cdev %s: %m\n", path);
                return EXIT_FAILURE;
        }

        fprintf(stderr, "Create uhid device\n");
        ret = create(fd);
        if (ret) {
                close(fd);
                return EXIT_FAILURE;
        }

        pfds[0].fd = STDIN_FILENO;
        pfds[0].events = POLLIN;
        pfds[1].fd = fd;
        pfds[1].events = POLLIN;

	printf(HidDesc);
        fprintf(stderr, "Press 'q' to quit...\n");
/*        while (1) {
                ret = poll(pfds, 2, -1);
                if (ret < 0) {
                        fprintf(stderr, "Cannot poll for fds: %m\n");
                        break;
                }
                if (pfds[0].revents & POLLHUP) {
                        fprintf(stderr, "Received HUP on stdin\n");
                        break;
                }
                if (pfds[1].revents & POLLHUP) {
                        fprintf(stderr, "Received HUP on uhid-cdev\n");
                        break;
                }

                if (pfds[0].revents & POLLIN) {
                        ret = keyboard(fd);
                        if (ret)
                                break;
                }
                if (pfds[1].revents & POLLIN) {
                        ret = event(fd);
                        if (ret)
                                break;
                }
  */      
	fgets(buffer,sizeof(buffer),stdin);

        fprintf(stderr, "Destroy uhid device\n");
        destroy(fd);
        return EXIT_SUCCESS; 	

}
