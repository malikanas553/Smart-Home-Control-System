# Smart Home Control System Design

| **Author**              | `Seif Salama, Malik Babiker, Mostafa Hatem`          |
|:------------------------|:-----------------------------------------------------|
| **Status**              | `Draft/Inspection/Approved`                          |
| **Version**             | `1.0`                                                |
| **Date**                | `09/12/2024`                                         |

## Introduction

This report outlines the design and low-level implementation of a Smart Home Control System, which monitors temperature and light intensity through analog sensors and controls a fan driven by a DC motor. The system dynamically adjusts fan speed and direction based on sensor readings and user input. Configuration settings, including fan speed and rotation direction, are accessible and adjustable via keypad input. The design is implemented using native C programming, avoiding Arduino-based code or pre-developed libraries to ensure a customized, lightweight, and efficient solution.

### Purpose
The purpose of this specification is to outline the internal structure, functional components, and embedded constraints for implementing the Smart Home Control System, forming the basis for coding and module testing.

### Scope
The scope of this document includes:

- Design and implementation of the Smart Home system.
- Integration of analog sensors, Temperature sensor and LDR, and display of their values on an LCD screen.
- User-configurable settings via keypad input.

This document serves as the reference for both coding and module testing, ensuring that the system works within the defined constraints and meets the project requirements.

The module priority is classified as P2, indicating that it is a necessary part of the system but not critical for initial deployment.

### Defnitions and Acronym
| **Abbreviation** | **Meaning**                                |  
|:----------------:|:------------------------------------------:|  
| ADC              | Analog-to-Digital Converter                |  
| UART             | Universal Asynchronous Receiver Transmitter|  
| LCD              | Liquid Crystal Display                     |  
| POT              | Potentiometer                              |  
| LDR              | Light Dependent Resistor                   |  
| DIO              | Digital Input Output                       |  
| LED              | Light Emitting Diode                       |  
| DC               | Direct Current                             |  
| PWM              | Pulse Width Modulation                     |  
| AC               | Air Conditioning                           |  
| APP              | Application                                |



## Architectural Overview

This section describes where this module resides in the context of the embedded system's software architecture
```plantuml
@@startuml
node "APP" {   
}

node "UART" { 
}

node "Keypad" {
}

node "LCD" {
}

node "DIO" {
}

node "ADC" {
}

node "Microcontroller" {
}

node "PWM" {
}

node "Menu" {
}

node "EEPROM" {
}

node "Register" {
}

node "DC_Motor" {
}

node "Servo" {
}

node "Settings" {
}

node "Sensors" {
}

node "LED" {
}

APP --> UART
APP <-- Keypad
APP --> LCD
APP <-- ADC
APP <--> EEPROM
APP <-- Sensors
APP <--> Settings
APP <-- Menu
APP <-->LED
LED -->DIO
LED -->PWM
EEPROM <--> Microcontroller
UART --> Microcontroller
ADC --> Microcontroller
DIO <--> Microcontroller
Register --> Microcontroller
LCD --> DIO
Menu --> LCD
Keypad --> DIO
PWM <-- Microcontroller
DC_Motor --> PWM
APP <--> DC_Motor
DIO --> Register
Servo --> PWM
APP <--> Servo
Settings --> EEPROM
Settings --> UART
Sensors --> ADC
Sensors --> DIO
Sensors --> UART
@enduml

```

## Functional Description
The Smart Home Control System integrates temperature control with fan simulation and smart lighting with LED control. It reads temperature and light intensity data from sensors, displays values on an LCD, and adjusts fan speed and direction based on the desired temperature set by the user. LED brightness is controlled by light intensity. The user can set the desired temperature via a keypad, and real-time data is transmitted via UART for external monitoring, providing a responsive smart home experience.

## Implementation of the Module
This chapter discusses the detailed design of the Smart Home Control System, which consists of two main parts.

Temperature Control System (Fan Simulation):

- Temperature Sensor: This part of the system uses an ADC to read the temperature values from a sensor. The temperature is then displayed on the LCD. The fan speed 
  and direction can be controlled based on the temperature readings.
