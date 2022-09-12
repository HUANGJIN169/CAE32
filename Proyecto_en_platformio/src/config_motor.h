#include "driver/mcpwm.h"


mcpwm_config_t motor1= {
   .frequency=2500,
   .duty_mode=4,
   .counter_mode=3,
   .cmpr_a=50,
   .cmpr_b=50
   };


void setup(){
    mcpwm_gpio_init(0,0,16);//pin 34 6
    mcpwm_gpio_init(0,1,17);//pin 35 7
    mcpwm_init(0, 0,&motor1);
    
   
}
