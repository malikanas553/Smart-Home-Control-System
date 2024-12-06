#ifndef SERVO_H
#define SERVO_H

// Register addresses
#define DDRB  (*(volatile uint8_t*)0x24) // Data Direction Register for Port B
#define PORTB (*(volatile uint8_t*)0x25) // Port B Data Register
#define TCCR1A (*(volatile uint8_t*)0x80) // Timer/Counter1 Control Register A
#define TCCR1B (*(volatile uint8_t*)0x81) // Timer/Counter1 Control Register B
#define ICR1 (*(volatile uint16_t*)0x86)  // Input Capture Register 1
#define OCR1A (*(volatile uint16_t*)0x88) // Output Compare Register 1A

// Bit masks for Timer/Counter1 control
#define WGM11  1 // Bit 1 in TCCR1A
#define COM1A1 7 // Bit 7 in TCCR1A
#define WGM13  4 // Bit 4 in TCCR1B
#define WGM12  3 // Bit 3 in TCCR1B
#define CS11   1 // Bit 1 in TCCR1B

// Servo configuration constants
#define F_CPU 16000000UL        // 16 MHz clock frequency
#define PRESCALER 8             // Timer1 prescaler value
#define SERVO_PERIOD 20000      // Servo period in microseconds (20ms for 50Hz)
#define TIMER_TOP (F_CPU / (PRESCALER * 1000000UL) * SERVO_PERIOD)

#define SERVO_MIN_PULSE 1000    // Minimum pulse width in microseconds (1ms)
#define SERVO_MAX_PULSE 2000    // Maximum pulse width in microseconds (2ms)

// Function prototypes
void servo_init(void);
void servo_set_angle(uint8_t angle);

#endif // SERVO_H
