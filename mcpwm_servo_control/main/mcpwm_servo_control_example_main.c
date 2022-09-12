/* brushed dc motor control example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

/*
 * This example will show you how to use MCPWM module to control brushed dc motor.
 * This code is tested with L298 motor driver.
 * User may need to make changes according to the motor driver they use.
 * #include <stdio.h>



*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "ConfADC.h"
#include "ConfMCPWM.h"
#include "ControladorMotor.h"
#include "ControladorI2c.h"
#include "ConfI2c.h" 
//#include "Consola.h"






void app_main() {
   ConfPinEntrada();
	ESP_ERROR_CHECK(i2c_master_init0());
	mcpwm_gpio_config();
	mcpwm_internal_config();
	IniciarAdc();
   printf("nivel %d \n",gpio_get_level(GPIO_NUM_13));
   if(gpio_get_level(GPIO_NUM_13)==1){
   RutinaDeConfiguracion();
   }
   
  MoverMotorAGrados(90,85);

   
}