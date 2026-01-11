#include <Arduino.h>
#include "motors.h"
#include "trace_sensor.h"

// Setup function to initialize serial communication, motors, and trace sensors
void setup() {
  Serial.begin(9600);//open serial and set the baudrate
  motors_init();
  trace_sensor_init();
}

// Main loop function to control the robot based on line sensor input
void loop() {
  if (check_line_center() == true) {
    Forward();
  }
  else {
    Stop();
    Back();
    delay(2000);
  }
}