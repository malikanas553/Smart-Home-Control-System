#include "Settings.h"
#include "Eeprom.h"

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