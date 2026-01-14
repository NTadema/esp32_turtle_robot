#include <Arduino.h>
#include <Servo.h>
#include "ultrasonic_servo.h"

Servo ultrasonic_servo;

void ultrasonic_servo_init(){
    ultrasonic_servo.attach(ULTRASONIC_SERVO_PIN, 500, 2500);
    ultrasonic_servo.write(90); // Set to neutral position
    delay(1000);
}

void ultrasonic_servo_set_angle(int angle){
    if(angle < 0) angle = 0;
    if(angle > 180) angle = 180;
    ultrasonic_servo.write(angle);
}

int ultrasonic_servo_get_angle(){
    return ultrasonic_servo.read();
}



