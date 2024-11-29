#include "DC_Motor.h"
#include "Pwm.h"

// Motor Array[Motor No][Pin]
unsigned char MotorArray[][3] = {
  {4, 5, 6}
};

void DC_Init(){

    DDRD |=  (1 << MotorArray[0][0]);
    DDRD |=  (1 << MotorArray[0][1]);
    PWM_Init();
}


void DC_Start(unsigned char MotorID, tenuDirection Direction, unsigned char Speed){
    if (!DIRECTION_CW)
    {
      
      PORTD |=  (1 << MotorArray[MotorID][0]);
      PORTD &=  ~(1 << MotorArray[MotorID][1]);
      Pwm_SetDutyCycle(Speed,MotorArray[MotorID][2]);

    } else{
      PORTD &=  ~(1 << MotorArray[MotorID][0]);
      PORTD |=  (1 << MotorArray[MotorID][1]);
      Pwm_SetDutyCycle(Speed,MotorArray[MotorID][2]);
    }
}

void DC_Stop(unsigned char MotorID){
    PORTD |=  (1 << MotorArray[MotorID][0]);
    PORTD |=  (1 << MotorArray[MotorID][1]);
}