#include "adc.h"
#include "register.h"

void Adc_Init(void) {
    // Set the REFS0 bit to select AVcc as reference
    Register_SetBit(&ADMUX, REFS0);

    // ADC Enable and prescaler of 128, 16000000/128 = 125000
    Register_SetBit(&ADCSRA, ADEN);  // Enable ADC
    Register_SetBit(&ADCSRA, ADPS2); // Set ADC prescaler
    Register_SetBit(&ADCSRA, ADPS1);
    Register_SetBit(&ADCSRA, ADPS0);
}

uint16_t Adc_ReadChannel(uint8_t ch) {
    ch = ch & 0b00000111;  // AND operation with 7 to keep value of ch between 0 and 7
    ADMUX = (ADMUX & 0b11111000)|ch; // clears the bottom 3 bits before ORing
 
    // start single convertion by writing ’1′ to ADSC
    Register_SetBit(&ADCSRA, ADSC);
    
    // wait till conversion is complete and ADSC becomes 0
    while (Register_GetBit(&ADCSRA, ADSC));
    return ADC;
}
