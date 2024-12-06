#include "Pwm.h"
#include "dio.h"
#include "register.h"

void PWM_Init(uint8_t channel) {
    switch (channel) {
        case PWM_CHANNEL_0A_PD6:
            Set_PIN_Direction(&DDRD, PD6, DIO_OUTPUT); // OC0A on PD6
            Register_SetBit(&TCCR0A, COM0A1); // Non-inverting Fast PWM
            Register_SetBit(&TCCR0A, WGM01);  // Fast PWM mode
            Register_SetBit(&TCCR0A, WGM00);  
            Register_SetBit(&TCCR0B, CS00);   // Prescaler 1024
            Register_SetBit(&TCCR0B, CS02);
            break;

        case PWM_CHANNEL_0B_PD5:
            Set_PIN_Direction(&DDRD, PD5, DIO_OUTPUT); // OC0B on PD5
            Register_SetBit(&TCCR0A, COM0B1); // Non-inverting Fast PWM
            Register_SetBit(&TCCR0A, WGM01);  // Fast PWM mode
            Register_SetBit(&TCCR0A, WGM00);
            Register_SetBit(&TCCR0B, CS00);   // Prescaler 1024
            Register_SetBit(&TCCR0B, CS02);
            break;

        case PWM_CHANNEL_2A_PB3:
            Set_PIN_Direction(&DDRB, PB3, DIO_OUTPUT); // OC2A on PB3
            Register_SetBit(&TCCR2A, COM2A1); // Non-inverting Fast PWM
            Register_SetBit(&TCCR2A, WGM21);  // Fast PWM mode
            Register_SetBit(&TCCR2A, WGM20);
            Register_SetBit(&TCCR2B, CS20);   // Prescaler 1024
            Register_SetBit(&TCCR2B, CS22);
            break;

        case PWM_CHANNEL_2B_PD3:
            Set_PIN_Direction(&DDRD, PD3, DIO_OUTPUT); // OC2B on PD3
            Register_SetBit(&TCCR2A, COM2B1); // Non-inverting Fast PWM
            Register_SetBit(&TCCR2A, WGM21);  // Fast PWM mode
            Register_SetBit(&TCCR2A, WGM20);
            Register_SetBit(&TCCR2B, CS20);   // Prescaler 1024
            Register_SetBit(&TCCR2B, CS22);
            break;

        default:
            break;
    }
}


void PWM_SetDutyCycle(uint8_t channel, uint8_t duty) {
    switch (channel) {
        case PWM_CHANNEL_0A_PD6:
            OCR0A = duty;
            break;

        case PWM_CHANNEL_0B_PD5:
            OCR0B = duty;
            break;

        case PWM_CHANNEL_2A_PB3:
            OCR2A = duty;
            break;

        case PWM_CHANNEL_2B_PD3:
            OCR2B = duty;
            break;

        default:
            // Handle invalid channels if needed
            break;
    }
}