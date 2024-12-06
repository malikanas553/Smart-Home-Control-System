#include "DC_Motor.h"
#include "Pwm.h"
#include "dio.h"
// Motor Array[Motor No][Pin]
unsigned char MotorArray[][4] = {
  {PC0, PC1, PB2, PWM_CHANNEL_0A_PD6}
};

void DC_Init(){

    Set_PIN_Direction(&DDRC, MotorArray[0][0], DIO_OUTPUT);
    Set_PIN_Direction(&DDRC, MotorArray[0][1], DIO_OUTPUT);
    Set_PIN_Direction(&DDRB, MotorArray[0][2], DIO_OUTPUT);
    PWM_Init(MotorArray[0][4]);

}


void DC_Start(unsigned char MotorID, unsigned char Direction, unsigned char Speed){

    if (!Direction)
    {
      Set_PIN_State(&PORTC, MotorArray[MotorID][0], HIGH);
      Set_PIN_State(&PORTC, MotorArray[MotorID][1], LOW);
      PWM_SetDutyCycle(Speed,MotorArray[MotorID][4]);

    } else{
      Set_PIN_State(&PORTC, MotorArray[MotorID][0], LOW);
      Set_PIN_State(&PORTC, MotorArray[MotorID][1], HIGH);
      PWM_SetDutyCycle(Speed,MotorArray[MotorID][4]);
    }

}
void DC_SetSpeed(unsigned char MotorID,unsigned char Speed){

  PWM_SetDutyCycle(Speed,MotorArray[MotorID][4]);

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