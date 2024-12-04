#ifndef __Pwm__
#define __Pwm__

#define OCR0A  (*(volatile unsigned char*)0x27)
#define OCR0B  (*(volatile unsigned char*)0x28)
#define OCR1AL (*(volatile unsigned char*)0x88)
#define OCR1AH (*(volatile unsigned char*)0x89)
#define OCR1BL (*(volatile unsigned char*)0x8A)
#define OCR1BH (*(volatile unsigned char*)0x8B)
#define OCR2A  (*(volatile unsigned char*)0xB3)
#define OCR2B  (*(volatile unsigned char*)0xB4)

#define TCCR0A (*(volatile unsigned char*)0x24)

#define WGM00  0
#define WGM01  1
#define COM0B0 4
#define COM0B1 5
#define COMOA0 6
#define COM0A1 7

#define TCCR0B (*(volatile unsigned char*)0x25)

#define CS00  0
#define CS01  1
#define CS02  2
#define WGM02 3
#define FOC0B 6
#define FOC0A 7

void PWM_Init(void);
void PWM_SetDutyCycle(unsigned char duty);

#endif
