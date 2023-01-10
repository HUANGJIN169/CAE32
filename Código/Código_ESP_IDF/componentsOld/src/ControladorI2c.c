#include "driver/i2c.h"
#include "esp_err.h"
#include "freertos/task.h"
#include  "ControladorMotor.h"



/**
 *  Hacer algo con los define correspondientes al la inicialización ya que se encuentran duplicados en 2 archivos c
 *  Agregar punteros para las variables conocidas como dato 1 y 2
 *  Modificar la función de escritura ya que creo que inicia y cierra la comunicación para cado dato, en vez de enviar toda la trama y cerrar la comunicación
 *  crear una función varidica para enviar la trama de datos
 */












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
void ConfiguracionMaxAng(){
    i2c_escritura(ADDR,MANG4b,0x0B);//Los valores escritos para los registros MANG son para limitar el angulo a 0°-260° y aprovechar la máxima resolución
    i2c_escritura(ADDR,MANG8b,0x8E);
    i2c_escritura(ADDR,CONF_REG,0b00010000);
}
void LeerRawAngle(){
    i2c_lectura(ADDR,RAW_ANGLE4b,&dato1,1);     //Lectura por medio de i2c del registro RAWANGLE y almacenados en las variables (dato1 y 2)
    i2c_lectura(ADDR,RAW_ANGLE8b,&dato2,1);
}

void EscribirTramaDeDatosAEncoder(uint8_t reg_addr0,uint8_t reg_addr1,uint8_t dato0,uint8_t dato1){
    i2c_escritura(ADDR,reg_addr0,dato0);
    i2c_escritura(ADDR,reg_addr1,dato1);
}
/**
 * @brief Rutina para la programación del encoder magnético por medio de comunicación i2c
 * 
 */

void RutinaDeConfiguracionManual(){
    //Colocar el indicador en la posición inicial manualmente
    ConfiguracionMaxAng();
    printf("Coloque el indicador en la posicion inicial");
    vTaskDelay(10000 / portTICK_PERIOD_MS);//Esperar 10 segundos para alcanzar a colocarlo manualmente
    LeerRawAngle();
    printf("Leyendo datos del registro RAW_ANGLE \t4b=%i\t8b=%i \n Escribiendo valores de RAW_ANGLE a ZPOS \n",dato1,dato2);
    EscribirTramaDeDatosAEncoder(ZPOS4b,ZPOS8b,dato1,dato2);
    printf("Coloque indicador a posición final en sentido horario");
    vTaskDelay(10000 / portTICK_PERIOD_MS);//Esperar 10 segundos para alcanzar a colocarlo manualmente
    LeerRawAngle();
    printf("Leyendo datos del registro RAW_ANGLE \t4b=%i\t8b=%i \n Escribiendo valores de RAW_ANGLE a MPOS \n",dato1,dato2);
    EscribirTramaDeDatosAEncoder(MPOS4b,MPOS8b,dato1,dato2);

}
void RutinaDeConfiguracionAutomatica(){
    ConfiguracionMaxAng();
    MoverMotorPorTiempo(40,1,100);
    MoverMotorPorTiempo(700,1,25);
    LeerRawAngle();
    EscribirTramaDeDatosAEncoder(ZPOS4b,ZPOS8b,dato1,dato2);
    MoverMotorPorTiempo(40,-1,100);
    MoverMotorPorTiempo(700,-1,25);
    LeerRawAngle();
    EscribirTramaDeDatosAEncoder(MPOS4b,MPOS8b,dato1,dato2);
}
