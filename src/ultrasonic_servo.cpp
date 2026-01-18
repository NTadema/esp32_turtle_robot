#include <Arduino.h>
#include <Servo.h>
#include "ultrasonic_servo.h"

Servo ultrasonic_servo;

// Initialize the ultrasonic servo
void ultrasonic_servo_init(){
    ultrasonic_servo.attach(ULTRASONIC_SERVO_PIN, 1000, 2000);
    ultrasonic_servo.write(100); // Set to neutral position
    delay(500);
    ultrasonic_servo.detach(); // Set to neutral position
}

// Set the angle of the ultrasonic servo
void set_ultrasonic_servo_angle(int angle){
    if(angle < 0) angle = 0;
    if(angle > 180) angle = 180;
    ultrasonic_servo.write(angle);
}

// Get the current angle of the ultrasonic servo
int get_ultrasonic_servo_angle(){
    return ultrasonic_servo.read();
}



