#include "DC_Motor.h"
#include "Pwm.h"
#include "dio.h"
// Motor Array[Motor No][Pin]
unsigned char MotorArray[][3] = {
  {4, 5, 6}
};

void DC_Init(){

    Set_PIN_Direction(&DDRD, MotorArray[0][0], DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, MotorArray[0][1], DIO_OUTPUT);
    //PWM_Init();

}


void DC_Start(unsigned char MotorID, tenuDirection Direction, unsigned char Speed){

    if (!DIRECTION_CW)
    {
      Set_PIN_State(&PORTD, MotorArray[MotorID][0], HIGH);
      Set_PIN_State(&PORTD, MotorArray[MotorID][1], LOW);
      PWM_SetDutyCycle(Speed,MotorArray[MotorID][2]);

    } else{
      Set_PIN_State(&PORTD, MotorArray[MotorID][0], LOW);
      Set_PIN_State(&PORTD, MotorArray[MotorID][1], HIGH);
      PWM_SetDutyCycle(Speed,MotorArray[MotorID][2]);
    }

}

void DC_Stop(unsigned char MotorID){

    Set_PIN_State(&PORTD, MotorArray[MotorID][0], HIGH);
    Set_PIN_State(&PORTD, MotorArray[MotorID][1], HIGH);
    
}