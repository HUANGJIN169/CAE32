#include "esp_log.h"
#include <stdio.h>
#include "driver/gpio.h"
#include "config_i2c.h"
#include "config_adc.h"


// Registros para la configuración y calibración del as5600-----------------------------------------------
#define ADDR 0x36
#define CONF_REG 0x08
#define RAW_ANGLE4b 0x0C
#define RAW_ANGLE8b 0x0D
#define ZPOS4b 0x01
#define ZPOS8b 0x02
#define MANG4b 0x05
#define MANG8b 0x06
// --------------------------------------------------------------------------------------------------------


// Variables para almacenar los datos de los registros RAWANGLE--------------------------------------------
uint8_t dato1=0;
uint8_t dato2=0;
bool configuracion=false;
// --------------------------------------------------------------------------------------------------------



void app_main(void)
{
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");
    iniciar_adc();
    while (!configuracion)
    {
    vTaskDelay(1000/portTICK_RATE_MS);
       for (int i=4;i>0;i--){                       //Ciclo for para mostrar los datos del registro RAWANGLE, cada segundo
        i2c_lectura(ADDR,RAW_ANGLE4b,&dato1,1);     //Lectura por medio de i2c del registro RAWANGLE y almacenados en las variables (dato1 y 2)
        i2c_lectura(ADDR,RAW_ANGLE8b,&dato2,1);
        printf("Leyendo datos del registro RAW_ANGLE \t4b=%i\t8b=%i \n",dato1,dato2);
        vTaskDelay(1000/portTICK_RATE_MS);
    }
    printf("Escribiendo valores de RAW_ANGLE a ZPOS\nConfigurando valor maximo de giro a 360 en el registro MANG\n");
    i2c_escritura(ADDR,ZPOS4b,dato1);
    i2c_escritura(ADDR,ZPOS8b,dato2);
    i2c_escritura(ADDR,MANG4b,0x0F);
    i2c_escritura(ADDR,MANG8b,0xFF);
    i2c_escritura(ADDR,CONF_REG,0b00010000);
    i2c_lectura(54,ZPOS4b,&dato1,1);
    i2c_lectura(54,ZPOS8b,&dato2,1);
    printf("Comprobando registros ZPOS \t\t4b= %i \t8b=%i\n",dato1,dato2);    
    configuracion=true;
    }
     while (1){
        printf("Voltaje calculado=%.2fv\t Valor del ADC=%i\n",calcular_voltaje(),adc1_get_raw(ADC1_CHANNEL_4));
        vTaskDelay(1000/portTICK_RATE_MS);
     }
}