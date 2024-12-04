#ifndef __I2C__
#define __I2C__ 

#include <stdint.h>

#define TWBR (*(volatile uint8_t*)0xB8)  // TWI Bit Rate Register
#define TWSR (*(volatile uint8_t*)0xB9)  // TWI Status Register
#define TWDR (*(volatile uint8_t*)0xBB)  // TWI Data Register
#define TWCR (*(volatile uint8_t*)0xBC)  // TWI Control Register

#define TWINT 7  // TWI Interrupt Flag
#define TWEA  6  // TWI Enable Acknowledge Bit
#define TWSTA 5  // TWI Start Condition Bit
#define TWSTO 4  // TWI Stop Condition Bit
#define TWEN  2  // TWI Enable Bit
#define TWPS0 0  // TWI Prescaler Bit 0
#define TWPS1 1  // TWI Prescaler Bit 1

#define TWI_STATUS_MASK 0xF8

void I2C_Init(void);
uint8_t I2C_Start(uint8_t write_address);
uint8_t I2C_Repeated_Start(uint8_t read_address);
uint8_t I2C_Write(uint8_t data);
uint8_t I2C_Read_Ack(void);
uint8_t I2C_Read_Nack(void);
void I2C_Stop(void);

#endif // I2C_H