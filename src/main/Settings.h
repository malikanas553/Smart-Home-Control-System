#ifndef __Settings__
#define __Settings__
#include <stdint.h>

#define CW 0
#define CCW 1
#define TEMP_ADDRESS 0
#define SPEED_ADDRESS 2
#define DIR_ADDRESS 4
#define LDR_ADDRESS 6

unsigned int FAN_SPEED = 100;
unsigned char FAN_DIR = CW;
unsigned char AC_TEMP = 20;
unsigned char new_setting = 0;
unsigned int LDR_THRESHOLD = 100;
// Function prototypes
void RestoreSettings(void);
void SaveSettings(void);
void HandleFanSettings(unsigned int *fan_speed, unsigned char *fan_dir, char key, unsigned char *new_setting);
void HandleACTemperature(unsigned char *ac_temp, char key, unsigned char *new_setting);

#endif