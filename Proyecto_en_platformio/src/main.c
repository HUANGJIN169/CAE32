#include "esp_log.h"
#include <stdio.h>
#include "driver/gpio.h"
//#include "config_i2c.h"
//#include "config_adc.h"
#include "config_motor.h"
#include "driver/timer.h"


// Registros para la configuración y calibración del as5600-----------------------------------------------
#define ADDR 0x36
#define CONF_REG 0x08
#define RAW_ANGLE4b 0x0C
#define RAW_ANGLE8b 0x0D
#define ZPOS4b 0x01
#define ZPOS8b 0x02
#define MANG4b 0x05
#define MANG8b 0x06
// --------------------------------------------------------------------------------------------------------


// Variables para almacenar los datos de los registros RAWANGLE--------------------------------------------
uint8_t dato1=0;
uint8_t dato2=0;
bool configuracion=false;
// --------------------------------------------------------------------------------------------------------



void app_main(void)
{
setup();
mcpwm_start(0,0);

//mcpwm_set_duty(0,1,1,80);
mcpwm_set_signal_high(0,0,0);
}

