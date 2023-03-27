#ifndef SPI_H
#define SPI_H

#include "driver/spi_master.h"
#include <string.h>

spi_device_handle_t init_spi_device();
void send_spi_data(spi_device_handle_t spi, uint8_t sended_data[4],
                   uint8_t received_data[3]);
#endif
