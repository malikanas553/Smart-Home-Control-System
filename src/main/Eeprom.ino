#include "Eeprom.h"
#include<avr/eeprom.h>


/* function for clock */
void EEP_Write_Byte(unsigned char address, char value)
{

	 eeprom_write_byte ((uint8_t*) address, value); 
  
}

unsigned char EEP_Read_Byte(unsigned char address)
{
	unsigned char byteRead;
	byteRead = eeprom_read_byte((uint8_t*)address); // read the byte in location 23
	return (unsigned char)byteRead;
}

void EEP_Read_Block(void *__dst, const void *__src, size_t __n) {

    eeprom_read_block(__dst, __src, __n); // Call the underlying EEPROM library function

}

void EEP_Write_Block(const void *__src, void *__dst, size_t __n) {

    eeprom_write_block(__src, __dst, __n);
    
}


