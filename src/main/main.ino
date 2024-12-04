#include <util/delay.h>
#include <string.h>
#include "Lcd.h"
#include "adc.h"
#include "dio.h"
#include "uart.h"
#include "keypad.h"
#include "DC_Motor.h"
#include <stdlib.h>


#define SAMPLE_N0 200
#define CW 0
#define CCW 1
#define BACK 2

unsigned char buffer[5];  // Increased buffer size for safety

uint8_t channel; // Variable for choosing a channel

unsigned char samples[SAMPLE_N0]; // Array to store LDR values
uint8_t sample_index = 0; // Index of Samples Array
unsigned int FAN_SPEED = 100;
unsigned char FAN_DIR = 0;
unsigned char AC_TEMP = 20;
unsigned char new_setting = 0;

#define TEMP_ADDRESS 0
#define SPEED_ADDRESS 2
#define DIR_ADDRESS 4

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

void AC_Menu(){
    
    LCD_String("TMP:");
    LCD_String_xy(1, 0, "7:SPEED");
    LCD_String_xy(1,13,"9:");
    LCD_Send(BACK,MODE_DATA);

}

void init() {

  dio_init();
  LCD_Init();
  UART_Init(9600);
  Adc_Init();
  LCD_Custom_Char(CW,CW_Arrow);
  LCD_Custom_Char(CCW,CCW_Arrow);
  LCD_Custom_Char(BACK,Back_Arrow);
  RestoreSettings();

}

int main(void) {

  init();

  while (1) {
    LCD_Clear();
    UART_SendString("System Started\n");
    LCD_Send(DISPLAY_ON_CURSOR_OFF, MODE_COMMAND);
    LCD_String("SMART HOME");
    LCD_Send(SET_CURSOR_LINE2, MODE_COMMAND);
    LCD_String("1:AC"); 
    

    while (key != 1 && key != 2) { // Wait for a key to get pressed
      key = keypad_get_key();
    }

    switch (key) {
      case 1:
          channel = TMP_PIN;
          UART_SendString("AC Chosen\n");
          LCD_Clear();
          AC_Menu();
          break;

      case 2:
          channel = LDR_PIN;
          LCD_Clear();
          LCD_String("LDR:");
          UART_SendString("Light Dependent Resistor Chosen\n");
          break;

      default:
          // Handle invalid key if necessary
          break;
    }


    

    
    while (key != 9) {

        LCD_MoveCursor_xy(0,14);
        LCD_Send(FAN_DIR,MODE_DATA);
        uint16_t adc_reading = Adc_ReadChannel(channel);
        samples[sample_index] = adc_reading;
        sample_index++;
        if(sample_index > SAMPLE_N0 - 1) sample_index = 0;
        unsigned short avg = 0;
        for(uint8_t i = 1; i < SAMPLE_N0 ; i++){
          avg += samples[i];
        }
        avg /= SAMPLE_N0;
        adc_reading = avg;

     

      // Display sensor reading and Send through UART

      itoa(adc_reading, buffer, 10);
      LCD_String_xy(0, 4, buffer);

      if (key == 6){

       FAN_DIR = (FAN_DIR) ? CW : CCW;
       UART_SendString("Fan Direction Toggled\n");
       _delay_ms(150);
       new_setting = 1;


     } else if (key == 7){
          LCD_Clear();
          LCD_String("SPEED:");
          UART_SendString("AC Speed Option Chosen\n");
          LCD_MoveCursor_xy(0,14);
          LCD_Send(FAN_DIR,MODE_DATA);
          LCD_String_xy(1,13,"9:");
          LCD_Send(BACK,MODE_DATA);

          while (key != 9){ // Wait for a key to get pressed
            unsigned char speed[5];
            itoa(FAN_SPEED,speed,10);
            if(key == 5){
              if(FAN_SPEED+100 < 1100){
              FAN_SPEED += 100;
              UART_SendString("Fan Speed Increased\n");
              new_setting = 1;
              }else{
              UART_SendString("Fan Speed is at Maximum\n");
              }
              _delay_ms(150);
            }else if(key == 4){
               if(FAN_SPEED-100 > 0){
                 FAN_SPEED -= 100;
                 UART_SendString("Fan Speed Decreased\n");
                 new_setting = 1;
              }else{
                 UART_SendString("Fan Speed is at Minimum\n");
              }
              _delay_ms(150);
            }

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


