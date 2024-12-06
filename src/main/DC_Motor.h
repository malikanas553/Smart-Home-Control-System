#ifndef __DC_MOTOR
#define __DC_MOTOR

typedef enum {
    DIRECTION_CW = 0,
    DIRECTION_CCW
} tenuDirection;

void DC_Init();
void DC_Start(unsigned char MotorID, unsigned char Direction, unsigned char Speed);
void DC_SetSpeed(unsigned char MotorID,unsigned char Speed);
void DC_Stop(unsigned char MotorID);

#endif