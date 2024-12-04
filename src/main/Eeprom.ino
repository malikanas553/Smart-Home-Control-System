#include "Eeprom.h"
#include<avr/eeprom.h>

/* function for clock */
void EEP_Write(unsigned char address, char value)
{

	eeprom_write_byte ((uint8_t*) address, value); 
  
}

unsigned char EEP_Read(unsigned char address)
{
	unsigned char byteRead;
	byteRead = eeprom_read_byte((uint8_t*)address); // read the byte in location 23
	return (unsigned char)byteRead;
}
