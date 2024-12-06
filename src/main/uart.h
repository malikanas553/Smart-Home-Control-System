// Include Guard to avoid multiple inclusion
#ifndef _uart_
#define _uart_

#include <stdint.h>
#define BUFFER_SIZE 16

#define UCSR0A  (*(volatile unsigned char*)0xC0)

#define UDRE0 5
#define RXC0 7

#define UCSR0B  (*(volatile unsigned char*)0xC1)

#define RXEN0 4
#define TXEN0 3
#define RXCIE0 7

#define UCSR0C  (*(volatile unsigned char*)0xC2)

#define UCSZ00 1
#define UCSZ01 2

#define UBRR0L  (*(volatile unsigned char*)0xC4) 
#define UBRR0H  (*(volatile unsigned char*)0xC5) 
#define UDR0  (*(volatile unsigned char*)0xC6)

volatile char receivedCommand[BUFFER_SIZE];  // Shared buffer for received commands
volatile uint8_t commandIndex = 0;  // Index for command buffer
volatile int rx_flag = 0;  // Flag indicating a command has been received

// Function Declarations
void UART_SetBaudRate(uint32_t baud_rate);
void UART_Init(uint32_t baud_rate);
void UART_SendChar(unsigned char data);
void UART_SendString(char* string);
char UART_Receive();
void UART_ReceiveString(char* buffer, uint16_t bufferSize);
unsigned int UART_ReadInt(void);
void UART_SendInt(uint8_t value);
#endif
