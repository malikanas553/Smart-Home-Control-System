#include "Led.h"
#include "Pwm.h"
#include "dio.h"


void LED_Init(void){

    PWM_Init(PWM_CHANNEL_2B_PD3);

}


void LED_ON(unsigned char Brightness){
    LED_Init();
    PWM_SetDutyCycle(PWM_CHANNEL_2B_PD3,Brightness);
  
}

void LED_OFF(void){
  
    PWM_Disable(PWM_CHANNEL_2B_PD3);
     
}