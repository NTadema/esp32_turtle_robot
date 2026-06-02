#include <Arduino.h>
#include "behaviors/avoid_line.h"
#include "behaviors/avoid_object.h"
#include "drivers/line_sensor.h"
#include "drivers/motors.h"
#include "drivers/ultrasonic_sensor.h"


void robot_brain_loop()
{
    avoid_line_behavior();
    scan_environment();
    avoid_object_behavior();

    bool line_detected =
        check_line_left() || check_line_center() || check_line_right();

    bool obstacle_detected =
        (front_distance < OBSTACLE_THRESHOLD or
         left_distance < OBSTACLE_THRESHOLD or
         right_distance < OBSTACLE_THRESHOLD);

    int left = FORWARD_SPEED;
    int right = FORWARD_SPEED;

    // PRIORITY 1: line behavior (strongest safety rule)
    if (line_detected) {
        left = line_left_speed;
        right = line_right_speed;
    }

    // PRIORITY 2: obstacle behavior
    else if (obstacle_detected) {
        // optionally override with obstacle logic variables
        left = obstacle_left_speed;
        right = obstacle_right_speed;
    }

    // PRIORITY 3: default forward motion
    else if (!line_detected && !obstacle_detected) {
        left = FORWARD_SPEED;
        right = FORWARD_SPEED;
    }
    else {
        left = 0;
        right = 0;
    }
    set_motors_speed(left, right);
}




