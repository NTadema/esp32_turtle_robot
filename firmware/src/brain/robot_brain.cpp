#include "behaviors/avoid_line.h"
#include "behaviors/avoid_object.h"
#include "drivers/line_sensor.h"
#include "drivers/motors.h"
#include "drivers/ultrasonic_sensor.h"

void robot_brain_loop() {
    float center_distance, left_distance, right_distance;

    //Priority 1: line avoidance
    if(check_line_left() || check_line_center() || check_line_right()){
        avoid_line_behavior();
        return;
    }

    //Priority 2: object avoidance
    scan_environment(center_distance, left_distance, right_distance);
    avoid_object_behavior(center_distance, left_distance, right_distance);
}

