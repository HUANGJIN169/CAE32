#include "freertos/FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "freertos/task.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/queue.h"
#include "Encoders.h"
#include "Marchas.h"
void app_main() {

IniciarAsignacionMemoria();
InicializacionPedalesVolante();
CalcularValorMapeado(ptr_acelerador);

i2c_Master_Inicio();
IniciarPines();
ActivarODesactivarEncoder(ptr_acelerador,1);
IniciarPinConfiguracion();
CalibracionEncoder(ptr_acelerador);


while (1)
{
    LeerValorBrutoADC(ptr_acelerador);
    vTaskDelay(1000 / portTICK_PERIOD_MS);//Contraresta el debounce propio del boton
    CalcularValorMapeado(ptr_acelerador);
    vTaskDelay(1000 / portTICK_PERIOD_MS);//Contraresta el debounce propio del boton
    printf("Valor mapeado: %d\n",ptr_acelerador->ValorMapeado);
}

}




