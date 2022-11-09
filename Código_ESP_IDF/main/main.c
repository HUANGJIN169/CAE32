#include "freertos/FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "freertos/task.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/queue.h"
#include "Encoders.h"
void app_main() {

IniciarAsignacionMemoria();
InicializacionPedalesVolante();
LeerValorBrutoADC(ptr_acelerador);
CalcularValorMapeado(ptr_acelerador);
imprimirValoresEncoder(ptr_acelerador);

i2c_Master_Inicio();
LeerEstadoAS5600(ptr_acelerador);
IniciarPines();
ActivarODesactivarEncoder(ptr_acelerador,1);
}




