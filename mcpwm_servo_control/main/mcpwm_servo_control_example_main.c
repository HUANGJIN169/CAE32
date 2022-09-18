
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
   int *ptr_grados=NULL;
   ptr_grados=(int*) malloc(sizeof(int));
   int *ptr_VoltajeRaw=NULL;
   ptr_VoltajeRaw=(int*)malloc(sizeof(int));
   ConfPinEntrada();
	ESP_ERROR_CHECK(i2c_master_init0());
	mcpwm_gpio_config();
	mcpwm_internal_config();
	IniciarAdc();
   
   printf("nivel %d \n",gpio_get_level(GPIO_NUM_13));
   if(gpio_get_level(GPIO_NUM_13)==1){
   RutinaDeConfiguracionAutomatica();
   }
   vTaskDelay(1000/ portTICK_PERIOD_MS);

   while (1)
   {
   MoverMotorPorTiempo(10,-1,100);
   MoverMotorPorTiempo(100,-1,25);
   VoltajeAGradosPtr(ptr_grados);
   ValorADCRaw(ptr_VoltajeRaw);
   printf("/*%d,%d*/\n",*ptr_grados,*ptr_VoltajeRaw);
   MoverMotorPorTiempo(10,1,100);
   MoverMotorPorTiempo(100,1,25);
   VoltajeAGradosPtr(ptr_grados);
   ValorADCRaw(ptr_VoltajeRaw);
   printf("/*%d,%d*/\n",*ptr_grados,*ptr_VoltajeRaw);
   vTaskDelay(1000/ portTICK_PERIOD_MS);

   }
   
   


}
