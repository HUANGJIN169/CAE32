#include "Spi_communication.h"

esp_err_t ret;

/*

spi_device_handle_t spi;

spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0,
};

spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 1*1000*1000,
        .mode = 0,
        .spics_io_num = PIN_NUM_CS,
        .queue_size = 1,
    };

void Initialize_Spi_Bus(spi_bus_config_t buscfg){
	ret=spi_bus_initialize(SPI2_HOST,&buscfg,0);
	if(ret==ESP_OK)
		printf("Inicialización correcta\n");
	else
		printf("ERROR\n");
}

void Add_Device_to_Spi_Bus(spi_device_interface_config_t devcfg,spi_device_handle_t spi){
	ret=spi_bus_add_device(SPI2_HOST,&devcfg,&spi);
	if(ret==ESP_OK)
		printf("Inicialización correcta\n");
	else
		printf("ERROR\n");
}
*/

spi_device_handle_t init_spi_device()
{
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 1000000,          // Velocidad de reloj de 1MHz
        .mode = 0,                          // Modo SPI 0
        .spics_io_num = PIN_NUM_CS,                  // GPIO para SS
        .queue_size = 1,                    // Cola de 1 transacción
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
void Send_Spi_Transaction(uint8_t data,spi_device_handle_t spi){
	spi_transaction_t t;
	memset(&t,0,sizeof(t));
	t.length=sizeof(data)*8;
	t.tx_buffer=&data;
	t.rx_buffer=NULL;
	ret=spi_device_polling_transmit(spi,&t);
	if(ret==ESP_OK)
		printf("Inicialización correcta\n");
	else
		printf("ERROR\n");
}

void send_spi_data(spi_device_handle_t spi, uint16_t data)
{
    esp_err_t ret;

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = sizeof(data) * 8;
    t.tx_buffer = &data;
    t.rx_buffer = NULL;
    ret = spi_device_polling_transmit(spi, &t);
    if (ret == ESP_OK)
    {
        printf("Envío correcto: 0x%x\n", data);
    }
    else
    {
        printf("Error de envío: %d\n", ret);
    }
}
