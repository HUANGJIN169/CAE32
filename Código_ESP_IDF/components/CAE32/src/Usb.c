#include "driver/uart.h"
#include "string.h"
#include "stdlib.h"
const uart_port_t usb_uart = UART_NUM_2;
const int uart_buffer_size=(1024*2);
QueueHandle_t uart_queue;
uart_config_t uart_config={
    .baud_rate=115200,
    .data_bits=UART_DATA_8_BITS,
    .parity=UART_PARITY_DISABLE,
    .stop_bits=UART_STOP_BITS_1,
    .flow_ctrl=UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_DEFAULT
 
};

void IniciarUSbUART(){
    ESP_ERROR_CHECK(uart_param_config(usb_uart,&uart_config));
    ESP_ERROR_CHECK(uart_set_pin(usb_uart,26,27,-1,-1));
    ESP_ERROR_CHECK(uart_driver_install(usb_uart,uart_buffer_size,uart_buffer_size,10,&uart_queue,0));

}
void transmitir(){
   char* test_str = "This is a test string.\n";
   uart_write_bytes(usb_uart, (const char*)test_str, strlen(test_str));
}
void transmitirint(const int cals){
    char buf[15];
    sprintf(buf,"%d",cals);
     uart_write_bytes(usb_uart,(const char*)buf+'0',1);
}
