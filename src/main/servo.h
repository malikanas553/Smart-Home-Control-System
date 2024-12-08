#ifndef SERVO_H
#define SERVO_H
#include <stdint.h>

// Servo configuration constants
#define F_CPU 16000000UL   // 16 MHz clock frequency
#define PRESCALER 8        // Timer1 prescaler value
#define SERVO_PERIOD 20000 // Servo period in microseconds (20ms for 50Hz)
#define TIMER_TOP (F_CPU / (PRESCALER * 1000000UL) * SERVO_PERIOD)

#define SERVO_MIN_PULSE 1000 // Minimum pulse width in microseconds (1ms)
#define SERVO_MAX_PULSE 2000 // Maximum pulse width in microseconds (2ms)

// Function prototypes
void servo_init(void);
void servo_set_angle(uint8_t angle);
void servo_swing(void);
#endif // SERVO_H
