#pragma once

// Ultrasonic sensor pins
#define TRIG 19
#define ECHO 18

// Function to initialize ultrasonic sensor
void ultrasonic_sensor_init();

// Function to read distance from ultrasonic sensor
int read_distance();
