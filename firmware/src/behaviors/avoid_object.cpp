#include <Arduino.h>
#include <Servo.h>
#include "behaviors/avoid_object.h"
#include "drivers/ultrasonic_sensor.h"
#include "drivers/ultrasonic_servo.h"
#include "drivers/motors.h"

float front_distance = 300;
float left_distance = 300;
float right_distance = 300;

int obstacle_left_speed = 0;
int obstacle_right_speed = 0;

unsigned long last_time = 0;
const unsigned long settle_time = 500; // Time in ms to wait for servo to settle before reading distance
ScanState scan_state = MOVE_LEFT;

void scan_environment() {
    unsigned long now = millis();

    switch (scan_state) {
        case MOVE_LEFT:
            set_ultrasonic_servo_angle(45);
            last_time = now;
            scan_state = READ_LEFT;
            break;

        case READ_LEFT:
            if (now - last_time >= settle_time) {
                left_distance = read_distance_median();
                scan_state = MOVE_FRONT;
            }
            break;
        case MOVE_FRONT:
            set_ultrasonic_servo_angle(100);
            last_time = now;
            scan_state = READ_FRONT;
            break;

        case READ_FRONT:
            if (now - last_time >= settle_time) {
                front_distance = read_distance_median();
                scan_state = MOVE_RIGHT;
            }
            break;

        case MOVE_RIGHT:
            set_ultrasonic_servo_angle(145);
            last_time = now;
            scan_state = READ_RIGHT;
            break;

        case READ_RIGHT:
            if (now - last_time >= settle_time) {
                right_distance = read_distance_median();
                scan_state = MOVE_FRONT_AGAIN;
            }
            break;
        case MOVE_FRONT_AGAIN:
            set_ultrasonic_servo_angle(100);
            last_time = now;
            scan_state = READ_FRONT_AGAIN;
            break;

        case READ_FRONT_AGAIN:
            if (now - last_time >= settle_time) {
                front_distance = read_distance_median();
                scan_state = MOVE_LEFT;
            }
            break;
    }
}

void avoid_object_behavior() {
    // Simple obstacle avoidance logic based on latest distance readings
    if (front_distance < OBSTACLE_THRESHOLD) {
        if (left_distance > right_distance) {
            // Turn left
            obstacle_left_speed = -TURN_SPEED;
            obstacle_right_speed = TURN_SPEED;
        } else {
            // Turn right
            obstacle_left_speed = TURN_SPEED;
            obstacle_right_speed = -TURN_SPEED;
        }
    } 
    else
    if (left_distance < OBSTACLE_THRESHOLD) {
        // Turn right to avoid left obstacle
        obstacle_left_speed = TURN_SPEED;
        obstacle_right_speed = -TURN_SPEED;
    } else if (right_distance < OBSTACLE_THRESHOLD) {
        // Turn left to avoid right obstacle
        obstacle_left_speed = -TURN_SPEED;
        obstacle_right_speed = TURN_SPEED;
    }
}
