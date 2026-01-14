#include <Arduino.h>
#include "ultrasonic_sensor.h"

// Initialize ultrasonic sensor pins
void ultrasonic_sensor_init() {
    pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
}

float read_distance(){
    // Send a microsecond pulse to trigger the ultrasonic sensor
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

     // Read echo pulse (timeout 30 ms)
    unsigned long duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, 30000);
    if (duration == 0) return -1; // no echo detected
    
    // Read the echo pin and calculate distance
    float distance = duration / 58.2; // Convert to cm
    return distance;
}



