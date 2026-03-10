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

// Move the robot forward
void Forward(){ 
    digitalWrite(L298N_LEFT_IN1_PIN, LOW);
    digitalWrite(L298N_LEFT_IN2_PIN, HIGH);
    digitalWrite(L298N_RIGHT_IN3_PIN, LOW);
    digitalWrite(L298N_RIGHT_IN4_PIN, HIGH);

    ledcWrite(L298N_LEFT_PWM_CHANNEL, DRIVE_SPEED);
    ledcWrite(L298N_RIGHT_PWM_CHANNEL, DRIVE_SPEED);
}

// Move the robot backward
void Backward() {
    digitalWrite(L298N_LEFT_IN1_PIN, HIGH);
    digitalWrite(L298N_LEFT_IN2_PIN, LOW);
    digitalWrite(L298N_RIGHT_IN3_PIN, HIGH);
    digitalWrite(L298N_RIGHT_IN4_PIN, LOW);

    ledcWrite(L298N_LEFT_PWM_CHANNEL, DRIVE_SPEED);
    ledcWrite(L298N_RIGHT_PWM_CHANNEL, DRIVE_SPEED);
}

// Turn the robot to the right
void Right(){
    digitalWrite(L298N_LEFT_IN1_PIN, HIGH);
    digitalWrite(L298N_LEFT_IN2_PIN, LOW);
    digitalWrite(L298N_RIGHT_IN3_PIN, LOW);
    digitalWrite(L298N_RIGHT_IN4_PIN, HIGH);

    ledcWrite(L298N_LEFT_PWM_CHANNEL, TURN_SPEED);
    ledcWrite(L298N_RIGHT_PWM_CHANNEL, TURN_SPEED);
}

// Turn the robot to the left
void Left() {
    digitalWrite(L298N_LEFT_IN1_PIN, LOW);
    digitalWrite(L298N_LEFT_IN2_PIN, HIGH);
    digitalWrite(L298N_RIGHT_IN3_PIN, HIGH);
    digitalWrite(L298N_RIGHT_IN4_PIN, LOW);

    ledcWrite(L298N_LEFT_PWM_CHANNEL, TURN_SPEED);
    ledcWrite(L298N_RIGHT_PWM_CHANNEL, TURN_SPEED);
}

// Stop the robot
void Stop(){
    ledcWrite(L298N_LEFT_PWM_CHANNEL, 0);
    ledcWrite(L298N_RIGHT_PWM_CHANNEL, 0);
}
