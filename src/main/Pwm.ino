#include "Pwm.h"
#include "dio.h"
#include "register.h"

void PWM_Init(PWM_Channel channel) {
    switch (channel) {
        case PWM_CHANNEL_0A:
            Set_PIN_Direction(&DDRD, PD6, DIO_OUTPUT); // OC0A on PD6 (Pin 6)
            Register_SetBit(&TCCR0A, COM0A1); // Non-inverting Fast PWM
            Register_SetBit(&TCCR0A, WGM01);  // Fast PWM mode
            Register_SetBit(&TCCR0A, WGM00);  
            Register_SetBit(&TCCR0B, CS00);   // Prescaler 1024
            Register_SetBit(&TCCR0B, CS02);
            break;

        case PWM_CHANNEL_0B:
            Set_PIN_Direction(&DDRD, PD5, DIO_OUTPUT); // OC0B on PD5 (Pin 5)
            Register_SetBit(&TCCR0A, COM0B1); // Non-inverting Fast PWM
            Register_SetBit(&TCCR0A, WGM01);  // Fast PWM mode
            Register_SetBit(&TCCR0A, WGM00);
            Register_SetBit(&TCCR0B, CS00);   // Prescaler 1024
            Register_SetBit(&TCCR0B, CS02);
            break;

        case PWM_CHANNEL_1A:
            Set_PIN_Direction(&DDRB, PB1, DIO_OUTPUT); // OC1A on PB1 (Pin 9)
            Register_SetBit(&TCCR1A, COM1A1); // Non-inverting Fast PWM
            Register_SetBit(&TCCR1A, WGM11);  // Fast PWM mode
            Register_SetBit(&TCCR1A, WGM10);
            Register_SetBit(&TCCR1B, WGM13);  
            Register_SetBit(&TCCR1B, WGM12);
            Register_SetBit(&TCCR1B, CS10);   // Prescaler 1
            break;

        case PWM_CHANNEL_1B:
            Set_PIN_Direction(&DDRB, PB2, DIO_OUTPUT); // OC1B on PB2 (Pin 10)
            Register_SetBit(&TCCR1A, COM1B1); // Non-inverting Fast PWM
            Register_SetBit(&TCCR1A, WGM11);  // Fast PWM mode
            Register_SetBit(&TCCR1A, WGM10);
            Register_SetBit(&TCCR1B, WGM13);  
            Register_SetBit(&TCCR1B, WGM12);
            Register_SetBit(&TCCR1B, CS10);   // Prescaler 1
            break;

        case PWM_CHANNEL_2A:
            Set_PIN_Direction(&DDRD, PD3, DIO_OUTPUT); // OC2A on PD3 (Pin 3)
            Register_SetBit(&TCCR2A, COM2A1); // Non-inverting Fast PWM
            Register_SetBit(&TCCR2A, WGM21);  // Fast PWM mode
            Register_SetBit(&TCCR2A, WGM20);
            Register_SetBit(&TCCR2B, CS20);   // Prescaler 1024
            Register_SetBit(&TCCR2B, CS22);
            break;

        case PWM_CHANNEL_2B:
            Set_PIN_Direction(&DDRB, PB3, DIO_OUTPUT); // OC2B on PB3 (Pin 11)
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


void PWM_SetDutyCycle(PWM_Channel channel, uint8_t duty) {
    switch (channel) {
        case PWM_CHANNEL_0A:
            OCR0A = duty;
            break;

        case PWM_CHANNEL_0B:
            OCR0B = duty;
            break;

        case PWM_CHANNEL_1A:
            OCR1AL = duty & 0xFF;
            OCR1AH = (duty >> 8); 
            break;

        case PWM_CHANNEL_1B:
            OCR1BL = duty & 0xFF;
            OCR1BH = (duty >> 8);
            break;

        case PWM_CHANNEL_2A:
            OCR2A = duty;
            break;

        case PWM_CHANNEL_2B:
            OCR2B = duty;
            break;

        default:
            // Handle invalid channels if needed
            break;
    }
}