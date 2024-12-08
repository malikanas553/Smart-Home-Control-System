#include <util/delay.h>
#include <string.h>
#include "Lcd.h"
#include "adc.h"
#include "dio.h"
#include "uart.h"
#include "keypad.h"
#include "DC_Motor.h"
#include "Menu.h"
#include <stdlib.h>


#define SAMPLE_N0 50
#define CW 0
#define CCW 1
#define BACK 2
#define TEMP_ADDRESS 0
#define SPEED_ADDRESS 2
#define DIR_ADDRESS 4
#define LDR_MIN 0       // Minimum LDR threshold
#define LDR_MAX 1000    // Maximum LDR threshold

unsigned int LDR_THRESHOLD = 500; // In

unsigned char buffer[5];  // Increased buffer size for safety

uint8_t channel; // Variable for choosing a channel

unsigned char samples[SAMPLE_N0]; // Array to store LDR values
uint8_t sample_index = 0; // Index of Samples Array
unsigned int FAN_SPEED = 100;
unsigned char FAN_DIR = CW;
unsigned char AC_TEMP = 20;
unsigned char new_setting = 0;


void RestoreSettings() {
	// Read FAN_SPEED (2 bytes)
	eeprom_read_block(&FAN_SPEED, (const void*)SPEED_ADDRESS, sizeof(FAN_SPEED));

	// Read FAN_DIR (1 byte)
	eeprom_read_block(&FAN_DIR, (const void*)DIR_ADDRESS, sizeof(FAN_DIR));

	// Read AC_TEMP (1 byte)
	eeprom_read_block(&AC_TEMP, (const void*)TEMP_ADDRESS, sizeof(AC_TEMP));
}

void SaveSettings() {
	// Save FAN_SPEED (2 bytes)
	EEP_Write_Block(&FAN_SPEED, (void *)SPEED_ADDRESS, sizeof(FAN_SPEED));

	// Save FAN_DIR (1 byte)
	EEP_Write_Block(&FAN_DIR, (void *)DIR_ADDRESS, sizeof(FAN_DIR));

	// Save AC_TEMP (1 byte)
	EEP_Write_Block(&AC_TEMP, (void *)TEMP_ADDRESS, sizeof(AC_TEMP));
}
void init() {

	dio_init();
	LCD_Init();
	UART_Init(9600);
	Adc_Init();
	//DC_Init();
	LCD_Custom_Char(CW,CW_Arrow);
	LCD_Custom_Char(CCW,CCW_Arrow);
	LCD_Custom_Char(BACK,Back_Arrow);
	RestoreSettings();

}

