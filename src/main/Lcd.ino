#include "dio.h"
#include "Lcd.h"
#include <util/delay.h>
// LCD function for sending command or data

void LCD_Send(unsigned char data, uint8_t mode) {
    
    LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); // sending upper nibble
    if (mode == MODE_DATA) {
        Set_PIN_State(&RS_EN_Port, RS, HIGH);
    }
    else if (mode == MODE_COMMAND) {
        Set_PIN_State(&RS_EN_Port, RS, LOW);
    }

	Set_PIN_State(&RS_EN_Port, EN, HIGH);
	_delay_us(1);
	Set_PIN_State(&RS_EN_Port, EN, LOW);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4); // sending lower nibble
	Set_PIN_State(&RS_EN_Port, EN, HIGH);
	_delay_us(1);
	Set_PIN_State(&RS_EN_Port, EN, LOW);
	_delay_ms(2);
}


// LCD Initialization function

void LCD_Init (void) {
	_delay_ms(20);			    // LCD Power On delay

	LCD_Send(RETURN_CURSOR_HOME, MODE_COMMAND);
	LCD_Send(LCD_4BIT_2LN, MODE_COMMAND);
	LCD_Send(DISPLAY_ON_CURSOR_OFF, MODE_COMMAND);
	LCD_Send(LCD_ENTRY_RIGHT, MODE_COMMAND);   
	LCD_Send(CLEAR_DISPLAY, MODE_COMMAND);  

	_delay_ms(2);
}

// LCD function for printing string on the screen

void LCD_String (char *str) {
	int i;
	for(i=0;str[i]!=0;i++) {
		LCD_Send (str[i],MODE_DATA);
	}
}

// LCD function for printing string on a specific position

void LCD_String_xy (uint8_t row, uint8_t pos, char *str) {
	if (row == 0 && pos<16)
	  LCD_Send((pos & 0x0F) | SET_CURSOR_LINE1, MODE_COMMAND);

	else if (row == 1 && pos<16)
	  LCD_Send((pos & 0x0F) | SET_CURSOR_LINE2, MODE_COMMAND);
    
	LCD_String(str);	  
}

// LCD function for clearing the screen

void LCD_Clear() {
	LCD_Send(CLEAR_DISPLAY, MODE_COMMAND);		
	_delay_ms(2);
	LCD_Send(SET_CURSOR_LINE1, MODE_COMMAND);
}

void LCD_Custom_Char (unsigned char loc, unsigned char *pattern)
{
	unsigned char i;
	if(loc<8)
	{
		LCD_Send(0x40 + (loc*8),MODE_COMMAND);	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)	/* Write 8 byte for generation of 1 character */
		LCD_Send(pattern[i],MODE_DATA);
	}
}