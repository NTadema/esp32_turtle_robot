#include <Arduino.h>
#include "behaviors/avoid_line.h"
#include "behaviors/avoid_object.h"
#include "drivers/wifi_control.h"
#include "drivers/line_sensor.h"
#include "drivers/motors.h"
#include "drivers/ultrasonic_sensor.h"
#include "brain/robot_brain.h"

const unsigned long wifi_command_timeout = 1000; // ms

void robot_brain_loop()
{
    wifi_control_loop();

    bool manual =
        (millis() - last_wifi_command_time <= wifi_command_timeout);
        
    int left = 0;
    int right = 0;

    if (manual) {
        left = wifi_left_speed;
        right = wifi_right_speed;
    }
    else {
        avoid_line_behavior();
        scan_environment();
        avoid_object_behavior();

        bool obstacle_detected =
            (front_distance < OBSTACLE_THRESHOLD ||
             left_distance < OBSTACLE_THRESHOLD ||
             right_distance < OBSTACLE_THRESHOLD);

        bool line_detected =
            check_line_left() || check_line_center() || check_line_right();

        if (obstacle_detected) {
            left = obstacle_left_speed;
            right = obstacle_right_speed;
        }
        else if (line_detected) {
            left = line_left_speed;
            right = line_right_speed;
        }
        else {
            left = FORWARD_SPEED;
            right = FORWARD_SPEED;
        }
    }

    set_motors_speed(left, right);
}




