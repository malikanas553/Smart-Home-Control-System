#include "servo.h"

// Initialize the servo control
void servo_init(void) {
    // Set PB1 (OC1A) as output
    DDRB |= (1 << 1); 

    // Configure Timer1 for Fast PWM mode
    TCCR1A |= (1 << WGM11) | (1 << COM1A1);  // Fast PWM, clear OC1A on compare match
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);  // Prescaler 8

    // Set the TOP value for a 20ms period
    ICR1 = TIMER_TOP;
}

// Set the angle of the servo
void servo_set_angle(uint8_t angle) {
    if (angle > 180) angle = 180;  // Limit angle to 180 degrees
    uint16_t pulse_width = SERVO_MIN_PULSE + ((uint32_t)(SERVO_MAX_PULSE - SERVO_MIN_PULSE) * angle) / 180;
    
    // Convert the pulse width to timer ticks
    OCR1A = (16 * pulse_width) / PRESCALER;
}
