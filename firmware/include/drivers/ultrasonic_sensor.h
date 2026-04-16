#pragma once

// Ultrasonic sensor pins
#define ULTRASONIC_TRIG_PIN 19
#define ULTRASONIC_ECHO_PIN 18

// Function to initialize ultrasonic sensor
void ultrasonic_sensor_init();

// Function to read distance from ultrasonic sensor
float read_distance();

// Function to read distance using median filtering
float read_distance_median();
