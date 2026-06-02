#include <Arduino.h>
#include "behaviors/avoid_line.h"
#include "drivers/line_sensor.h"
#include "drivers/motors.h"

int line_left_speed = 0;
int line_right_speed = 0;

// Behavior to avoid lines detected by the line sensors
void avoid_line_behavior() {
    
    bool left = check_line_left();
    bool center = check_line_center();
    bool right = check_line_right();

    if (center) {
        line_left_speed = -REVERSE_SPEED;
        line_right_speed = -REVERSE_SPEED;
        return;
    }

    if (left && right) {
        // intersection: treat as center or stop
        line_left_speed = -REVERSE_SPEED;
        line_right_speed = -REVERSE_SPEED;
        return;
    }

    if (left) {
        line_left_speed = -TURN_SPEED;
        line_right_speed = TURN_SPEED;
        return;
    }

    if (right) {
        line_left_speed = TURN_SPEED;
        line_right_speed = -TURN_SPEED;
        return;
    }
}