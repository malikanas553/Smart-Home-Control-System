#include "Led.h"
#include "Pwm.h"
#include "dio.h"


void LED_Init(void){

    Set_PIN_Direction(&DDRD, YELLOW_LED_PIN, DIO_OUTPUT);
    PWM_Init(PWM_CHANNEL_2B_PD3);

}


void LED_ON(unsigned char Brightness){

    PWM_SetDutyCycle(PWM_CHANNEL_2B_PD3,Brightness);
  
}

void LED_OFF(void){
     
     Set_PIN_State(&PORTD, YELLOW_LED_PIN , LOW);
     
}