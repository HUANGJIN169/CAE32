#include "freertos/FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "freertos/task.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/queue.h"
#include "Encoders.h"
#include "Marchas.h"
#include "ComunicacionUSB.h"
#include "Tareas.h"
#define TAG "main"

void iniciacion(){
//IniciarAsignacionMemoriaEncoder();
//InicializacionPedalesVolante();
//i2c_Master_Inicio();
//IniciarPinesActivacionEncoder();
IniciarPinesMarchas(Marchas);
//IniciarPinConfiguracion();
}


void app_main() {
iniciacion();
//CalibracionEncoder(ptr_acelerador);
while (1)
{
    /*limpiartrama(datos);
    LecturaMarcha(&Velocidad);
    LeerValorBrutoADC(ptr_acelerador);
    vTaskDelay(1000 / portTICK_PERIOD_MS);//Contraresta el debounce propio del boton
    CalcularValorMapeado(ptr_acelerador);
    vTaskDelay(1000 / portTICK_PERIOD_MS);//Contraresta el debounce propio del boton
    //ESP_LOGI(TAG,"Valor mapeado: %d\n",ptr_acelerador->ValorMapeado);
    UnionDeTrama(datos,&Velocidad);
    EnvioDatosUSB(datos);
    
    ImprimirVelocidadActual(&Velocidad);
 */
    LecturaMarcha(&Velocidad);
    vTaskDelay(1000 / portTICK_PERIOD_MS);//Contraresta el debounce propio del boton
    ImprimirVelocidadActual(&Velocidad);
    vTaskDelay(1000 / portTICK_PERIOD_MS);//Contraresta el debounce propio del boton


}
}




