#include <Arduino.h>
#include "motors.h"
#include "trace_sensor.h"
#include "ultrasonic_sensor.h"

// Setup function to initialize serial communication, motors, and trace sensors
void setup() {
  Serial.begin(9600);//open serial and set the baudrate
  motors_init();
  trace_sensor_init();
  ultrasonic_sensor_init();
}

// Main loop function to control the robot based on line sensor input
void loop() {
  int distance_cm = read_distance();
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  delay(500); // Wait for 500 milliseconds before the next reading
}