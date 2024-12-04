#ifndef __EEPROM__
#define __EEPROM__ 

/* function for clock */
void EEP_Write_Byte(unsigned char address, char value);

unsigned char EEP_Read_Byte(unsigned char address);

void EEP_Read_Block(void *__dst, const void *__src, size_t __n);

void EEP_Write_Block(const void *__src, void *__dst, size_t __n);

#endif /*#ifndef __EEPROM__*/