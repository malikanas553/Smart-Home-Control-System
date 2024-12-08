#include "DC_Motor.h"
#include "Pwm.h"
#include "dio.h"
// Motor Array[Motor No][Pin]
unsigned char MotorArray[][3] = {
  {PC2, PC3, PWM_CHANNEL_0A_PD6}
};

void DC_Init(){

    Set_PIN_Direction(&DDRC, MotorArray[0][0], DIO_OUTPUT);
    Set_PIN_Direction(&DDRC, MotorArray[0][1], DIO_OUTPUT);
    PWM_Init(MotorArray[0][2]);

}


void DC_Start(unsigned char MotorID, unsigned char Direction, unsigned char Speed){

    if (!Direction)
    {
      Set_PIN_State(&PORTC, MotorArray[MotorID][0], HIGH);
      Set_PIN_State(&PORTC, MotorArray[MotorID][1], LOW);
      PWM_SetDutyCycle(MotorArray[MotorID][2],Speed);

    } else{
      Set_PIN_State(&PORTC, MotorArray[MotorID][0], LOW);
      Set_PIN_State(&PORTC, MotorArray[MotorID][1], HIGH);
      PWM_SetDutyCycle(MotorArray[MotorID][2],Speed);
    }

}
void DC_SetSpeed(unsigned char MotorID,unsigned char Speed){

  PWM_SetDutyCycle(MotorArray[MotorID][2],Speed);

}

void DC_SetDirection(unsigned char MotorID, unsigned char Direction){
    if (!Direction)
    {
      Set_PIN_State(&PORTC, MotorArray[MotorID][0], HIGH);
      Set_PIN_State(&PORTC, MotorArray[MotorID][1], LOW);

    } else{
      Set_PIN_State(&PORTC, MotorArray[MotorID][0], LOW);
      Set_PIN_State(&PORTC, MotorArray[MotorID][1], HIGH);
    }

}
void DC_Stop(unsigned char MotorID){

    Set_PIN_State(&PORTC, MotorArray[MotorID][0], HIGH);
    Set_PIN_State(&PORTC, MotorArray[MotorID][1], HIGH);
    
}