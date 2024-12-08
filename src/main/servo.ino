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
    for (uint8_t i = 0; i <= 180; i++)
    {
        servo_set_angle(i);
        _delay_ms(10);
    }
    for (uint8_t i = 180; i > 0; i--)
    {
        servo_set_angle(i);
        _delay_ms(10);
    }
}