#include <Arduino.h>
#include <Servo.h>
#include "behaviors/avoid_object.h"
#include "drivers/ultrasonic_sensor.h"
#include "drivers/ultrasonic_servo.h"
#include "drivers/motors.h"

// Environment scan
void scan_environment(float &center_distance, float &left_distance, float &right_distance) {
    // Center
    set_ultrasonic_servo_angle(SCAN_ANGLE_CENTER);
    center_distance = read_distance_median();

    // Left
    set_ultrasonic_servo_angle(SCAN_ANGLE_LEFT);
    left_distance = read_distance_median();

    // Right
    set_ultrasonic_servo_angle(SCAN_ANGLE_RIGHT);
    right_distance = read_distance_median();

    // Return to center
    set_ultrasonic_servo_angle(SCAN_ANGLE_CENTER);
}

// Obstacle avoidance
void avoid_object_behavior(float center_distance, float left_distance, float right_distance) {

    // If currently turning, check if turn is finished
    if(is_turning) {
        if(millis() - turn_start_time >= TURN_DURATION) {
            // Turn complete, go forward
            set_motors_speed(FORWARD_SPEED, FORWARD_SPEED);
            is_turning = false;
        }
        return; // still turning
    }

    // Decide motion based on largest distance
    if(center_distance >= left_distance && center_distance >= right_distance) {
        // Path straight ahead is safest
        set_motors_speed(FORWARD_SPEED, FORWARD_SPEED);
    } else if(left_distance >= right_distance) {
        // Start left turn
        set_motors_speed(TURN_SPEED, -TURN_SPEED);
        turn_start_time = millis();
        is_turning = true;
    } else {
        // Start right turn
        set_motors_speed(-TURN_SPEED, TURN_SPEED);
        turn_start_time = millis();
        is_turning = true;
    }
}