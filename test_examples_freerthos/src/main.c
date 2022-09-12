#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
//#include "freertos/FreeRTOSConfig.h"
volatile uint32_t contador=0;

void vtarea_periodica(void *pvParameters){
    const TickType_t xdelay=100/portTICK_PERIOD_MS;
    TickType_t xtiempo_de_respuesta;    
    xtiempo_de_respuesta=xTaskGetTickCount();
    for (;;)
    {
        printf("tarea periodica\n");
        vTaskDelayUntil(&xtiempo_de_respuesta,xdelay);
}
}
void vtarea_continua (void *pvParameters)
{
    char *pcnombre_de_tarea;
    pcnombre_de_tarea =(char *) pvParameters;
    for (;;)
    {
        printf("%s %i",pcnombre_de_tarea,contador);
        vTaskDelay(250);
    }
}
/*
void contar(void){
    contador++;
}
*/
static const char *texto_para_tarea1="tarea 1 corriendo\n";
static const char *texto_para_tarea2="tarea 2 corriendo\n";
void app_main() {
    //esp_register_freertos_idle_hook_for_cpu(&contar,1);
    xTaskCreate(vtarea_continua,"tarea1",2048, (void *) texto_para_tarea1,1,NULL);
    xTaskCreate(vtarea_continua,"tarea2",2048, (void *) texto_para_tarea2,1,NULL);
    xTaskCreate(vtarea_periodica,"vtarea_periodica",2048,NULL,2,NULL);
    }