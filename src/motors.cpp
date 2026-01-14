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
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    ledcSetup(ENA_CHANNEL, 5000, 8);
    ledcSetup(ENB_CHANNEL, 5000, 8);

    ledcAttachPin(ENA_PIN, ENA_CHANNEL);
    ledcAttachPin(ENB_PIN, ENB_CHANNEL);
}

// Move the robot forward
void Forward(){ 
  ledcWrite(ENA_CHANNEL, SPEED); // ENA_PINble L298n A channel
  ledcWrite(ENB_CHANNEL, SPEED); // ENA_PINble L298n B channel
  digitalWrite(IN1,LOW); // Set IN1 LOW level
  digitalWrite(IN2,HIGH);  // Set IN2 HIGH level
  digitalWrite(IN3,LOW);  // Set IN3 low level
  digitalWrite(IN4,HIGH); // Set IN4 hight level
}

// Move the robot backward
void Backward() {
  ledcWrite(ENA_CHANNEL, SPEED);
  ledcWrite(ENB_CHANNEL, SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Turn the robot to the right
void Right(){
  ledcWrite(ENA_CHANNEL, TURN_SPEED);
  ledcWrite(ENB_CHANNEL, TURN_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Turn the robot to the left
void Left() {
  ledcWrite(ENA_CHANNEL, TURN_SPEED);
  ledcWrite(ENB_CHANNEL, TURN_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Stop the robot
void Stop(){
  ledcWrite(ENA_CHANNEL, 0); // Disable L298n A channel
  ledcWrite(ENB_CHANNEL, 0); // Disable L298n B channel
}