int main(void) {

	init();

	while (1) {
		
		//System Initialization
		LCD_Clear();
		MAIN_Menu();


		while (key != 1 && key != 2) { // Wait for a key to get pressed
			key = keypad_get_key();
		}

		switch (key) {
			case 1:
				channel = TMP_PIN;
				AC_Menu();
				_delay_ms(150);
				key = 0;
				break;

			case 2:
				channel = LDR_PIN;
				LDR_Menu();
				_delay_ms(150);
				key = 0;
				break;

			default:
				// Handle invalid key if necessary
				break;
		}

	//While loop for Second Menu (AC/LDR)
		while (key != 3) {
			uint16_t adc_reading;
			adc_reading = Adc_ReadChannel(channel);	
		
			if(channel == TMP_PIN){
			//Add Fan direction if AC chosen
				LCD_MoveCursor_xy(0,14);
				LCD_Send(FAN_DIR,MODE_DATA);
		
				float temp_val;
				temp_val = (adc_reading * 4.88);	// Convert adc value to equivalent voltage
				adc_reading = (temp_val/10);	// LM35 gives output of 10mv/°C
				UART_SendString("Temperature = ");
				UART_SendInt(temp_val);
				UART_SendString(" Degree Celsius\n");
			}

			else if(channel == LDR_PIN){
			
			samples[sample_index] = adc_reading;
			sample_index++;
			if(sample_index > SAMPLE_N0 - 1) sample_index = 0;
			unsigned short avg = 0;
			for(uint8_t i = 1; i < SAMPLE_N0 ; i++){
			avg += samples[i];
			}
			avg /= SAMPLE_N0;
			adc_reading = avg;

			}


			// Display sensor reading
			itoa(adc_reading, buffer, 10);
			LCD_String_xy(0, 4, buffer);
		
			switch (channel){
				case TMP_PIN:
					if (key == 1){
												
						DC_Start(0, FAN_DIR, FAN_SPEED);
						key = '\0';
						LCD_Clear();
						AC_Speed_Menu();

						while (key != 3){ // Wait for a key to get pressed

							unsigned char speed[5];
							itoa(FAN_SPEED,speed,10);
							LCD_MoveCursor_xy(0,14);
							LCD_Send(FAN_DIR,MODE_DATA);

							HandleFanSettings(&FAN_SPEED,&FAN_DIR,key,&new_setting);

							LCD_String_xy(0,6,speed);
							key = keypad_get_key();
							_delay_ms(3);
							LCD_String_xy(0, 6,"    ");

						}

						if(new_setting){
							SaveSettings();
							UART_SendString("Settings Saved");
							new_setting = 0;
						}

						key = '\0';
						_delay_ms(150);
						LCD_Clear();
						AC_Menu();

					} 
					
					else if(key == 2){

						AC_Set_Menu();
						//While Loop for AC_SET MENU
						while (key != 3){ // Wait for a key to get pressed

						unsigned char temp[5];
						itoa(AC_TEMP,temp,10);

						HandleACTemperature(&AC_TEMP, key, &new_setting);

						LCD_String_xy(0,5,temp);
						key = keypad_get_key();
						_delay_ms(3);
						LCD_String_xy(0,5,"    ");

						}

						if(new_setting){
							SaveSettings();
							UART_SendString("Settings Saved");
							new_setting = 0;
						}
					
						key = '\0';
						_delay_ms(150);
						LCD_Clear();
						AC_Menu();

					} 
					break;
				case LDR_PIN:
					if (key == 1) {
						key = '\0';
						LCD_Clear();
						LDR_Set_Menu(); // Display the LDR settings menu

					while (key != 3) { // Wait for the user to press the "back" key
						unsigned char ldr_value[5];
						itoa(LDR_THRESHOLD, ldr_value, 10);

						LCD_String_xy(0, 5, ldr_value); // Display the current threshold
						key = keypad_get_key();
						_delay_ms(3);
						LCD_String_xy(0, 5, "    "); // Clear the previous threshold display

						switch (key) {
							case 4: // Decrease threshold
								if (LDR_THRESHOLD - 1 >= LDR_MIN) {
									LDR_THRESHOLD -= 1;
									UART_SendString("LDR Threshold Decreased\n");
									new_setting = 1;
								} 
								else {
									UART_SendString("LDR Threshold at Minimum\n");
								}
								_delay_ms(150);
								break;

							case 5: // Increase threshold
								if (LDR_THRESHOLD + 1 <= LDR_MAX) {
									LDR_THRESHOLD += 1;
									UART_SendString("LDR Threshold Increased\n");
									new_setting = 1;
								} else {
									UART_SendString("LDR Threshold at Maximum\n");
								}
								_delay_ms(150);
								break;
							default:
								break;
						}
					}

					if (new_setting) {
						SaveSettings();
						UART_SendString("Settings Saved\n");
						new_setting = 0;
					}

					key = '\0';
					_delay_ms(150);
					UART_SendString("Back to LDR Menu\n");
					LCD_Clear();
					LDR_Menu();
					}
					break;

				default:
					break;

			}

				// Check adc_reading range and display status


				// Delay for display refresh and update key

			key = keypad_get_key();
			_delay_ms(3);
			LCD_String_xy(0, 4,"    ");


		}

		key = '\0';  // Reset key for the next iteration

	}

	return 0;
}


