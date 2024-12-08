// Include Guard to avoid multiple inclusion
#ifndef __Menu__
#define __Menu__ 

#include <stdint.h>

#define BACK 2

void AC_Menu(void);
void AC_Speed_Menu(void);
void AC_Set_Menu(void);
void MAIN_Menu(void);
void LDR_Menu(void);
void LDR_Set_Menu(void);
void HandleFanSettings(unsigned int *fan_speed, unsigned char *fan_dir, char key, unsigned char *new_setting);
void HandleACTemperature(unsigned char *ac_temp, char key, unsigned char *new_setting);
#endif