#include "driver/i2c.h"
static const char *TAG = "i2c-simple-example";

#define I2C_MASTER_SCL_IO           22      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           21      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

esp_err_t i2c_lectura(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    esp_err_t ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (slave_addr<<1), 1);
    i2c_master_write_byte(cmd, reg_addr, 1);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) {
        return ret;
    }
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (slave_addr<<1)|1, 1);
    i2c_master_read(cmd, data, len,  I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}
void i2c_escritura(uint8_t addr,uint8_t reg_addr,uint8_t data){
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd,(addr<<1),0x0);
    i2c_master_write(cmd,&reg_addr,1,0x0);
    i2c_master_write(cmd,&data,1,0x0);
    i2c_master_stop(cmd); 
    i2c_master_cmd_begin(I2C_MASTER_NUM,cmd,I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}
/*    ESP_ERROR_CHECK(i2c_master_init());
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
     } */