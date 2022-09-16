#include "driver/adc.h" 

#define ADC_ATT 1.750/4095
#define ADC_CHANNEL_ANGULO ADC1_CHANNEL_7

/**
 * @brief Inicializa el ADC y específica la resolución del ADC y selecciona el pin de entrada en este caso el pin 35
 * 
 */
void IniciarAdc(){
    adc1_config_width(ADC_WIDTH_BIT_12); 
    adc1_config_channel_atten(ADC_CHANNEL_ANGULO,ADC_ATTEN_DB_6);
}

/**
 * @brief Calcula el voltaje real en base a la atenuación, revise los valores en la API ADC de ESP-IDF
 * 
 * @return float Voltage real
 */
 float calcular_voltaje(){
    return adc1_get_raw(ADC_CHANNEL_ANGULO);
 }

/**
 * @brief Ecuación para obtener los grados Y=0.078*lectura analógica-30.09
 * @return int Grados reales
 */
int VoltajeAGrados(){
    int grados=adc1_get_raw(ADC_CHANNEL_ANGULO)*0.1203-7.5789; 
    return grados;
}
