#include "Lcd.h"
#include "uart.h"
// LCD function for sending command or data
void AC_Menu(void)
{
    LCD_Clear();
    UART_SendString("AC Chosen\n");
    LCD_String("TMP:");
    LCD_String_xy(1, 0, "1:S/D 2:SET");
    LCD_String_xy(1,13,"3:");
    LCD_Send(BACK,MODE_DATA);
}

void AC_Speed_Menu(void)
{
    LCD_String("SPEED:");
    UART_SendString("AC Speed Option Chosen\n");
    LCD_MoveCursor_xy(0,14);
    LCD_Send(FAN_DIR,MODE_DATA);
    LCD_String_xy(1,0,"4:- 5:+ 6:");
    LCD_Send(CW,MODE_DATA);
    LCD_String_xy(1,13,"3:");
    LCD_Send(BACK,MODE_DATA);
}

void AC_Set_Menu(void)
{
    LCD_Clear();
    LCD_String("TEMP:");
    UART_SendString("AC Temp Option Chosen\n");
    LCD_String_xy(1,0,"4:- 5:+");
    LCD_String_xy(1,13,"3:");
    LCD_Send(BACK,MODE_DATA);
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

void MAIN_Menu(void)
{
    UART_SendString("System Started\n");
    LCD_Send(DISPLAY_ON_CURSOR_OFF, MODE_COMMAND);
    LCD_String("SMART HOME");
    LCD_Send(SET_CURSOR_LINE2, MODE_COMMAND);
    LCD_String("1:AC  2:LDR"); 
}

void LDR_Menu(void)
{
    LCD_Clear();
    UART_SendString("LDR chosen\n");
    LCD_String("Brightness:");
    LCD_String_xy(1, 0, "1:SET");
}

void LDR_Set_Menu(void)
{
    LCD_Clear();
    LCD_String("Light:");
    UART_SendString("LDR set option chosen\n");
    LCD_String_xy(1,0,"4:- 5:+");
    LCD_String_xy(1,13,"3:");
    LCD_Send(BACK,MODE_DATA);
}
