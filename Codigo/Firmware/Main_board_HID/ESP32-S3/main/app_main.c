#include "Spi_communication.h"
#include "esp_log.h"
void app_main() {
    uint8_t response = 0;
    spi_device_handle_t spi = init_spi_device();
    send_spi_data(spi, STATUS, response);
    if (response == 0) {
        printf("Didnt receive anyting\n");
    } else {
        printf("I receive: %d \n", response);
    }
    // spi_bus_free(SPI2_HOST);
}
