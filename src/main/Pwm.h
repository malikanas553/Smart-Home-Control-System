#ifndef __Pwm__
#define __Pwm__

// Timer 0
#define OCR0A  (*(volatile unsigned char*)0x27)
#define OCR0B  (*(volatile unsigned char*)0x28)
#define TCCR0A (*(volatile unsigned char*)0x24)
#define TCCR0B (*(volatile unsigned char*)0x25)

#define WGM00  0
#define WGM01  1
#define COM0B0 4
#define COM0B1 5
#define COMOA0 6
#define COM0A1 7
#define CS00  0
#define CS01  1
#define CS02  2
#define WGM02 3
#define FOC0B 6
#define FOC0A 7

// Timer 1
#define OCR1AL (*(volatile unsigned char*)0x88)
#define OCR1AH (*(volatile unsigned char*)0x89)
#define OCR1BL (*(volatile unsigned char*)0x8A)
#define OCR1BH (*(volatile unsigned char*)0x8B)
#define TCCR1A (*(volatile unsigned char*)0x80)
#define TCCR1B (*(volatile unsigned char*)0x81)

#define WGM10  0
#define WGM11  1
#define COM1B0 4
#define COM1B1 5
#define COM1A0 6
#define COM1A1 7
#define CS10   0
#define CS11   1
#define CS12   2
#define WGM12  3
#define WGM13  4

// Timer 2
#define OCR2A  (*(volatile unsigned char*)0xB3)
#define OCR2B  (*(volatile unsigned char*)0xB4)
#define TCCR2A (*(volatile unsigned char*)0xB0)
#define TCCR2B (*(volatile unsigned char*)0xB1)

#define WGM20  0
#define WGM21  1
#define COM2B0 4
#define COM2B1 5
#define COM2A0 6
#define COM2A1 7
#define CS20   0
#define CS21   1
#define CS22   2

typedef enum {
    PWM_CHANNEL_0A,  // Timer 0, OC0A
    PWM_CHANNEL_0B,  // Timer 0, OC0B
    PWM_CHANNEL_2A,  // Timer 2, OC2A
    PWM_CHANNEL_2B,  // Timer 2, OC2B
    PWM_CHANNEL_1A,  // Timer 1, OC1A
    PWM_CHANNEL_1B   // Timer 1, OC1B
} PWM_Channel;

void PWM_Init(void);
void PWM_SetDutyCycle(unsigned char duty);

#endif
