
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
//#include "Consola.h"
//#define CONFIG_FREERTOS_HZ 100

//pdMS_TO_TICKS(100)
void imprimir(void *pv){
   char *ptr;
   ptr=(char *) pv;
   for(;;){
   printf("tarea: %s\n",ptr);
   vTaskDelay(250 / portTICK_PERIOD_MS);
}
}
void vLeerValorAnalogico(void *pvParameters);
void vImprimirValor(void *pvParameters);
QueueHandle_t xQueue;
static void vEnvioTarea(void *pv){
   int LValoraEnviar;
   BaseType_t xstatus;
   LValoraEnviar=(int)pv;
   for (;;){
      xstatus=xQueueSendToBack(xQueue,&LValoraEnviar,0);
      if (xstatus!=pdPASS)
      {
         printf("no se pudo hacer la queue\r\n");
      }
   }
}
static void vRecibirTarea(void *pv){
   int LValoraRecibir;
   BaseType_t xstatus;
   const TickType_t xTickaesperar = pdMS_TO_TICKS(100);
   for(;;){
      if(uxQueueMessagesWaiting(xQueue)!=0){
         printf("Queue deberia estar vacia!\r\n");
      }
      xstatus=xQueueReceive(xQueue,&LValoraRecibir,xTickaesperar);
      
      if(xstatus==pdPASS){
         printf("/*%d*/\n",LValoraRecibir);
                
      }
      else{
         printf("no se recibio valor\n");
      }
   }
}



int *ptr_VoltajeRaw=NULL;
void app_main() {
xQueue=xQueueCreate(5,sizeof(int));

if (xQueue!=NULL){
   xTaskCreate(vEnvioTarea,"envio1",2048,(void *) 215,1,NULL);
   xTaskCreate(vEnvioTarea,"envio2",2048,(void *) 104,1,NULL);
   xTaskCreate(vRecibirTarea,"recepcion",2048,NULL,2,NULL);
}
else{

}
for(;;);
/*
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
   xTaskCreate(vLeerValorAnalogico,"Lectura analógica",2048,(void*)ptr_VoltajeRaw,3,NULL);
   xTaskCreate(vImprimirValor,"dato",2048,(void*)ptr_VoltajeRaw,1,NULL);

   //xTaskCreate(imprimir,"enviar valor",2048,(void *)"lalo",2,NULL);
   //xTaskCreate(imprimir,"enviar valor",2048,(void *)"54alo",2,NULL);

*/


}






void vLeerValorAnalogico(void *pvParameters)
{
   int *pcs;
   pcs=(int *) pvParameters;
   for(;;){
      VoltajeAGradosPtrv(pcs);
      vTaskDelay(250 / portTICK_PERIOD_MS);
   }
}
void vImprimirValor(void *pvParameters){
   int *texto;
   texto=(int *) pvParameters;
   for(;;){
      printf("/*%d*/\n",*texto);
      vTaskDelay(250 / portTICK_PERIOD_MS);
   }
}