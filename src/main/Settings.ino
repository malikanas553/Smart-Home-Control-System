#include "Settings.h"
#include "Eeprom.h"
#include "uart.h"

void RestoreSettings(void)
{
  // Read FAN_SPEED (2 bytes)
  EEP_Read_Block(&FAN_SPEED, (const void *)SPEED_ADDRESS, sizeof(FAN_SPEED));

  // Read FAN_DIR (1 byte)
  EEP_Read_Block(&FAN_DIR, (const void *)DIR_ADDRESS, sizeof(FAN_DIR));

  // Read AC_TEMP (1 byte)
  EEP_Read_Block(&AC_TEMP, (const void *)TEMP_ADDRESS, sizeof(AC_TEMP));

  EEP_Read_Block(&LDR_THRESHOLD, (const void *)LDR_ADDRESS, sizeof(LDR_THRESHOLD));
}

void HandleACTemperature(unsigned char *ac_temp,char key, unsigned char *new_setting) {
    switch (key) {
        case 5: // Increase AC Temperature
            if (*ac_temp + 1 < 27) { // Check if within the maximum limit
                (*ac_temp)++;
                UART_SendString("AC Temp Increased\n");
                *new_setting = 1;
            } else {
                UART_SendString("AC Temp is at Maximum\n");
            }
            _delay_ms(150);
            break;

        case 4: // Decrease AC Temperature
            if (*ac_temp - 1 > 19) { // Check if within the minimum limit
                (*ac_temp)--;
                UART_SendString("AC Temp Decreased\n");
                *new_setting = 1;
            } else {
                UART_SendString("AC Temp is at Minimum\n");
            }
            _delay_ms(150);
            break;

        default:
            // Do nothing for unsupported keys
            break;
    }
}

void HandleFanSettings(unsigned int *fan_speed, unsigned char *fan_dir,char key, unsigned char *new_setting) {
    switch (key) {
        case 4: // Decrease Fan Speed
            if (*fan_speed - 100 > 0) {
                *fan_speed -= 100;
                DC_SetSpeed(0, *fan_speed); // Set the new fan speed
                UART_SendString("Fan Speed Decreased\n");
                *new_setting = 1;
            } else {
                UART_SendString("Fan Speed is at Minimum\n");
            }
            _delay_ms(150);
            break;

        case 5: // Increase Fan Speed
            if (*fan_speed + 100 < 1100) {
                *fan_speed += 100;
                DC_SetSpeed(0, *fan_speed); // Set the new fan speed
                UART_SendString("Fan Speed Increased\n");
                *new_setting = 1;
            } else {
                UART_SendString("Fan Speed is at Maximum\n");
            }
            _delay_ms(150);
            break;

        case 6: // Toggle Fan Direction
            *fan_dir = (*fan_dir) ? CW : CCW;
            UART_SendString("Fan Direction Toggled\n");
            _delay_ms(150);
            *new_setting = 1;
            break;

        default:
            // Do nothing for unsupported keys
            break;
    }
}

void SaveSettings(void)
{
  // Save FAN_SPEED (2 bytes)
  EEP_Write_Block(&FAN_SPEED, (void *)SPEED_ADDRESS, sizeof(FAN_SPEED));

  // Save FAN_DIR (1 byte)
  EEP_Write_Block(&FAN_DIR, (void *)DIR_ADDRESS, sizeof(FAN_DIR));

  // Save AC_TEMP (1 byte)
  EEP_Write_Block(&AC_TEMP, (void *)TEMP_ADDRESS, sizeof(AC_TEMP));

  EEP_Write_Block(&LDR_THRESHOLD, (void *)LDR_ADDRESS, sizeof(LDR_THRESHOLD));
}