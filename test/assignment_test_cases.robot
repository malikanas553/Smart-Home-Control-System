*** Settings ***
Documentation     Embedded Systems Project Test Cases for New Application
Setup             Connect Project Circuit

*** Test Cases ***
Test Case 1: Verify System Initialization
    [Documentation] Ensuring the system initializes correctly and retrieves stored settings.

    [Setup steps]
    Power on the microcontroller circuit.

    [Action steps]
    Observe the LCD and Serial Monitor after powering on.

    [Assertion steps]
    Verify that the LCD displays the main menu: "Analog Sensors\n 1:AC 2:LDR".
    Verify the Serial Monitor outputs: "System Initialized".
    Verify that stored settings (FAN_SPEED, FAN_DIR, AC_TEMP) are loaded correctly.

Test Case 2: Verify Main Menu Navigation
    [Documentation] Ensuring correct navigation between main menu options using the keypad.

    [Setup steps]
    Power on the microcontroller circuit.

    [Action steps]
    Press 1 on the keypad.
    Press 3 on the keypad to go back.
    Press 2 on the keypad.
    Press 3 on the keypad to go back.

    [Assertion steps]
    After pressing 1:
      Verify LCD displays the "AC Menu".
      Verify Serial Monitor outputs: "AC Menu Selected".
    After pressing 3:
      Verify LCD returns to the main menu.
      Verify Serial Monitor outputs: "Main Menu".
    After pressing 2:
      Verify LCD displays the "LDR Menu".
      Verify Serial Monitor outputs: "LDR Menu Selected".
    After pressing 3:
      Verify LCD returns to the main menu.
      Verify Serial Monitor outputs: "Main Menu".

Test Case 3: Verify Fan Speed Adjustment
    [Documentation] Ensuring fan speed can be adjusted correctly in the AC Menu.

    [Setup steps]
    Power on the microcontroller circuit.
    Navigate to the AC Menu by pressing 1 on the keypad.

    [Action steps]
    Press 4 to decrease speed.
    Press 5 to increase speed.
    Observe LCD updates and Serial Monitor outputs.

    [Assertion steps]
    After pressing 4:
      Verify FAN_SPEED decreases by 10 units (or by 1 unit if close to the minimum limit).
      Verify LCD displays updated speed.
      Verify Serial Monitor outputs: "Fan Speed Decreased".
    After pressing 5:
      Verify FAN_SPEED increases by 10 units (or by 1 unit if close to the maximum limit).
      Verify LCD displays updated speed.
      Verify Serial Monitor outputs: "Fan Speed Increased".

Test Case 4: Verify AC Temperature Adjustment
    [Documentation] Ensuring the AC temperature can be adjusted correctly in the AC Menu.

    [Setup steps]
    Power on the microcontroller circuit.
    Navigate to the AC Menu by pressing 1 on the keypad.

    [Action steps]
    Press 4 to decrease temperature.
    Press 5 to increase temperature.
    Observe LCD updates and Serial Monitor outputs.

    [Assertion steps]
    After pressing 4:
      Verify AC_TEMP decreases by 1 unit (or remains at the minimum limit).
      Verify LCD displays updated temperature.
      Verify Serial Monitor outputs: "Temperature Decreased".
    After pressing 5:
      Verify AC_TEMP increases by 1 unit (or remains at the maximum limit).
      Verify LCD displays updated temperature.
      Verify Serial Monitor outputs: "Temperature Increased".

Test Case 5: Verify LDR Threshold Adjustment
    [Documentation] Ensuring the LDR threshold can be adjusted correctly in the LDR Menu.

    [Setup steps]
    Power on the microcontroller circuit.
    Navigate to the LDR Menu by pressing 2 on the keypad.

    [Action steps]
    Press 4 to decrease the threshold.
    Press 5 to increase the threshold.
    Observe LCD updates and Serial Monitor outputs.

    [Assertion steps]
    After pressing 4:
      Verify LDR_THRESHOLD decreases by 1 unit (or remains at the minimum limit).
      Verify LCD displays updated threshold.
      Verify Serial Monitor outputs: "LDR Threshold Decreased".
    After pressing 5:
      Verify LDR_THRESHOLD increases by 1 unit (or remains at the maximum limit).
      Verify LCD displays updated threshold.
      Verify Serial Monitor outputs: "LDR Threshold Increased".

