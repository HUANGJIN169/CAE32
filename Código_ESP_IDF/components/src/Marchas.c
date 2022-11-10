//*****************************Configuración de marcha********************//
// Este código tiene como proposito capturar el cambio en el que se encuentra la trasmisión
// además esta pensado para una transmision en H, aunque facilmente puede configurarse para cambio secuencial
// Por ejemplo: Primera, Segunda, Neutral, etc.
// >>*****Por el momento se conectara cada pin de un boton con una entrada del ESP-32 pero en el futuro se usara un multiplexor o algo similar
// Las tareas que se deben de ejecutar son:
//      *Seleccion de pines como entradas
//      *Lectura de Velocidad actual(Ejemplo: primera)


#include "Marchas.h"
#include "driver/gpio.h"

const unsigned char Primera=19;     /*Pines que corresponden con una marcha*/
const unsigned char Segunda=18;
const unsigned char Tercera=5;
const unsigned char Cuarta=17;
const unsigned char Quinta=16;
const unsigned char Sexta=4;

unsigned char PinVelocidad[6]={Primera,Segunda,Tercera,Cuarta,Quinta,Sexta};    //Matrix para iterar el numero de pin y añadirlo como entrada y leer su nivel
unsigned char *Velocidad;   
void IniciarPinesMarchas(unsigned char Velocidades[6]){                         //Se declaran los pines como salida
    for (int i = 0; i <=6 ; i++)
    {
    gpio_set_direction(Velocidades[i],GPIO_MODE_INPUT);
    }
    
}
//La lectura se podría realizar con interrupciones
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void LecturaMarcha(unsigned char Velocidades[6],unsigned char *VelocidadActual){//Se lee el nivel de cada pin si alguno se encuentra en alto lo guarda en la variable marcha
    unsigned char Marcha=0;
    for (unsigned int i = 0; i <=6 ; i++)
    {
        if (gpio_get_level(Velocidades[i])==1){//si no se encuentra nungun pin en alto no modifica el valor y lo deja en su estado inicial =0 que equivale a neutral
            Marcha=Velocidades[i]+1;
    }   
    }
    *VelocidadActual=Marcha;
    
}

void ImprimirVelocidadActual(unsigned char *VelocidadActual){
    printf("La velocidad actual es %d \n",*VelocidadActual);
}