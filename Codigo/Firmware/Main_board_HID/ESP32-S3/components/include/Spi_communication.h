#include "driver/spi_master.h"
#include <string.h>
//  	Spi's pin	//
extern uint8_t PIN_NUM_MISO;
extern uint8_t PIN_NUM_MOSI;
extern uint8_t PIN_NUM_CLK;
extern uint8_t PIN_NUM_CS;
//----------------------//

//  Pedal's registers	//
extern uint8_t VERSION;
extern uint8_t CONFIG_ADC_RESOLUTION;
extern uint8_t ACCE;
extern uint8_t BRAKE;
extern uint8_t CLUTCH;
extern uint8_t STATUS;
//---------------------//

spi_device_handle_t init_spi_device();
void send_spi_data(spi_device_handle_t spi, uint8_t sended_data,
                   uint8_t received_data);
