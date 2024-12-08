#include <util/delay.h>
#include <string.h>
#include "Lcd.h"
#include "adc.h"
#include "dio.h"
#include "uart.h"
#include "keypad.h"
#include "DC_Motor.h"
#include "Menu.h"
#include "Eeprom.h"
#include "sensors.h"
#include "Led.h"
#include "Settings.h"
#include <stdlib.h>

#define LDR_MIN 10	// Minimum LDR threshold
#define LDR_MAX 250 // Maximum LDR threshold

// In

unsigned char buffer[5]; // Increased buffer size for safety

uint8_t channel; // Variable for choosing a channel

uint16_t adc_reading = 0;

void init()
{
	dio_init();
	LCD_Init();
	UART_Init(9600);
	Adc_Init();
	DC_Init();
	LCD_Custom_Char(CW, CW_Arrow);
	LCD_Custom_Char(CCW, CCW_Arrow);
	LCD_Custom_Char(BACK, Back_Arrow);
	RestoreSettings();
}

int main(void)
{

	init();

	while (1)
	{

		// System Initialization
		LCD_Clear();
		MAIN_Menu();

		while (key != 1 && key != 2)
		{ // Wait for a key to get pressed
			key = keypad_get_key();
		}

		switch (key)
		{
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

		// While loop for Second Menu (AC/LDR)
		while (key != 3)
		{
			adc_reading = Adc_ReadChannel(channel);

			if (channel == TMP_PIN)
			{
				// Add Fan direction if AC chosen
				LCD_MoveCursor_xy(0, 14);
				LCD_Send(FAN_DIR, MODE_DATA);
				adc_reading = Sensors_GetTemperature(channel);

				if (adc_reading > AC_TEMP)
				{
					DC_Start(0, CW, FAN_SPEED);
				}
				else
				{
					DC_Stop(0);
				}
				itoa(adc_reading, buffer, 10);
				LCD_String_xy(0, 4, buffer);
			}

			else if (channel == LDR_PIN)
			{
				adc_reading = Sensors_GetLightLevel(channel);

				if (adc_reading < 20)
				{
					LED_ON(1023);
				}
				else
				{
					LED_OFF();
				}
				itoa(adc_reading, buffer, 10);
				LCD_String_xy(0, 11, buffer);
			}

			// Display sensor reading

			switch (channel)
			{
			case TMP_PIN:
				if (key == 1)
				{

					key = '\0';
					LCD_Clear();
					AC_Speed_Menu();

					while (key != 3)
					{ // Wait for a key to get pressed

						unsigned char speed[5];
						itoa(FAN_SPEED, speed, 10);
						LCD_MoveCursor_xy(0, 14);
						LCD_Send(FAN_DIR, MODE_DATA);

						HandleFanSettings(&FAN_SPEED, &FAN_DIR, key, &new_setting);
						DC_SetSpeed(0, FAN_SPEED);
						DC_SetDirection(0, FAN_DIR);
						LCD_String_xy(0, 6, speed);
						key = keypad_get_key();
						_delay_ms(100);
						LCD_String_xy(0, 6, "    ");
					}

					if (new_setting)
					{
						SaveSettings();
						UART_SendString("Settings Saved");
						new_setting = 0;
					}

					key = '\0';
					_delay_ms(150);
					LCD_Clear();
					AC_Menu();
				}

				else if (key == 2)
				{

					AC_Set_Menu();
					// While Loop for AC_SET MENU
					while (key != 3)
					{ // Wait for a key to get pressed

						unsigned char temp[5];
						itoa(AC_TEMP, temp, 10);

						HandleACTemperature(&AC_TEMP, key, &new_setting);

						LCD_String_xy(0, 5, temp);
						key = keypad_get_key();
						_delay_ms(3);
						LCD_String_xy(0, 5, "    ");
					}

					if (new_setting)
					{
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
				if (key == 1)
				{
					key = '\0';
					LCD_Clear();
					LDR_Set_Menu(); // Display the LDR settings menu

					while (key != 3)
					{ // Wait for the user to press the "back" key
						unsigned char ldr_value[5];
						itoa(LDR_THRESHOLD, ldr_value, 10);

						LCD_String_xy(0, 6, ldr_value); // Display the current threshold
						key = keypad_get_key();
						_delay_ms(3);
						LCD_String_xy(0, 6, "    "); // Clear the previous threshold display

						switch (key)
						{
						case 4: // Decrease threshold
							if (LDR_THRESHOLD - 10 >= 10)
							{
								LDR_THRESHOLD -= 10;
								UART_SendString("LDR Threshold Decreased\n");
								new_setting = 1;
							}
							else
							{
								UART_SendString("LDR Threshold at Minimum\n");
							}
							_delay_ms(150);
							break;

						case 5: // Increase threshold
							if (LDR_THRESHOLD + 10 <= 255)
							{
								LDR_THRESHOLD += 10;
								UART_SendString("LDR Threshold Increased\n");
								new_setting = 1;
							}
							else
							{
								UART_SendString("LDR Threshold at Maximum\n");
							}
							_delay_ms(150);
							break;
						default:
							break;
						}

						LED_ON(LDR_THRESHOLD);
					}

					if (new_setting)
					{
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
			if (channel == TMP_PIN)
			{
				LCD_String_xy(0, 4, "    ");
			}
			else
			{
				LCD_String_xy(0, 11, "    ");
			}
		}

		key = '\0'; // Reset key for the next iteration
		DC_Stop(0);
		LED_OFF();
	}

	return 0;
}
