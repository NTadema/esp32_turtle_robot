#include <Arduino.h>
#include "motors.h"

//    The direction of the robot's movement
//  ENA_PIN   ENB_PIN   IN1   IN2   IN3   IN4   Description 
//  HIGH  HIGH  HIGH  LOW   LOW   HIGH  Robot is moving forward
//  HIGH  HIGH  LOW   HIGH  HIGH  LOW   Robot is moving backward
//  HIGH  HIGH  LOW   HIGH  LOW   HIGH  Robot is turning left
//  HIGH  HIGH  HIGH  LOW   HIGH  LOW   Robot is turning right
//  HIGH  HIGH  LOW   LOW   LOW   LOW   Robot stopped
//  HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  Robot stopped
//  LOW   LOW   N/A   N/A   N/A   N/A   Robot stopped

// Initialize motor control pins and PWM
void motors_init() {
    pinMode(L298N_LEFT_IN1_PIN, OUTPUT);
    pinMode(L298N_LEFT_IN2_PIN, OUTPUT);
    pinMode(L298N_RIGHT_IN3_PIN, OUTPUT);
    pinMode(L298N_RIGHT_IN4_PIN, OUTPUT);

    ledcSetup(L298N_LEFT_PWN_CHANNEL, 5000, 8);
    ledcSetup(L298N_RIGHT_PWN_CHANNEL, 5000, 8);

    ledcAttachPin(L298N_ENA_PIN, L298N_LEFT_PWN_CHANNEL);
    ledcAttachPin(L298N_ENB_PIN, L298N_RIGHT_PWN_CHANNEL);
}

// Move the robot forward
void Forward(){ 
  ledcWrite(L298N_LEFT_PWN_CHANNEL, DRIVE_SPEED); // ENA_PINble L298n A channel
  ledcWrite(L298N_RIGHT_PWN_CHANNEL, DRIVE_SPEED); // ENA_PINble L298n B channel
  digitalWrite(L298N_LEFT_IN1_PIN,LOW); // Set IN1 LOW level
  digitalWrite(L298N_LEFT_IN2_PIN,HIGH);  // Set IN2 HIGH level
  digitalWrite(L298N_RIGHT_IN3_PIN,LOW);  // Set IN3 low level
  digitalWrite(L298N_RIGHT_IN4_PIN,HIGH); // Set IN4 hight level
}

// Move the robot backward
void Backward() {
  ledcWrite(L298N_LEFT_PWN_CHANNEL, DRIVE_SPEED);
  ledcWrite(L298N_RIGHT_PWN_CHANNEL, DRIVE_SPEED);
  digitalWrite(L298N_LEFT_IN1_PIN, HIGH);
  digitalWrite(L298N_LEFT_IN2_PIN, LOW);
  digitalWrite(L298N_RIGHT_IN3_PIN, HIGH);
  digitalWrite(L298N_RIGHT_IN4_PIN, LOW);
}

// Turn the robot to the right
void Right(){
  ledcWrite(L298N_LEFT_PWN_CHANNEL, TURN_SPEED);
  ledcWrite(L298N_RIGHT_PWN_CHANNEL, TURN_SPEED);
  digitalWrite(L298N_LEFT_IN1_PIN, HIGH);
  digitalWrite(L298N_LEFT_IN2_PIN, LOW);
  digitalWrite(L298N_RIGHT_IN3_PIN, LOW);
  digitalWrite(L298N_RIGHT_IN4_PIN, HIGH);
}

// Turn the robot to the left
void Left() {
  ledcWrite(L298N_LEFT_PWN_CHANNEL, TURN_SPEED);
  ledcWrite(L298N_RIGHT_PWN_CHANNEL, TURN_SPEED);
  digitalWrite(L298N_LEFT_IN1_PIN, LOW);
  digitalWrite(L298N_LEFT_IN2_PIN, HIGH);
  digitalWrite(L298N_RIGHT_IN3_PIN, HIGH);
  digitalWrite(L298N_RIGHT_IN4_PIN, LOW);
}

// Stop the robot
void Stop(){
  ledcWrite(L298N_LEFT_PWN_CHANNEL, 0); // Disable L298n A channel
  ledcWrite(L298N_RIGHT_PWN_CHANNEL, 0); // Disable L298n B channel
}