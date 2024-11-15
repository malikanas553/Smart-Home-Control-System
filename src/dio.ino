#include "dio.h"

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

void Set_PIN_Direction(volatile uint8_t* ddr, uint8_t pin, uint8_t direction) {
    if (pin >= 8) return; // Invalid pin
    else if (direction == DIO_INPUT) {
        *ddr &= ~(1 << pin); 
    } 
    else if (direction == DIO_OUTPUT) {
        *ddr |= (1 << pin);
    }
    else if (direction == DIO_INPUT_PULLUP) {
        *ddr &= ~(1 << pin); 
        PORTB |= (1 << pin);
    }
}

void Set_PIN_State(volatile uint8_t* port, uint8_t pin, uint8_t state) {

    if (pin >= 8) return; // Invalid pin
    else if (state == HIGH) {
        *port |= (1 << pin);
    } 
    else if (state == LOW) {
        *port &= ~(1 << pin);
    }

}

uint8_t Is_Button_Pressed(volatile uint8_t* pin_reg, uint8_t pin) {

    if (pin >= 8) return; // Invalid pin
    return !(*pin_reg & (1 << pin)); // Return 1 if the pin is LOW (button pressed), 0 if HIGH (button not pressed)

}