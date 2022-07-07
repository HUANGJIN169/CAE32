#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
void tarea_periodica(void *pvParameters){
    const TickType_t delay=100/portTICK_PERIOD_MS;
    TickType_t tiempo_de_respuesta;    
    tiempo_de_respuesta=xTaskGetTickCount();
    for (;;)
    {
        printf("tarea periodica");
        vTaskDelayUntil(&tiempo_de_respuesta,delay);
}
}
void tarea_continua (void *pvParameters)
{
    char *nombre_de_tarea;
    nombre_de_tarea =(char *) pvParameters;
    for (;;)
    {
        printf(nombre_de_tarea);
    }
}
static const char *texto_para_tarea1="tarea 1 corriendo\n";
static const char *texto_para_tarea2="tarea 2 corriendo\n";
void app_main() {
    xTaskCreate(tarea_continua,"tarea1",2048, (void *) texto_para_tarea1,1,NULL);
    xTaskCreate(tarea_continua,"tarea2",2048, (void *) texto_para_tarea2,1,NULL);
    xTaskCreate(tarea_periodica,"tarea_periodica",2048,NULL,2,NULL);
    }