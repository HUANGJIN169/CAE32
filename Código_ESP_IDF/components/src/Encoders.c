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


void test_en (struct Encoder *lalito);
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
    .PinActivacion=PIN_ENABLE_FRENO,
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
    .PinActivacion=PIN_ENABLE_ACELERADOR,
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
    .PinActivacion=PIN_ENABLE_CLUTCH,
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
    .PinActivacion=PIN_ENABLE_VOLANTE,
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
    for (int i=0; i<=3; i++){               //Ciclo iniciar la configuracion del ADC a todos los canales (pines) 
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
//  _ ____      
// (_)___ \ ___ 
// | | __) / __|
// | |/ __/ (__ 
// |_|_____\___|
/*======================================================================*/



void LeerEstadoAS5600 (struct Encoder *Pedal){
//Para leer el valor del estado del encoder aka AS5600 es nesesario usar la comunicación i2c

}

