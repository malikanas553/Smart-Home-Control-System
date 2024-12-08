#include "servo.h"
#include "Register.h"
#include "dio.h"
#include "Pwm.h"

// Initialize the servo control
void servo_init(void)
{
    // Set PB1 (OC1A) as output
    PWM_Init(PWM_CHANNEL_0B_PD5);
    // Set the TOP value for a 20ms period
    ICR1 = TIMER_TOP;
}

// Set the angle of the servo
void servo_set_angle(uint8_t angle)
{
    if (angle > 180)
        angle = 180; // Limit angle to 180 degrees
    uint16_t pulse_width = SERVO_MIN_PULSE + ((uint32_t)(SERVO_MAX_PULSE - SERVO_MIN_PULSE) * angle) / 180;

    // Convert the pulse width to timer ticks
    PWM_SetDutyCycle(PWM_CHANNEL_0B_PD5, ((16 * pulse_width) / PRESCALER));
}

void servo_swing(void)
{
  uint8_t i;
    for (i = 0; i <= 180; i += 1)  // Increment by 1°
    {
        servo_set_angle(i); // Set servo angle
        _delay_ms(15);      // Allow time for the servo to move
    }
    for (i = 180; i > 0; i -= 1)   // Decrement by 1°
    {
        servo_set_angle(i); // Set servo angle
        _delay_ms(15);      // Allow time for the servo to move
    }
}
