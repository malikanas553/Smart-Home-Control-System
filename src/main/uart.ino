#include <avr/interrupt.h>
#include "uart.h"

void UART_SetBaudRate(uint32_t baud_rate) {
    uint16_t ubrr = F_CPU / ((baud_rate*16) - 1); // Baud rate formula
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
}

void UART_Init(uint32_t baud_rate) {
    UART_SetBaudRate(baud_rate);
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0); // Enable uart tx and rx
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Set to 8-bit mode
    UCSR0B |= (1 << RXCIE0); // Enable rx interrupt
}

void UART_SendChar(unsigned char data) {
    while (!(UCSR0A & ( 1 << UDRE0))); // Wait until Buffer is empty
    UDR0 = data; 
}

void UART_SendString(char* string) {
    int i = 0;
        while(string[i]) { 
            UART_SendChar(string[i++]); // Loop until string ends
        }
}

char UART_Receive() {
    while((UCSR0A & (1 << RXC0)) == 0); // Wait until data is received
    return UDR0;
}

unsigned int UART_ReadInt(void) {
    unsigned int value = 0;
    while ( ! (UCSR0A & ( 1 << RXC0)) );  //Int is 16 bits so value is shifted to store it
    value = UDR0; // Store in first 8 bits
    value <<= 8;
    value |= UDR0; // Store in 8 lower bits
    return value;
}


void UART_ReceiveString(char* buffer, uint16_t bufferSize) {
    uint16_t i = 0;
    char receivedChar;

    while (i < (bufferSize - 1)) { 
        receivedChar = UART_Receive();

        if (receivedChar == '\n' || receivedChar == '\0') { // If newline or null terminator is received, break
            break;
        }
        
        buffer[i++] = receivedChar; // Store received character in buffer
    }
    buffer[i] = '\0'; // Add null terminator to end of string
}

// UART RX interrupt
ISR(USART_RX_vect) { 
    char receivedChar = UDR0;  // Read recieved charachter

    // Store received character in buffer
    if (commandIndex < BUFFER_SIZE - 1) {
        receivedCommand[commandIndex++] = receivedChar;
    }

    // Check if the received character is the end of a command ('\n' or '\0')
    if (receivedChar == '\n' || receivedChar == '\0') {
        receivedCommand[commandIndex - 1] = '\0';  // Null-terminate string
        rx_flag = 1;  // Indicate that a complete command has been received
    }
}
