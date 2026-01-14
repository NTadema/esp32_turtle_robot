#pragma once

// L298N pins
#define ENA_PIN 25
#define ENB_PIN 13
#define IN1 26
#define IN2 27
#define IN3 14
#define IN4 12

// PWM channels
#define ENA_CHANNEL 0
#define ENB_CHANNEL 1

// Speed constants
#define SPEED 200
#define TURN_SPEED 120

// Motor pin definitions
void motors_init();

// Motor control functions
void Forward();
void Backward();
void Right();
void Left();
void Stop();