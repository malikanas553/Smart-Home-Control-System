#include "Pwm.h"
#include "dio.h"
#include "register.h"

void PWM_Init(){
  Set_PIN_Direction(&DDRD, PD6, DIO_OUTPUT); //Set OC0A as output
  
  // Configure TCCR0A for Non-Inverting Fast PWM mode 3 using OCR A unit
  Register_SetBit(&TCCR0A, COM0A1);
  Register_SetBit(&TCCR0A, WGM01);
  Register_SetBit(&TCCR0A, WGM00);

  // Configure TCCR0B for a prescaler of 1024
  Register_SetBit(&TCCR0B, CS00);
  Register_SetBit(&TCCR0B, CS02);
}

void PWM_SetDutyCycle(char duty,unsigned char pin){
  if (pin == 3) {
    OCR2B = duty;
  } else if (pin == 6) {
    OCR0A = duty;
  } else {
    //invalid pin
    return;
  }
}