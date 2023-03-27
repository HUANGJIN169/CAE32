#include "Spi_communication.h"
#include "Usb_communication.h"
#include "esp_log.h"
#include "freertos/task.h"
#include <stdio.h>
void app_main() {
    uint8_t response[3];
    uint8_t tests_data[4] = {0x10, 0x12, 0x13, 0x32};
    spi_device_handle_t spi = init_spi_device();
    usb_initialization();
}
