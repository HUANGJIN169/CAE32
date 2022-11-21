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

/*
 Información de las diferentes ID (sirve para identificar que dispositivo se conecto)
 https://usb.org/sites/default/files/hut1_3_0.pdf

 Ejemplo: en el bit 0x01 en Generic Desktop Page
 Se puede indentificar un mouse=0x02
			teclado=0x06				
		       joystick=0x04
--En base a la documentación--
System
Multi-Axis
Controller
----------
CA A collection of controls that may contain the same controls as listed in Multi-Axis
Controller (Usage 0x08) and/or additional associated controls such as wheels, dials,
buttons etc... for exclusive use of the System.
---------
Pero quizas sea mejor mantenerlo como Joystick para tener un buena compatibilidad



 HID Report Descriptor
 Se emularan 6 botones para la palanca de cambios
             4 Ejes para volante y pedales




*/
int main(){


}
