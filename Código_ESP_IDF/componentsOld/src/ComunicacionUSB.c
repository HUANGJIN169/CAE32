//*************************************Unión y manipulación de trama USB**************//
// Este código une los datos de cada Pedal,Volante,Caja de cambios y Errores
// Esta trama sera la que se envia por UART->TTL a la computadora
// Posteriormente sera analizada por el driver personalizado  
// Las capacidades del microcontrolador serán las siguientes
//      *Envió de trama con la posiciones de todos los encoders y caja de cambios
//      *Reporte de errores desde el microcontrolador a la pc
//      *Recepcion de comandos para configuracion y calibracion de Encoders
//          *Estos se configuran desde una interfaz de usuario
//      *Recepcion de valores para FFB<<Proximamente
//**************************************************************************************
//
//
//-------------------------------------Trama USB--------------------------------------//
// 8bits    |8bits    |8bits    |11bits         |8bits      |8bits      |8bits                  |
//Acelerador|Freno    |Clutch   |Volante        |CajaCambio |Errores MC |Comandos desde el PC   |
/*#include "ComunicacionUSB.h"

struct TramaUSB TramaUSB0={
    .Acelerador=0,
    .Freno=0,
    .Clutch=0,
    .Volante=0,
    .CajaDeCambio=0,
    .ErroresCAE32=0,
    .Comandos=0,
};
struct TramaUSB *ptr_TramaUSB=&TramaUSB0;
*/
//void EnvioDatosUSB(struct TramaUSB *unUSB){
//    //printf("%d,%d,%d,%d,%d,%d,%d\n",unionUSB->Acelerador,unionUSB->Freno,unionUSB->Clutch,unionUSB->Volante,unionUSB->CajaDeCambio,unionUSB->ErroresCAE32,unionUSB->Comandos);
//    printf("as");
//}
/*
void UnionDeTrama(struct TramaUSB *unionUSB){
//Las primeras 4 partes provienen del valor mapeado de cada encoder
   unionUSB->Acelerador=ptr_acelerador->ValorMapeado;
    unionUSB->Freno=ptr_freno->ValorMapeado;
    unionUSB->Clutch=ptr_clutch->ValorMapeado;
    unionUSB->Volante=ptr_volante->ValorMapeado;
    unionUSB->CajaDeCambio=*Velocidad;
    unionUSB->ErroresCAE32=0;
    unionUSB->Comandos=0;


        printf("[ERROR]\tValor fuera de rango\n");
}
*/
void lol(){
    print("asd");
}