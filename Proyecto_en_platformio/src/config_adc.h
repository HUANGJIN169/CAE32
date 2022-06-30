#include "driver/adc_common.h"
#define ADC_ATT 1.250
void iniciar_adc(){
    adc1_config_width(ADC_WIDTH_BIT_12); 
    adc1_config_channel_atten(ADC1_CHANNEL_4,ADC_ATTEN_DB_2_5);
}
 float calcular_voltaje(){
    float resultado=adc1_get_raw(ADC1_CHANNEL_4)*ADC_ATT/4095;
    return resultado;
 }
 gpio_config_t pin19={
    .pin_bit_mask=1ULL<<19,
    .mode=GPIO_MODE_INPUT,
    .pull_down_en=GPIO_PULLDOWN_ENABLE
};