//**************Configuraciones para los encoders AS5600******************//
//  Este código tiene como objetivo realizar las configuraciones necesarias
//  para lograr utilizar los encoders las tareas que deben de ejecutarse son
//      
//
//      * Inicialización de todos los pines para lecturas analogicas
//      * Configuracion del canal ADC de los pines
//      * Escritura y lectura de los encoders usando comunicación i2c
//      * Manejo de activación de cada encoder, esto por que el AS5600 no se puede cambiar su dirección
//***********************************************************************//
//  EL CÓDIGO SE ENCUENTRA SEPARADO EN 2 PARTES, ESTAN SEPARADAS POR ADC Y COMUNICACIÓN I2C


/*======================================================================*/
//     _    ____   ____
//    / \  |  _ \ / ___|
//   / _ \ | | | | |    
//  / ___ \| |_| | |___ 
// /_/   \_\____/ \____|
/*======================================================================*/

//************************Uso********************//
//
//
//
//************************************************//


//************************Mantenimiento de errores*******//
//
//
//
//
//*******************************************************//

#include "Encoders.h"
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include <stdlib.h>


void CalcularValorMapeado(struct Encoder *Pedal);
/*<<<<<<<<<<<<<<<<<<<<Declaración de pedales>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
struct Encoder Freno={
    .ResolucionBits=255,
    .TPedal={'F'},
    .ValorBrutoADC=0,
    .ValorMapeado=0,
    .Error=0,
    .PinADC=0,
    .Giro=0,
    .ValorInicial=0,
    .ValorFinal=0,
    .PinActivacion=27,
    .CanalADC=7,
    .GradosDeGiro=1  
};


struct Encoder Acelerador={
    .ResolucionBits=255,
    .TPedal={'A'},
    .ValorBrutoADC=0,
    .ValorMapeado=0,
    .Error=0,
    .PinADC=0,
    .Giro=0,
    .ValorInicial=0,
    .ValorFinal=0,
    .PinActivacion=26,
    .CanalADC=6,
    .GradosDeGiro=1

};


struct Encoder Clutch={
    .ResolucionBits=255,
    .TPedal={'C'},
    .ValorBrutoADC=0,
    .ValorMapeado=0,
    .Error=0,
    .PinADC=0,
    .Giro=0,
    .ValorInicial=0,
    .ValorFinal=0,
    .PinActivacion=25,
    .CanalADC=5,
    .GradosDeGiro=1
};

struct Encoder Volante={
    .ResolucionBits=8,
    .TPedal={'V'},
    .ValorBrutoADC=0,
    .ValorMapeado=0,
    .Error=0,
    .PinADC=0,
    .Giro=0,
    .ValorInicial=0,
    .ValorFinal=0,
    .PinActivacion=14,
    .CanalADC=4,
    .GradosDeGiro=900 //Valor estandar para los volantes de entrada
};
//<<<<<<<<<<<<<<<<<<<<<<<<<<<------->>>>>>>>>>>>>>>>>>>>>>>>




/*<<<<<<<<<<<<<<<<<<<<Declaración de Pointers ADC y asignación de memoria>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
struct Encoder *ptr_volante;
struct Encoder *ptr_freno;
struct Encoder *ptr_acelerador;
struct Encoder *ptr_clutch;
struct Encoder *matrix_ptr_encoders[4];




void IniciarAsignacionMemoria(){
ptr_volante=malloc(sizeof(struct Encoder));
ptr_volante=&Volante;
ptr_freno=malloc(sizeof(struct Encoder*));
ptr_freno=&Freno;
ptr_acelerador=malloc(sizeof(struct Encoder*));
ptr_acelerador=&Acelerador;
ptr_clutch=malloc(sizeof(struct Encoder*));
ptr_clutch=&Clutch;
matrix_ptr_encoders[0]=ptr_volante;
matrix_ptr_encoders[1]=ptr_freno;
matrix_ptr_encoders[2]=ptr_acelerador;
matrix_ptr_encoders[3]=ptr_clutch;
}




/*<<<<<<<<<<<<<<<<<<<<Declaración de handles ADC>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

//-------------ADC1 Init---------------//
adc_oneshot_unit_init_cfg_t inicializacionConfig= {
    .unit_id = ADC_UNIT_1,
    };

adc_oneshot_unit_handle_t adc_handle_general=NULL;
adc_oneshot_chan_cfg_t configuracion ={
    .bitwidth=ADC_BITWIDTH_11, 
    .atten=ADC_ATTEN_DB_6,
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<------->>>>>>>>>>>>>>>>>>>>>>>>


void InicializacionCanalADC (struct Encoder *Pedal1){
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle_general,Pedal1->CanalADC,&configuracion));
    ESP_ERROR_CHECK(adc_oneshot_channel_to_io(inicializacionConfig.unit_id,Pedal1->CanalADC,&Pedal1->PinADC));
    printf("El canal %d corresponde al pin %d del %s\n",Pedal1->CanalADC,Pedal1->PinADC,Pedal1->TPedal);
    }



void LeerValorBrutoADC (struct Encoder *Pedal){
    ESP_ERROR_CHECK(adc_oneshot_read(adc_handle_general,Pedal->CanalADC,&Pedal->ValorBrutoADC));
}



void imprimirValoresEncoder(struct Encoder *Pedal){
    printf("------------------------\nPedal %s \n",Pedal->TPedal);
    printf("Valores iniciales | Lectura ADC:%d\t Valor Superior:%d\t Valor Inicial:%d\t Valor Mapeado:%d\n",Pedal->ValorBrutoADC,Pedal->ValorFinal,Pedal->ValorInicial,Pedal->ValorMapeado);
    printf("Canal %d y pin correspondiente %d\n------------------------\n",Pedal->CanalADC,Pedal->PinADC);
}

void CalcularValorMapeado(struct Encoder *Pedal){
    Pedal->ValorMapeado=Pedal->ValorBrutoADC+110;
    }


void InicializacionPedalesVolante(){
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&inicializacionConfig, &adc_handle_general));
    for (int i=0; i<=3; i++){               //Ciclo para iniciar la configuracion del ADC a todos los canales (pines) 
        InicializacionCanalADC(matrix_ptr_encoders[i]);
    }
}
/*======================================================================*/
//     _    ___    ____ 
//    / \  |  _ \ / ___|
//   / _ \ | | | | |    
//  / ___ \| |_| | |___ 
// /_/   \_\____/ \____|
/*======================================================================*/



