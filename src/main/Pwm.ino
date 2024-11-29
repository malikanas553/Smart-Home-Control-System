#include  "Pwm.h"

void PWM_Init(){

  DDRD |= (1<<PD6);    //Fast PWM output at OC0A pin
  TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);	//Non-Inverting Fast PWM mode 3 using OCR A unit
	TCCR0B |= (1<<CS00) | (1<<CS02);	//Prescalar over 1024

}

void Pwm_SetDutyCycle(char duty,unsigned char pin){

  if(pin == 3){
    OCR2B = duty;
  }else if(pin == 6){
    OCR0A = duty;
  }
  
}