/* SPI Slave Halfduplex example

    This example code is in the Public Domain (or CC0 licensed, at your option.)

    Unless required by applicable law or agreed to in writing, this
    software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
    CONDITIONS OF ANY KIND, either express or implied.
*/
#include "esp_log.h"
#include "Spi_communication.h"
#define PIN_NUM_MISO 37 
#define PIN_NUM_MOSI 35
#define PIN_NUM_CLK  36
#define PIN_NUM_CS   45
void app_main()
{
uint16_t data=0x1234;
    //uint8_t data[4]={0x10,0x11,0x12,0x13};
    spi_device_handle_t spi=init_spi_device();
    //Send_Spi_Transaction(data,spi);
	send_spi_data(spi,data);

    // Remove the device from the SPI bus
    //spi_bus_remove_device(spi);

    // Free the SPI bus
    //spi_bus_free(SPI2_HOST);
}
