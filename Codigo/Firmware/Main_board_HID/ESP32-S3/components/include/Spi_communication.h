#include "driver/spi_master.h"
#include <string.h>
#define PIN_NUM_MISO 37 
#define PIN_NUM_MOSI 35
#define PIN_NUM_CLK  36
#define PIN_NUM_CS   45

//extern spi_device_handle_t spi;

//extern spi_bus_config_t buscfg;

//extern spi_device_interface_config_t devcfg;

//void Initialize_Spi_Bus(spi_bus_config_t buscfg);
//void Add_Device_to_Spi_Bus(spi_device_interface_config_t devcfg,spi_device_handle_t spi);
void Send_Spi_Transaction(uint8_t data,spi_device_handle_t spi);
spi_device_handle_t init_spi_device();
void send_spi_data(spi_device_handle_t spi, uint16_t data);
