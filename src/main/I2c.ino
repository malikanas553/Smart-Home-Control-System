#include "I2c.h"
#include "Register.h"

#define F_CPU 16000000UL
#define SCL_CLK 100000
#define BITRATE(TWSR) ((F_CPU / SCL_CLK - 16) / (2 * (1 << (2 * ((TWSR) & 0x03)))))

void I2C_Init(void) {
    *TWBR = BITRATE(0x00);  // Set bit rate based on formula
    Register_ResetBit(TWSR, TWPS0);  // Set prescaler to 1
    Register_ResetBit(TWSR, TWPS1);
}

uint8_t I2C_Start(uint8_t write_address) {
    Register_SetBit(TWCR, TWSTA);  // Generate START condition
    Register_SetBit(TWCR, TWEN);   // Enable TWI
    Register_SetBit(TWCR, TWINT);  // Clear interrupt flag

    while (!Register_GetBit(TWCR, TWINT));  // Wait for completion

    if ((*TWSR & TWI_STATUS_MASK) != 0x08) return 0;  // START not transmitted

    *TWDR = write_address;  // Load slave address with write flag
    Register_SetBit(TWCR, TWEN);  // Enable TWI
    Register_SetBit(TWCR, TWINT); // Clear interrupt flag

    while (!Register_GetBit(TWCR, TWINT));  // Wait for completion

    uint8_t status = *TWSR & TWI_STATUS_MASK;
    if (status == 0x18) return 1;  // SLA+W transmitted, ACK received
    if (status == 0x20) return 2;  // SLA+W transmitted, NACK received
    return 3;  // SLA+W failed
}

uint8_t I2C_Repeated_Start(uint8_t read_address) {
    Register_SetBit(TWCR, TWSTA);  // Generate START condition
    Register_SetBit(TWCR, TWEN);   // Enable TWI
    Register_SetBit(TWCR, TWINT);  // Clear interrupt flag

    while (!Register_GetBit(TWCR, TWINT));  // Wait for completion

    if ((*TWSR & TWI_STATUS_MASK) != 0x10) return 0;  // Repeated START not transmitted

    *TWDR = read_address;  // Load slave address with read flag
    Register_SetBit(TWCR, TWEN);  // Enable TWI
    Register_SetBit(TWCR, TWINT); // Clear interrupt flag

    while (!Register_GetBit(TWCR, TWINT));  // Wait for completion

    uint8_t status = *TWSR & TWI_STATUS_MASK;
    if (status == 0x40) return 1;  // SLA+R transmitted, ACK received
    if (status == 0x48) return 2;  // SLA+R transmitted, NACK received
    return 3;  // SLA+R failed
}

uint8_t I2C_Write(uint8_t data) {
    *TWDR = data;  // Load data into register
    Register_SetBit(TWCR, TWEN);   // Enable TWI
    Register_SetBit(TWCR, TWINT);  // Clear interrupt flag

    while (!Register_GetBit(TWCR, TWINT));  // Wait for completion

    uint8_t status = *TWSR & TWI_STATUS_MASK;
    if (status == 0x28) return 0;  // Data transmitted, ACK received
    if (status == 0x30) return 1;  // Data transmitted, NACK received
    return 2;  // Data transmission failed
}

uint8_t I2C_Read_Ack(void) {
    Register_SetBit(TWCR, TWEA);   // Enable ACK
    Register_SetBit(TWCR, TWEN);   // Enable TWI
    Register_SetBit(TWCR, TWINT);  // Clear interrupt flag

    while (!Register_GetBit(TWCR, TWINT));  // Wait for completion

    return *TWDR;  // Return received data
}

uint8_t I2C_Read_Nack(void) {
    Register_ResetBit(TWCR, TWEA);  // Disable ACK
    Register_SetBit(TWCR, TWEN);    // Enable TWI
    Register_SetBit(TWCR, TWINT);   // Clear interrupt flag

    while (!Register_GetBit(TWCR, TWINT));  // Wait for completion

    return *TWDR;  // Return received data
}

void I2C_Stop(void) {
    Register_SetBit(TWCR, TWSTO);  // Generate STOP condition
    Register_SetBit(TWCR, TWEN);   // Enable TWI
    Register_SetBit(TWCR, TWINT);  // Clear interrupt flag

    while (Register_GetBit(TWCR, TWSTO));  // Wait for STOP to complete
}