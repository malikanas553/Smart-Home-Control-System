# ADC LCD Interface Design

| **Author**              | `Seif Salama, Malik Babiker, Mostafa Hatem`                                       |
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
- Alert mechanism to notify the user when sensor readings exceed the defined limits.

This document serves as the reference for both coding and module testing, ensuring that the system works within the defined constraints and meets the project requirements.

The module priority is classified as P2, indicating that it is a necessary part of the system but not critical for initial deployment.

### Defnitions and Acronym
| **Abbreviation** |             **Meaning**             |
|:----------------:|:-----------------------------------:|
| ADC              | Analog-to-Digital Converter              |
| UART             | Universal Asynchronous Receiver Transmitter |
| LCD              | Liquid Crystal Display                  |
| POT              | Potentiometer                            |
| LDR              | Light Dependent Resistor                |
| DIO              | Digital Input Output                |
| LED              | Light Emitting Diode                |
| DC               | Direct Current                      |
| PWM              | Pulse Width Modulation              |


## Architectural Overview

This section describes where this module resides in the context of the embedded system's software architecture
```plantuml
@startuml
node "APP" {   
}
node "UART" { 
}
node "Keypad"{
}
node "LCD"{
}
node "DIO"{
}
node "ADC"{
}
node "Mircocontroller"{
}
node "DIO"{
}
node "PWM"{
}
node "Menu"{
}
node "EEPROM"{
}
node "Register"{
}
node 
APP --> UART
APP <-- Keypad
APP --> LCD
UART --> Mircocontroller
APP <-- ADC
ADC <-- Mircocontroller
DIO <--> Mircocontroller
LCD --> DIO
Keypad --> DIO

@enduml
```

### Assumptions & Constraints

1. This system assumes stable input from sensors, using averaging to reduce noise.
2. The LCD display has limited character space, requiring concise data representation.
3. The module operates within the 8-bit MCU memory constraints and processing capacity.

```plantuml
@startuml
(*) --> Init
Init --> ConfigureADC_UART_LCD
ConfigureADC_UART_LCD --> AwaitKeyInput
AwaitKeyInput --> SetChannel
SetChannel --> If "Key = 1" then
    If --> DisplayPotValue

else if "Key = 2" then
    If --> DisplayLDRValue

else
    If --> AwaitKeyInput
endif
@enduml
```

## Functional Description
The ADC LCD Interface reads analog values from sensors connected to specified ADC channels. Data is sampled (for noise reduction) and displayed on an LCD. Threshold limits for sensor readings can be adjusted using a keypad, and UART communication sends real-time data to an external monitor.

## Implementation of the Module
This chapter discusses the detailed design of the module.

- ADC Initialization: Initializes ADC for specified channels.
- LCD Display Functions: Displays sensor type, reading, and threshold limits.
- UART Communication: Transmits real-time sensor data over UART.
- Keypad Input Handling: Adjusts LLM/HHM thresholds.

## Integration and Configuration
### Static Files

| File name     | Contents                            |
|---------------|-------------------------------------|
| main.ino      | Source code for main application    |
| dio.ino       | Source code for DIO functions       |
| dio.h         | Header file for DIO functions       |
| uart.ino      | Source code for UART functions      |
| uart.h        | Header file for UART functions      |
| adc.ino       | Source code for ADC functions       |
| adc.h         | Header file for ADC functions       |
| Lcd.ino       | Source code for LCD functions       |
| Lcd.h         | Header file for LCD functions       |
| keypad.ino    | Source code for Keypad functions    |
| keypad.h      | Header file for Keypad functions    |
| pwm.ino       | Source code for PWM functions       |
| pwm.h         | Header file for PWM functions       |
| menu.ino      | Source code for menu display        |
| menu.h        | Header file for menu display        |
| dc_motor.ino  | Source code for DC Motor functions  |
| dc_motor.h    | Header file for DC Motor functions  |
| eeprom.ino    | Source code for EEPROM functions    |
| eeprom.h      | Header file for EEPROM functions    |


### Include Structure

The following diagram shows dependencies upon files in the module.

```plantuml
@startuml
package "ADC_LCD_Module" {
    [adc.c] --> [adc.h]
    [lcd.c] --> [lcd.h]
    [uart.c] --> [uart.h]
    [keypad.c] --> [keypad.h]
    [main.c] --> [adc.h]
    [main.c] --> [lcd.h]
    [main.c] --> [uart.h]
    [main.c] --> [keypad.h]
}
@enduml
```

### Configuration
Any required hardware/software or system configuration that can be adjusted a header file shall be detailed in this section. This can be placed in the table below.
| Name | Value range | Description |
|------|-------------|-------------|
| LLM           | 0 - 1023        | Lower threshold limit for sensor readings     |
| HHM           | 0 - 1023        | Upper threshold limit for sensor readings     |
| UART_BaudRate | 9600            | Baud rate for UART communication              |
| SAMPLE_N0     | 20              | Number of samples for averaging sensor data   |