#include "Lcd.h"
#include "uart.h"
// LCD function for sending command or data
void AC_Menu(void)
{
    LCD_String("TMP:");
    LCD_String_xy(1, 0, "1:S/D 2:SET");
    LCD_String_xy(1,13,"3:");
    LCD_Send(BACK,MODE_DATA);
}

void SPEED_Menu(void)
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

void MAIN_Menu(void)
{
    UART_SendString("System Started\n");
    LCD_Send(DISPLAY_ON_CURSOR_OFF, MODE_COMMAND);
    LCD_String("SMART HOME");
    LCD_Send(SET_CURSOR_LINE2, MODE_COMMAND);
    LCD_String("1:AC"); 
}