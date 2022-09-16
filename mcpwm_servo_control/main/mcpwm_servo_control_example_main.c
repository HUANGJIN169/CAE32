
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
   RutinaDeConfiguracionManual();
   }
   
  MoverMotorAGrados(90,85);

   
}
