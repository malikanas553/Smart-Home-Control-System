#include "dio.h"
#include "Register.h"
void dio_init(void) {
  
    // lcd dio init
    Set_PIN_Direction(&DDRD, EN, DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, RS, DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, PD4, DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, PD5, DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, PD6, DIO_OUTPUT);
    Set_PIN_Direction(&DDRD, PD7, DIO_OUTPUT);

    // keypad dio init
    Set_PIN_Direction(&DDRB, ROW1_PIN, DIO_OUTPUT);
    Set_PIN_Direction(&DDRB, ROW2_PIN, DIO_OUTPUT);
    Set_PIN_Direction(&DDRB, ROW3_PIN, DIO_OUTPUT);
    Set_PIN_Direction(&DDRB, COL1_PIN, DIO_INPUT_PULLUP);
    Set_PIN_Direction(&DDRB, COL2_PIN, DIO_INPUT_PULLUP);
    Set_PIN_Direction(&DDRB, COL3_PIN, DIO_INPUT_PULLUP);

    // PORTC dio init
    Set_PIN_Direction(&DDRC, LDR_PIN, DIO_INPUT);
    Set_PIN_Direction(&DDRC, POT_PIN, DIO_INPUT);
    Set_PIN_Direction(&DDRC, PC2, DIO_INPUT);
    Set_PIN_Direction(&DDRC, RED_LED_PIN, DIO_OUTPUT);
    Set_PIN_Direction(&DDRC, PC4, DIO_OUTPUT);
    Set_PIN_Direction(&DDRC, PC5, DIO_OUTPUT);

}

void Set_PIN_Direction(volatile unsigned char* ddr, unsigned char pin, uint8_t direction) {

    if (pin >= 8) return; // Invalid pin
    else if (direction == DIO_INPUT) {
        Register_ResetBit(ddr,pin); 
    }
    else if (direction == DIO_OUTPUT) {
        Register_SetBit(ddr,pin);
    }
    else if (direction == DIO_INPUT_PULLUP) {
        Register_ResetBit(ddr,pin);  
        PORTB |= (1 << pin); //I found this here ( don't know it's purpose)
    }

}

void Set_PIN_State(volatile unsigned char* port, unsigned char pin, uint8_t state) {

    if (pin >= 8) return; // Invalid pin
    else if (state == HIGH) {
        Register_SetBit(port,pin); 
    } 
    else if (state == LOW) {
        Register_ResetBit(port,pin); 
    }

}

uint8_t Is_Button_Pressed(volatile unsigned char* pin_reg, unsigned char pin) {

    if (pin >= 8) return; // Invalid pin
    return !(*pin_reg & (1 << pin)); // Return 1 if the pin is LOW (button pressed), 0 if HIGH (button not pressed)

}