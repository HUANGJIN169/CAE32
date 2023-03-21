#include "Spi_communication.h"
#include "esp_log.h"
#include "freertos/task.h"
void app_main() {
    uint8_t response[4];
    uint8_t lol[4] = {0x10, 0x12, 0x13, 0x32};
    spi_device_handle_t spi = init_spi_device();
    while (1) {
        vTaskDelay(100 / portTICK_PERIOD_MS);
        send_spi_data(spi, lol, response);

        // printf("%d,%d,%d\r\n", response[0], response[1], response[2]);
        // spi_bus_free(SPI2_HOST);
    }
}
