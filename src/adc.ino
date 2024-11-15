#include "adc.h"

void Adc_Init(void) {
    // AREF = AVcc
    ADMUX = (1<<REFS0);
    // ADC Enable and prescaler of 128, 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t Adc_ReadChannel(uint8_t ch) {
    ch = ch & 0b00000111;  // AND operation with 7 to keep value of ch between 0 and 7
    ADMUX = (ADMUX & 0b11111000)|ch; // clears the bottom 3 bits before ORing
 
    // start single convertion by writing ’1′ to ADSC
     ADCSRA = ADCSRA | (1<<ADSC);
    
    // wait till conversion is complete and ADSC becomes 0
    while (ADCSRA & (1<<ADSC));
    return (ADC);
}
