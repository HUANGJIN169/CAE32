#include "driver/i2c.h"
#include "esp_err.h"
#include "freertos/task.h"

#define I2C_MASTER_SCL_IO           22      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           21      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000


// Registros para la configuración y calibración del as5600-----------------------------------------------
#define ADDR 0x36
#define CONF_REG 0x08
#define RAW_ANGLE4b 0x0C
#define RAW_ANGLE8b 0x0D
#define ZPOS4b 0x01
#define ZPOS8b 0x02
#define MANG4b 0x05
#define MANG8b 0x06
#define MPOS4b 0x03
#define MPOS8b 0x04
// --------------------------------------------------------------------------------------------------------


// Variables para almacenar los datos de los registros RAWANGLE--------------------------------------------
uint8_t dato1=0;
uint8_t dato2=0;
bool configuracion=false;
// --------------------------------------------------------------------------------------------------------
/**
 * @brief Lee un registro de algún de algun dispositivo por i2c
 * 
 * @param slave_addr Dirección del dispositivo
 * @param reg_addr Registro a leer
 * @param data Apuntador donde se guarda el dato leído
 * @param len Longitud de bits
 * @return esp_err_t 
 */
esp_err_t i2c_lectura(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    //agregar un error en dado caso que no se reciba una respuesta por falta de comunicación (Desconectado y si se apunta a un registro que no existe)
    esp_err_t ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (slave_addr<<1), 1);
    i2c_master_write_byte(cmd, reg_addr, 1);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) {
        return ret;
    }
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (slave_addr<<1)|1, 1);
    i2c_master_read(cmd, data, len,  I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}
/**
 * @brief Escribe un valor a un registro
 * 
 * @param addr Dirección del dispositivo
 * @param reg_addr Registro a escribir
 * @param data Valor a escribir
 */
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
/*
Step 1 Power up the AS5600.

Step 2 Turn the magnet to the start position.

Step 3
Read the RAW ANGLE register.
Write the RAW ANGLE value into the ZPOS register.
Wait at least 1 ms.

Step 4
Rotate the magnet in the direction defined by the level on the DIR pin (GND for clockwise, VDD
for counterclockwise) to the stop position. The amount of rotation must be greater than
18 degrees.

Step 5
Read the RAW ANGLE register.
Write the RAW ANGLE value into the MPOS register.
Wait at least 1 ms.
Proceed with Step 6 to permanently program the configuration.

Step 6 Perform a BURN_ANGLE command to permanently program the device.
Wait at least 1 ms.

Step 7
Verify the BURN_ANGLE command:
Write the commands 0x01, 0x11 and 0x10 sequentially into the register 0xFF to load the actual
OTP content.
Read the ZPOS and MPOS registers to verify that the BURN_ANGLE command was successful.

Step 8 Read and verify the ZPOS and MPOS registers again after a new power-up cycle
*/


/**
 * @brief Rutina para la programación del encoder magnético por medio de comunicación i2c
 * 
 */

void RutinaDeConfiguracion(){
    //Colocar el indicador en la posición inicial manualmente
    i2c_escritura(ADDR,CONF_REG,0b00010000);
    printf("Coloque el indicador en la posicion inicial");
    vTaskDelay(10000 / portTICK_PERIOD_MS);//Esperar 10 segundos para alcanzar a colocarlo manualmente
    i2c_lectura(ADDR,RAW_ANGLE4b,&dato1,1);     //Lectura por medio de i2c del registro RAWANGLE y almacenados en las variables (dato1 y 2)
    i2c_lectura(ADDR,RAW_ANGLE8b,&dato2,1);
    printf("Leyendo datos del registro RAW_ANGLE \t4b=%i\t8b=%i \n",dato1,dato2);
    printf("Escribiendo valores de RAW_ANGLE a ZPOS \n");
    i2c_escritura(ADDR,ZPOS4b,dato1);
    i2c_escritura(ADDR,ZPOS8b,dato2);
    printf("Coloque indicador a posición final en sentido horario");
    vTaskDelay(10000 / portTICK_PERIOD_MS);//Esperar 10 segundos para alcanzar a colocarlo manualmente
    i2c_lectura(ADDR,RAW_ANGLE4b,&dato1,1);     //Lectura por medio de i2c del registro RAWANGLE y almacenados en las variables (dato1 y 2)
    i2c_lectura(ADDR,RAW_ANGLE8b,&dato2,1);
    printf("Leyendo datos del registro RAW_ANGLE \t4b=%i\t8b=%i \n",dato1,dato2);
    printf("Escribiendo valores de RAW_ANGLE a MPOS \n");
    i2c_escritura(ADDR,MPOS4b,dato1);
    i2c_escritura(ADDR,MPOS8b,dato2);
}
/*
int EstadoDeAS5600(){

}*/