/*======================================================================*/
//   ____ ____ ___ ___      Para leer y calibrar el encoder se tiene que añadir una forma de desactivar los demas encoders, y esto secede por que todos  
//  / ___|  _ \_ _/ _ \     tienen la misma dirección i2c y no hay forma de cambiarlos
// | |  _| |_) | | | | |
// | |_| |  __/| | |_| |    El plan es tener un transistor que desconecte el scl de los demas encoders que no se esten programando
//  \____|_|  |___\___/     Los pines de activación se encuentran en el la estructura Encoder 
/*======================================================================*/
#include "driver/gpio.h"
// Declaracion de configuracion de pines//

gpio_config_t configuracionPines={
    .mode= GPIO_MODE_OUTPUT,
    .pull_up_en=GPIO_PULLUP_DISABLE,
    .pull_down_en=GPIO_PULLDOWN_ENABLE,
    .intr_type=GPIO_INTR_DISABLE
};

//-------------------------------------//

void DireccionPines(struct Encoder *Pedal){ //Declara los pines de activacion correspondientes de cada encoder como salida
    ESP_ERROR_CHECK(gpio_set_direction(Pedal->PinActivacion,configuracionPines.mode));
}

void IniciarPines(){                        //Ciclo for para seleccionar los pines que se usaran como salida
    for (int i =0; i<=3; i++){               
        DireccionPines(matrix_ptr_encoders[i]);
    }
}

void ActivarODesactivarEncoder(struct Encoder *Pedal,uint8_t estado){ //Habilita o desabilita la comunicación con un encoder
  int matrixPines[4];
    for (int i =0; i<=3; i++){               
        matrixPines[i]=matrix_ptr_encoders[i]->PinActivacion;
    }
  
  
  if (estado==1){ //Activar el transistor en todos los demas para evitar que no choque el bus menos en el que se esta calibrando
    for(int i=0;i<=3;i++){
        if(matrixPines[i]==Pedal->PinActivacion){
            gpio_set_level(matrixPines[i],0);
        }
        else{
            gpio_set_level(matrixPines[i],1);
        }
    }
    

  }
    else{//Desactiva el transistor en todos los pines
    
    for (int i =0; i<=3; i++){               
    gpio_set_level(matrixPines[i],1);
    }
    }
}

/*======================================================================*/
//   ____ ____ ___ ___  
/*  / ___|  _ \_ _/ _ \  */
// | |  _| |_) | | | | |
// | |_| |  __/| | |_| |
//  \____|_|  |___\___/ 
/*======================================================================*/



/*======================================================================*/
//  _ ____      
// (_)___ \ ___ 
// | | __) / __|
// | |/ __/ (__ 
// |_|_____\___|
/*======================================================================*/
#include "driver/i2c.h"

//Tomado del ejemplo de ESP-IDF de comunicación i2c
//https://github.com/espressif/esp-idf/blob/master/examples/peripherals/i2c/i2c_simple/main/i2c_simple_main.c

const int I2C_MASTER_SCL_IO=22;                         /*!< GPIO number used for I2C master clock */
const int I2C_MASTER_SDA_IO=21;                         /*!< GPIO number used for I2C master data  */
const int I2C_MASTER_NUM=0;                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
const int I2C_MASTER_FREQ_HZ=400000;                     /*!< I2C master clock frequency */
const int I2C_MASTER_TX_BUF_DISABLE=0;                          /*!< I2C master doesn't need buffer */
const int I2C_MASTER_RX_BUF_DISABLE=0;                          /*!< I2C master doesn't need buffer */
const int I2C_MASTER_TIMEOUT_MS=1000;

esp_err_t i2c_Master_Init(void)
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


void i2c_Master_Inicio(){
    i2c_Master_Init();
}

esp_err_t i2c_lectura(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    //desarrollar una funcion varidica para meterle como parametros todos los registros que quiera leer 
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
/*Registros relacionados a la configuracion y estado del encoder*/
const uint8_t ADDR=0x36;
const uint8_t CONF_REG=0x08;
const uint8_t RAW_ANGLE_L=0x0C;
const uint8_t RAW_ANGLE_M=0x0D;
const uint8_t ZPOS_L=0x01;
const uint8_t ZPOS_M=0x02;
const uint8_t MANG_L=0x05;
const uint8_t MANG_M=0x06;
const uint8_t MPOS_L=0x03;
const uint8_t MPOS_M=0x04;
const uint8_t STATUSE=0x0B;
/*---------------------------------------------------------------*/



void LeerEstadoAS5600 (struct Encoder *Pedal){
//Para leer el valor del estado del encoder aka AS5600 es nesesario usar la comunicación i2c
uint8_t temporat;
i2c_lectura(ADDR,STATUSE,&temporat,1);
printf("%d\n",temporat);

}

 
