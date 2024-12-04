// Include Guard to avoid multiple inclusion
#ifndef __adc__
#define __adc__

#include <stdint.h>

#define ADCL   (*(volatile unsigned char*)0x78) 
#define ADCH   (*(volatile unsigned char*)0x79)  
#define ADC    (*(volatile unsigned short*)0x78) 

#define ADMUX (*(volatile unsigned char*)0x7C)
#define ADCSRA (*(volatile unsigned char*)0x7A)

#define MUX0 0
#define MUX1 1
#define MUX2 2
#define MUX3  3

#define ADLAR 5
#define REFS0  6
#define REFS1  7

#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE  3
#define ADIF  4
#define ADATE 5
#define ADSC  6
#define ADEN  7

void Adc_Init(void);
uint16_t Adc_ReadChannel(uint8_t ch);
uint16_t Adc_Sampling(uint16_t adc_reading, unsigned char SAMPLE_N0);
#endif
