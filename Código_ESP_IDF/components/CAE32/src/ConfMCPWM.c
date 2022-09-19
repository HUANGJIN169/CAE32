#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define PWM0A_PIN 25
#define PWM0B_PIN 33
/**
 * @brief Configura los pines de salida PWM para controlar el sentido de giro del motor
 * 
 */
void mcpwm_gpio_config (){
	ESP_ERROR_CHECK(mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, PWM0A_PIN));    
	ESP_ERROR_CHECK(mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, PWM0B_PIN));    
   }
mcpwm_config_t configPwm = {
    .frequency=1000,
    .cmpr_a=0,
    .cmpr_b=0,
    .counter_mode=MCPWM_UP_COUNTER,
    .duty_mode = MCPWM_DUTY_MODE_0
};
/**
 * @brief Inicia el modulo MCPWM con la prevía configuración (mcpwm_gpio_config) 
 * 
 */
void mcpwm_internal_config (){
	printf("Configuring Initial Parameters of mcpwm0......\n");
	ESP_ERROR_CHECK(mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &configPwm));    //Configure PWM0A & PWM0B with above settings
}
/**
 * @brief Test para conocer si se configuro correctamente el modulo MCPWM, Advertencia (usar exclusivamente un instrumento de medición) si se usa
 * con un motor conectado este se bloquea y puede provocar un corto circuito
 *
 * 
 * @return int 
 */
int testFrecuencia(){
    	uint8_t i = 0;
	float dutyCounter = 0.0;

	while (1) {

		for (i = 0; i < 100; i++){
			
			dutyCounter = i * 1.0;
			ESP_ERROR_CHECK(mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, dutyCounter));
			ESP_ERROR_CHECK(mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_B, dutyCounter));
			printf("Duty = %f \n",dutyCounter);
			vTaskDelay(100);
			}
	}
}