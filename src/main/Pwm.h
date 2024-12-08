#ifndef __Pwm__
#define __Pwm__

#include <stdint.h>
#include <avr/io.h>

#define PWM_CHANNEL_0A_PD6 0 // Timer 0, OC0A
#define PWM_CHANNEL_0B_PD5 1 // Timer 0, OC0B
#define PWM_CHANNEL_2A_PB3 2 // Timer 2, OC2A
#define PWM_CHANNEL_2B_PD3 3 // Timer 2, OC2B

void PWM_Init(uint8_t channel);
void PWM_SetDutyCycle(uint8_t channel, uint8_t duty);
void PWM_Disable(uint8_t channel);
#endif