- Fan Speed and Direction Control: The fan simulates an air conditioning system. The fan's speed and direction (clockwise or counterclockwise) are adjusted based on 
  the temperature sensor's reading. The user can set the temperature via the keypad, and this value determine when the fan will start and stop operating.

Smart Lighting System (LDR Sensor and LED):

- LDR (Light Dependent Resistor) Sensor: This sensor is used to monitor the surrounding light intensity. The LDR sensor is connected to the ADC, and its readings 
  are displayed on the LCD.
- LED Control: The LED simulates the smart lighting system, and its brightness is adjusted based on the light intensity measured by the LDR. The LED's brightness can 
  be controlled to match desired lighting levels based on the sensor's readings.

## Integration and Configuration
### Static Files

```
| File name     | Contents                             |
|---------------|--------------------------------------|
| main.ino      | Source code for main application     |
| dio.ino       | Source code for DIO functions        |
| dio.h         | Header file for DIO functions        |
| uart.ino      | Source code for UART functions       |
| uart.h        | Header file for UART functions       |
| adc.ino       | Source code for ADC functions        |
| adc.h         | Header file for ADC functions        |
| lcd.ino       | Source code for LCD functions        |
| lcd.h         | Header file for LCD functions        |
| keypad.ino    | Source code for Keypad functions     |
| keypad.h      | Header file for Keypad functions     |
| pwm.ino       | Source code for PWM functions        |
| pwm.h         | Header file for PWM functions        |
| menu.ino      | Source code for menu display         |
| menu.h        | Header file for menu display         |
| dc_motor.ino  | Source code for DC Motor functions   |
| dc_motor.h    | Header file for DC Motor functions   |
| eeprom.ino    | Source code for EEPROM functions     |
| eeprom.h      | Header file for EEPROM functions     |
| servo.ino     | Source code for Servo Motor functions|
| servo.h       | Header file for Servo Motor functions|
| settings.ino  | Source code for settings management  |
| settings.h    | Header file for settings management  |
| sensors.ino   | Source code for sensor data handling |
| sensors.h     | Header file for sensor data handling |
| register.h    | Header file for register definitions |
| led.ino       | Source code for LED functions        |
| led.h         | Header file for LED functions        |


```


### Include Structure

The following diagram shows dependencies upon files in the module.

```plantuml
@startuml
package "Smart_Home_Control_System" {
    [adc.ino] --> [adc.h]
    [lcd.ino] --> [lcd.h]
    [uart.ino] --> [uart.h]
    [keypad.ino] --> [keypad.h]
    [keypad.ino] --> [dio.h]
    [pwm.ino] --> [pwm.h]
    [dc_motor.ino] --> [dc_motor.h]
    [dc_motor.ino] --> [dio.h]
    [dc_motor.ino] --> [pwm.h]
    [menu.ino] --> [lcd.h]
    [menu.ino] --> [uart.h]
    [main.ino] --> [lcd.h]
    [main.ino] --> [uart.h]
    [main.ino] --> [keypad.h]
    [main.ino] --> [dc_motor.h]
    [main.ino] --> [menu.h]
    [dio.ino] --> [register.h]
    [servo.ino] --> [pwm.h]
    [sensors.ino] --> [sensors.h]
    [settings.ino] --> [settings.h]
    [main.ino] --> [keypad.h]
    [main.ino] --> [dc_motor.h]
    [main.ino] --> [menu.h]
    [main.ino] --> [settings.h]
    [main.ino] --> [sensors.h]
}
@enduml

```

### Configuration
Any required hardware/software or system configuration that can be adjusted a header file shall be detailed in this section. This can be placed in the table below.
| Name      | Value Range  | Description                                    |
|-----------|--------------|------------------------------------------------|
| SPEED     | 0 - 1023     | Speed control value for the fan                |
| Direction | 0 - 1        | Direction control for the fan (0: CW, 1: CCW)  |
| TEMP      | 0 - 1023     | Temperature sensor reading range               |
| SAMPLES   | 20           | Number of samples for averaging sensor data    |
