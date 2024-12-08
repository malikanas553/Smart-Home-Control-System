#ifndef __sensors__
#define __sensors__
#include <stdint.h>

#define KnownThermistorResistorValue 100000 // Value of the known resistor (100kΩ)
#define adcResolution 1023.0 // 10-bit ADC resolution
#define vcc 5.0 // Supply voltage (5V)
#define ThermistorBetaValue 3950.0 // Beta value of the thermistor
#define ThermistorNominalResistance 100000.0 // Resistance at 25°C (100kΩ)
#define ThermistorNominalTemperature 25.0 // Nominal temperature in Celsius (25°C)
#define SAMPLE_N0 50

float Sensors_GetTemperature(uint8_t channel); // Function to read temperature from a thermistor
float Sensors_GetLightLevel(uint8_t channel);  // Function to read light level from an LDR

#endif