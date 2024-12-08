# Smart Home Control System

## 1. Introduction
The Smart Home System project integrates multiple components such as analog-to-digital conversion (ADC), EEPROM storage, servo motor control, DC motor operations, environmental sensing (temperature and light monitoring), and a user menu interface via a keypad and LCD. The primary goal is to create a modular, efficient, and user-friendly system that monitors environmental parameters, stores settings, adjusts devices (motors/servos), and allows user interaction through a menu-driven interface.

### Goals of the Project
The goals of this project include:

* Environmental Monitoring: Real-time temperature and light monitoring through ADC readings from temperature sensors and LDR sensors.
* User Menu Interface: A user-friendly menu navigable via a keypad and displayed on an LCD.
* Motor & Servo Control: Dynamically controlling DC motors and servo motors to automate environmental adjustments based on sensor input or user commands.
* Threshold Alerts: Triggering alerts when temperature or light readings exceed defined thresholds.
* Persistent Settings Storage: Using EEPROM to save and restore user preferences and environmental thresholds.
* Integration: Combining sensors, actuators (motors/servos), and environmental monitoring seamlessly into a single system.


### Problem Addressed
Smart home systems require integrated environmental monitoring, device control, and user interactivity. This project addresses these needs by implementing:

* ADC monitoring for real-time temperature and light data.
* EEPROM storage to ensure settings (thresholds, preferences) persist during power cycles.
* Servo and DC motor control for dynamic adjustments and environmental management.
* User input & menu navigation for intuitive control and environmental preferences configuration.

## 2. Project Code

**GitHub Repository:**
[Smart-Home-Control-System](https://github.com/malikanas553/Smart-Home-Control-System)

**Local Root Directory**
[Source_Code](./src/main)

## 3. Test Cases

Test Cases are developed in Robot Framework Test steps:
[Robot_Tests](./test/assignment_test_cases.robot)

## 4. Bill of Materials (BOM)

**BOM**
[BOM](./bom/BOM.csv)

**Optimized BOM**
[Optimized_BOM](./bom/optimized_bom.csv)

## 5. Design
[Design_Report](./design/project_design_tpl.md)