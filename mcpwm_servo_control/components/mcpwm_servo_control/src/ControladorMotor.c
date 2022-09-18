#include "stdbool.h"
#include "driver/mcpwm.h"
#include "driver/adc.h" 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ConfADC.h"
#include "driver/gpio.h"


#define ADC_CHANNEL_ANGULO ADC1_CHANNEL_7



void ConfPinEntrada (){
gpio_config_t BotonRutina={
    .mode=GPIO_MODE_INPUT,
    .pull_up_en=GPIO_PULLUP_ENABLE,
    .pin_bit_mask=GPIO_NUM_13,
};
gpio_config(&BotonRutina);
}

void FrenarMotor(){
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A);
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B);
    vTaskDelay(100/ portTICK_PERIOD_MS);
}

void MoverSentidoHorario(float cicloDeTrabajo){
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, cicloDeTrabajo);
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
}

void MoverSentidoAntihorario(float cicloDeTrabajo){
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, cicloDeTrabajo);
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);  //call this each time, if operator was previously in low/high state
}

void MoverSentidoGiro(float cicloDeTrabajo, int sentidoDeGiro){
    int signal_low_opr=0;
    int duty_type_opr=0;
    switch (sentidoDeGiro)
    {
    case 1://Sentido horario
        signal_low_opr=1;
        duty_type_opr=0;
        break;
    case -1://Sentido antihorario
        signal_low_opr=0;
        duty_type_opr=1;

        break;
    default:
        break;
    }
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, signal_low_opr);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, duty_type_opr, cicloDeTrabajo);
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, duty_type_opr, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
    //vTaskDelay(500/ portTICK_PERIOD_MS);
}

/**
 * @brief Mueve el motor por un tiempo definido, además de elegir el sentido de giro y la potencia
 * 
 * @param milisegundos 
 * @param sentidoDeGiro true=Derecha(Sentido horario) false=Izquierda (Sentido antihorario) 
 * @param cicloDeTrabajo 
 */
void MoverMotorPorTiempo(int milisegundos,int sentidoDeGiro,float cicloDeTrabajo){
    MoverSentidoGiro(cicloDeTrabajo,sentidoDeGiro);
    vTaskDelay(milisegundos / portTICK_PERIOD_MS);
    FrenarMotor();

}
/**
 * @brief Mueve el indicador a los grados deseados
 * 
 * @param gradosDeseados 
 *
 * @param cicloDeTrabajo 
 * @return true 
 * @return false 
 */
bool MoverMotorAGrados(int gradosDeseados,float cicloDeTrabajo){ //Agregar la caracteristica de control PID
    if (gradosDeseados>270)
    {
        return false;
    }
   

    do
    {
      printf("/*LALO,%d,%d*/\n",VoltajeAGrados(),gradosDeseados);
      if (gradosDeseados>VoltajeAGrados()){
        //gira a la derecha
        MoverSentidoGiro(cicloDeTrabajo,-1);
      }
    else{
        //gira a la izquierda
     
        MoverSentidoGiro(cicloDeTrabajo,1);
    }
      vTaskDelay(110/ portTICK_PERIOD_MS);
      
    } while (VoltajeAGrados()!=gradosDeseados);
     FrenarMotor();
    return true;
}