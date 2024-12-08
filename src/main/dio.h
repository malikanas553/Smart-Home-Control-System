// Include Guard to avoid multiple inclusion
#ifndef _dio_ 
#define _dio_

#include <stdint.h>

#define PORTD  (*(volatile unsigned char*)0x2B)
#define DDRD  (*(volatile unsigned char*)0x2A)
#define PIND (*(volatile unsigned char*)0x29)

// Pins (PORTD)
#define PD0 0
#define PD1 1
#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

#define PORTB (*(volatile unsigned char*)0x25)
#define DDRB (*(volatile unsigned char*)0x24)
#define PINB (*(volatile unsigned char*)0x23)

// Pins (PORTB)
#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5



#define PORTC (*(volatile unsigned char*)0x28)
#define DDRC (*(volatile unsigned char*)0x27)
#define PINC (*(volatile unsigned char*)0x26)

// Pins (PORTC)
#define PC0 0
#define PC1 1
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5

#define DIO_INPUT 0
#define DIO_OUTPUT 1
#define DIO_INPUT_PULLUP 2

#define LOW 0
#define HIGH 1

// LCD Pins Port
#define LCD_Dir  DDRD
#define LCD_Port PORTD
#define RS_EN_Dir  DDRC
#define RS_EN_Port PORTC


//LCD Pins
#define EN PC2
#define RS PC3
#define D4 PD4
#define D5 PD2
#define D6 PD6
#define D7 PD7

//LED Pin
#define YELLOW_LED_PIN PD3

// Keypad Pins (PORTB)
#define ROW1_PIN PB0
#define ROW2_PIN PB1
#define ROW3_PIN -1
#define COL1_PIN PB2
#define COL2_PIN PB4
#define COL3_PIN PB5

//Analog Sensors Pin
#define LDR_PIN PC0
#define TMP_PIN PC1

// Function Declarations
void dio_init(void);
void Set_PIN_Direction(volatile unsigned char* ddr, unsigned char pin, uint8_t direction, volatile unsigned char* port = &PORTB);
void Set_PIN_State(volatile unsigned char* port, unsigned char pin, uint8_t state);
uint8_t Is_Button_Pressed(volatile unsigned char* pin_reg, unsigned char pin);

#endif