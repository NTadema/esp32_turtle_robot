#include <Arduino.h>
#include "motors.h"
#include "line_sensor.h"
#include "ultrasonic_sensor.h"
#include "ultrasonic_servo.h"

// Setup function to initialize serial communication, motors, and trace sensors
void setup() {
  Serial.begin(9600);//open serial and set the baudrate
  motors_init();
  trace_sensor_init();
  ultrasonic_sensor_init();
  ultrasonic_servo_init();
}

int ultrasonic_angle = (90); // Initial angle for ultrasonic servo
bool sequence_phase = true; // true: phase 1, false: phase 2
int direction = 1; // Direction variable for motor control
int angle_step = 30; // Angle step for servo movement

// Main loop function to control the robot based on line sensor input
void loop() {
    // Move servo
    ultrasonic_servo_set_angle(ultrasonic_angle);
    delay(500);

    // Read distance
    int distance = read_distance();
    Serial.print("Angle: ");
    Serial.print(ultrasonic_angle);
    Serial.print(" Distance: ");
    Serial.println(distance);

    // Update angle according to sequence
    ultrasonic_angle += angle_step * direction;

    if (direction == 1 && ultrasonic_angle >= 150) {
        ultrasonic_angle = 120;
        direction = -1; // start decreasing
    }
    else if (direction == -1 && ultrasonic_angle <= 0) {
        ultrasonic_angle = 30;
        direction = 1; // start increasing
    }
}
