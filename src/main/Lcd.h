// Include Guard to avoid multiple inclusion
#ifndef __Lcd__
#define __Lcd__ 

#include <stdint.h>

unsigned char CCW_Arrow[] = {
  0b00000,
  0b01110,
  0b01100,
  0b01010,
  0b00001,
  0b00001,
  0b10001,
  0b01110
};

unsigned char CW_Arrow[] = {
  0b00000,
  0b01110,
  0b00110,
  0b01010,
  0b10000,
  0b10000,
  0b10001,
  0b01110
};

unsigned char Back_Arrow[] = {
  B00000,
  B00000,
  B00100,
  B01000,
  B11111,
  B01000,
  B00100,
  B00000
};

// LCD Modes: Command Mode and Data Mode
#define MODE_DATA 1
#define MODE_COMMAND 0

// LCD Commands: Basic Commands
#define CLEAR_DISPLAY 0x01 
#define RETURN_CURSOR_HOME 0x02

// LCD Commands: Entry Mode (Setup Display and Cursor movement)
#define LCD_ENTRY_LEFT 0x04 
#define LCD_ENTRY_LEFT_DISPLAY_RIGHT 0x05
#define LCD_ENTRY_RIGHT 0x06
#define LCD_ENTRY_RIGHT_DISPLAY_LEFT 0x07 

// LCD Commands: Display and Cursor Mode
#define DISPLAY_OFF_CURSOR_OFF 0x08
#define DISPLAY_ON_CURSOR_OFF 0x0C
#define DISPLAY_ON_CURSOR_ON 0x0E
#define DISPLAY_ON_CURSOR_BLINK 0x0F

// LCD Commands: Manual Cursor Shift or Display Shift
#define CURSOR_SHIFT_LEFT 0x10 
#define CURSOR_SHIFT_RIGHT 0x14
#define DISPLAY_SHIFT_LEFT 0x18 
#define DISPLAY_SHIFT_RIGHT 0x1C

// LCD Commands: Cursor Position
#define SET_CURSOR_LINE1 0x80
#define SET_CURSOR_LINE2 0xC0

// LCD Commands: Interface Data Length and Lines
#define LCD_4BIT_1LN 0x20
#define LCD_4BIT_2LN 0x28                                   
#define LCD_8BIT_1LN 0x30
#define LCD_8BIT_2LN 0x38

void LCD_Send (unsigned char char_data, uint8_t mode);
void LCD_Init (void);
void LCD_String (char *str);
void LCD_MoveCursor_xy(uint8_t row, uint8_t pos);
void LCD_String_xy (uint8_t row, uint8_t pos, char *str);
void LCD_Custom_Char (unsigned char loc, unsigned char *pattern);
void LCD_Clear();
#endif