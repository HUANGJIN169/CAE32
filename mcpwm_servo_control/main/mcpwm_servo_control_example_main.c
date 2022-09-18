
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



void vLeerValorAnalogico(void *pvParameters);
const int *ptr_VoltajeRaw=NULL;
void app_main() {
   //int *ptr_grados=NULL;
   //ptr_grados=(int*) malloc(sizeof(int));

   //ptr_VoltajeRaw=(int*)malloc(sizeof(int));

   ConfPinEntrada();
	ESP_ERROR_CHECK(i2c_master_init0());
	mcpwm_gpio_config();
	mcpwm_internal_config();
	IniciarAdc();
   
   printf("nivel %d \n",gpio_get_level(GPIO_NUM_13));
   if(gpio_get_level(GPIO_NUM_13)==1){
   RutinaDeConfiguracionAutomatica();
   }
   xTaskCreate(vLeerValorAnalogico,"Lectura analógica",1000,(void*)ptr_VoltajeRaw,1,NULL);

}
void vLeerValorAnalogico(void *pvParameters)
{
   int *pcs;
   pcs=(int *) pvParameters;
   for(;;){
      VoltajeAGradosPtr(pcs);
   }
}