Test Case 6: Verify Sensor Readings Display
    [Documentation] Ensuring sensor readings are displayed correctly on the LCD.

    [Setup steps]
    Power on the microcontroller circuit.
    Navigate to the respective menus: AC Menu (press 1) or LDR Menu (press 2).

    [Action steps]
    Simulate varying temperature or light levels.
    Observe LCD updates and Serial Monitor outputs.

    [Assertion steps]
    In AC Menu:
      Verify the LCD displays the correct temperature reading.
      Verify Serial Monitor outputs: "Temperature: {VALUE}".
    In LDR Menu:
      Verify the LCD displays the correct light intensity level.
      Verify Serial Monitor outputs: "Light Level: {VALUE}".

Test Case 7: Verify Settings Save and Restore
    [Documentation] Ensuring settings are saved to EEPROM and restored correctly.

    [Setup steps]
    Power on the microcontroller circuit.
    Adjust FAN_SPEED, FAN_DIR, AC_TEMP, and LDR_THRESHOLD.

    [Action steps]
    Save settings by navigating back to the main menu.
    Power off the system.
    Power on the system.
    Observe restored settings on LCD and Serial Monitor.

    [Assertion steps]
    Verify LCD and Serial Monitor display restored values for FAN_SPEED, FAN_DIR, AC_TEMP, and LDR_THRESHOLD.
    Verify Serial Monitor outputs: "Settings Restored". 

Test Case 8: Verify Fan Direction Toggle
    [Documentation] Ensuring that fan direction can toggle between CW (clockwise) and CCW (counter-clockwise).
    [Setup steps]  
    Power on the microcontroller circuit.  
    Navigate to the AC menu by pressing `1`.  

    [Action steps]  
    Press `6` on the keypad to toggle fan direction.  
    Press `6` again to toggle back.  

    [Assertion steps]  
    After pressing `6`:  
      Verify that fan direction toggles between CW and CCW.  
      Confirm Serial Monitor outputs: **"Fan Direction: CW"** or **"Fan Direction: CCW"**.  

Test Case 9: Verify Temperature Value Limits
    [Documentation] Ensuring that the AC temperature value remains within defined upper and lower bounds.
    [Setup steps]  
    Power on the microcontroller circuit.  
    Navigate to the AC menu by pressing `1`.  

    [Action steps]  
    Press `4` to attempt to decrease temperature below its minimum.  
    Press `5` to attempt to increase temperature above its maximum.  

    [Assertion steps]  
    After repeatedly pressing `4`:  
      Verify that the temperature value does not drop below its defined lower limit.  
      Confirm Serial Monitor outputs: **"Temperature at minimum"**.  
    After repeatedly pressing `5`:  
      Verify that the temperature value does not increase above its defined upper limit.  
      Confirm Serial Monitor outputs: **"Temperature at maximum"**.  

Test Case 10: Verify System Reset Functionality
    [Documentation] Ensuring that a system reset restores settings and clears temporary states.
    [Setup steps]  
    Power on the microcontroller circuit and configure settings such as `FAN_SPEED`, `FAN_DIR`, `AC_TEMP`, and `LDR_THRESHOLD`.  

    [Action steps]  
    Trigger a reset sequence by pressing a reset button.  

    [Assertion steps]  
    After the system resets:  
      Verify that stored settings are restored from EEPROM.  
      Confirm Serial Monitor outputs: **"System Reset Complete"**.  
      Verify that all settings return to their expected states.  

Test Case 11: Verify Sensor Readings Response to Threshold Crossing
    [Documentation] Ensuring that sensor readings and logic trigger actions when sensor readings cross thresholds.
    [Setup steps]  
    Power on the microcontroller circuit.  
    Navigate to the LDR menu or simulate sensor inputs for LDR testing.  

    [Action steps]  
    Simulate light level changes to cross the threshold values.  

    [Assertion steps]  
    When light levels are below the threshold:  
      Verify Serial Monitor outputs: **"LDR_THRESHOLD OK"**.  
      Ensure no LED is activated.  
    When light levels are above the threshold:  
      Verify Serial Monitor outputs: **"STATUS = NOK"**.  
      Confirm that the RED LED is turned on.  

Test Case 12: Verify EEPROM Write and Read Operations for Fan Speed
    [Documentation] Ensuring that settings are correctly saved to and read from EEPROM persistently.
    [Setup steps]  
    Power on the microcontroller circuit.  
    Set a custom fan speed value using keypad adjustments.  

    [Action steps]  
    Save the fan speed settings by navigating back to the main menu. Power-cycle the system.  

    [Assertion steps]  
    After system restart:  
      Verify that fan speed settings have been restored.  
      Confirm Serial Monitor outputs: **"Fan speed restored from EEPROM"**.  

