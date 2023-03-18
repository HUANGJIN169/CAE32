#include "Spi_communication.h"

//  	Spi's pin	//
uint8_t PIN_NUM_MISO = 37;
uint8_t PIN_NUM_MOSI = 35;
uint8_t PIN_NUM_CLK = 36;
uint8_t PIN_NUM_CS = 45;
//----------------------//

//  Pedal's registers	//
uint8_t VERSION = 0x01;
uint8_t CONFIG_ADC_RESOLUTION = 0x02;
uint8_t ACCE = 0x03;
uint8_t BRAKE = 0x04;
uint8_t CLUTCH = 0x05;
uint8_t STATUS = 0x06;
//---------------------//

spi_device_handle_t init_spi_device() {

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 1000000,
        .mode = 0,
        .spics_io_num = PIN_NUM_CS,
        .queue_size = 1,
    };

    spi_device_handle_t spi;

    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0,
    };

    esp_err_t ret;
    ret = spi_bus_initialize(SPI2_HOST, &buscfg, 0);

    ret = spi_bus_add_device(SPI2_HOST, &devcfg, &spi);

    return spi;
}

void send_spi_data(spi_device_handle_t spi, uint8_t sended_data,
                   uint8_t received_data) {
    esp_err_t ret;

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = sizeof(sended_data) * 8;
    t.tx_buffer = &sended_data;
    t.rx_buffer = &received_data;
    ret = spi_device_polling_transmit(spi, &t);
    if (ret == ESP_OK) {
        printf("Envío correcto: 0x%x\n", sended_data);
    } else {
        printf("Error de envío: %d\n", ret);
    }
}
