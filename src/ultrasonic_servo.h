#pragma once

// Ultrasonic servo pin
#define ULTRASONIC_SERVO_PIN 16

// Initialize the ultrasonic servo
void ultrasonic_servo_init();

// Set the angle of the ultrasonic servo (0 to 180 degrees)
void set_ultrasonic_servo_angle(int angle);

// Get the current angle of the ultrasonic servo
int get_ultrasonic_servo_angle();