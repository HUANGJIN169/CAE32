
#include "freertos/FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "freertos/task.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "ConfADC.h"
#include "ConfMCPWM.h"
#include "ControladorMotor.h"
#include "ControladorI2c.h"
#include "ConfI2c.h" 
#include "freertos/queue.h"
#include "Usb.h"




//int *ptr_VoltajeRaw=NULL;
void app_main() {
   IniciarUSbUART();
   //transmitir("la cica");
   transmitir();
   transmitirint(70);


}





