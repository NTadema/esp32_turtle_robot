#include <Arduino.h>
#include <IRremote.hpp>

#include "motors.h"
#include "line_sensor.h"
#include "ultrasonic_sensor.h"
#include "ultrasonic_servo.h"
#include "ir_remote_control.h"
#include "wifi_control.h"

// Global command watchdog
unsigned long last_command_time = 0;
const unsigned long command_timeout = 500; // ms

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

    // Safety stop
    if (millis() - last_command_time > command_timeout) {
        stop_motors();
    }
}
