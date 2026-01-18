#pragma once
#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE
#include <IRremote.hpp>
#include "motors.h"

// Define the IR receiver pin
#define IR_RECEIVER_PIN 15

// Declare variables as extern
extern uint32_t last_decoded_raw_data;
extern unsigned long last_command_time;
extern const unsigned long command_timeout;

// Initialize the IR remote control
void ir_remote_control_init();

// Function for translating IR signals
void translate_ir_signal();