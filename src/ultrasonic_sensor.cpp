#include <Arduino.h>
#include "ultrasonic_sensor.h"

// Initialize ultrasonic sensor pins
void ultrasonic_sensor_init() {
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
}

int read_distance(){
    // Send a microsecond pulse to trigger the ultrasonic sensor
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(20);
    digitalWrite(TRIG, LOW);

    // Read the echo pin and calculate distance
    float distance = pulseIn(ECHO, HIGH);
    distance = distance / 58.2; // Convert to cm
    return (int)distance;
}



