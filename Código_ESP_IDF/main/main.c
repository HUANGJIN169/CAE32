#include "freertos/FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "freertos/task.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/queue.h"
#include "Encoders.h"
//struct Encoder *ptr_volante;
void app_main() {

IniciarAsignacionMemoria();
//ptr_volante=(struct Encoder *)malloc(sizeof(struct Encoder));
InicializacionPedalesVolante();
LeerValorBrutoADC(ptr_acelerador);
CalcularValorMapeado(ptr_acelerador);
imprimirValoresEncoder(ptr_acelerador);
}





