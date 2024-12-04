#ifndef __EEPROM__
#define __EEPROM__ 

/* function for clock */
void EEP_Write(unsigned char address, char value);

unsigned char EEP_Read(unsigned char address);

#endif /*#ifndef __EEPROM__*/