#include <Arduino.h>
#include <IRremote.hpp>

#include "drivers/motors.h"
#include "drivers/line_sensor.h"
#include "drivers/ultrasonic_sensor.h"
#include "drivers/ultrasonic_servo.h"
#include "drivers/ir_remote_control.h"
#include "drivers/wifi_control.h"

#include "behaviors/avoid_line.h"
#include "behaviors/avoid_object.h"

#include "brain/robot_brain.h"

// Global command watchdog
unsigned long last_command_time = 0;
const unsigned long command_timeout = 500; // ms

// Turn variables
unsigned long turn_start_time = 0;
bool is_turning = false;
const unsigned long TURN_DURATION = 500; // ms

// Initialize all components
void setup() {
    Serial.begin(9600); // Open serial at 9600 baud
    motors_init();
    trace_sensor_init();
    ultrasonic_sensor_init();
    ultrasonic_servo_init();
    ir_remote_control_init();
    wifi_control_init();
    delay(500);

}

// Main loop
void loop() {
    // Handle IR remote
    if (IrReceiver.decode()) {
        last_command_time = millis();
        translate_ir_signal();
        IrReceiver.resume();
    }
    // Handle UDP WiFi control
    wifi_control_loop();

    // Decide whether to run robot brain
    if (millis() - last_command_time > command_timeout) {
        // No recent manual command, run autonomous brain
        // Autonomous mode
        robot_brain_loop();
    } else {
        // Manual control active, do nothing (motors already updated by manual)
    }
}
