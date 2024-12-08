#include "sensors.h"
#include "adc.h"
#include "dio.h"
#include "uart.h"
#include <math.h>

unsigned char samples[SAMPLE_N0]; // Array to store LDR values
uint8_t sample_index = 0; // Index of Samples Array

float Sensors_GetTemperature(uint8_t channel) {
    // Read ADC value
    float tempreatureCelsius = Adc_ReadChannel(TMP_PIN);

	// Convert ADC value to voltage
	tempreatureCelsius *= (vcc / adcResolution);

	// Calculate the thermistor's resistance
	float thermistorResistance = (vcc / tempreatureCelsius - 1.0) * KnownThermistorResistorValue;

	// Calculate temperature using the Beta formula
	float temperatureKelvin = 1.0 / (1.0 / (ThermistorNominalTemperature + 273.15) + (1.0 / ThermistorBetaValue) * log(thermistorResistance / ThermistorNominalResistance));
	tempreatureCelsius = temperatureKelvin - 273.15;
    UART_SendString("Temperature: ");
    UART_SendInt(tempreatureCelsius);
    UART_SendString(" C\n");
    
    return tempreatureCelsius;
}

float Sensors_GetLightLevel(uint8_t channel) {
    // Read ADC value
    float lightLevel = Adc_ReadChannel(LDR_PIN);
    samples[sample_index] = lightLevel;
				sample_index++;
	if (sample_index > SAMPLE_N0 - 1) sample_index = 0;
	unsigned short avg = 0;
	for(uint8_t i = 1; i < SAMPLE_N0 ; i++){
		avg += samples[i];
	}
	avg /= SAMPLE_N0;
    UART_SendString("Light Level: ");
    UART_SendInt(avg);
    UART_SendString("\n");
    return avg;
}