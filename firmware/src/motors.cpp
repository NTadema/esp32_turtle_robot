#include <Arduino.h>
#include "motors.h"

// Initialize motor control pins and PWM
void motors_init() {
    pinMode(L298N_LEFT_IN1_PIN, OUTPUT);
    pinMode(L298N_LEFT_IN2_PIN, OUTPUT);
    pinMode(L298N_RIGHT_IN3_PIN, OUTPUT);
    pinMode(L298N_RIGHT_IN4_PIN, OUTPUT);

    // Setup PWM channels
    ledcSetup(L298N_LEFT_PWM_CHANNEL, 5000, 8);
    ledcSetup(L298N_RIGHT_PWM_CHANNEL, 5000, 8);

    ledcAttachPin(L298N_ENA_PIN, L298N_LEFT_PWM_CHANNEL);
    ledcAttachPin(L298N_ENB_PIN, L298N_RIGHT_PWM_CHANNEL);
}

void set_motors_speed(int left_speed, int right_speed) {
    // Set left motor direction
    if (left_speed > 0) {
        digitalWrite(L298N_LEFT_IN1_PIN, HIGH);
        digitalWrite(L298N_LEFT_IN2_PIN, LOW);
    } else if (left_speed < 0) {
        digitalWrite(L298N_LEFT_IN1_PIN, LOW);
        digitalWrite(L298N_LEFT_IN2_PIN, HIGH);
        left_speed = -left_speed; // Make speed positive for PWM
    } else {
        digitalWrite(L298N_LEFT_IN1_PIN, LOW);
        digitalWrite(L298N_LEFT_IN2_PIN, LOW);
    }

    // Set right motor direction
    if (right_speed > 0) {
        digitalWrite(L298N_RIGHT_IN3_PIN, HIGH);
        digitalWrite(L298N_RIGHT_IN4_PIN, LOW);
    } else if (right_speed < 0) {
        digitalWrite(L298N_RIGHT_IN3_PIN, LOW);
        digitalWrite(L298N_RIGHT_IN4_PIN, HIGH);
        right_speed = -right_speed; // Make speed positive for PWM
    } else {
        digitalWrite(L298N_RIGHT_IN3_PIN, LOW);
        digitalWrite(L298N_RIGHT_IN4_PIN, LOW);
    }

    // Set PWM duty cycle
    ledcWrite(L298N_LEFT_PWM_CHANNEL, left_speed);
    ledcWrite(L298N_RIGHT_PWM_CHANNEL, right_speed);
}

// Stop the robot
void stop_motors(){
    set_motors_speed(0, 0);
}
