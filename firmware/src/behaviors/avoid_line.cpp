#include <Arduino.h>
#include "behaviors/avoid_line.h"
#include "drivers/line_sensor.h"
#include "drivers/motors.h"

void avoid_line_behavior() {
    if(check_line_left()){
        set_motors_speed(-TURN_SPEED, TURN_SPEED); // turn right
        delay(400);
    } 
    else if(check_line_right()){
        set_motors_speed(TURN_SPEED, -TURN_SPEED); // turn left
        delay(400);
    } 
    else if(check_line_center()){
        set_motors_speed(0,0);
        delay(200);
        set_motors_speed(-REVERSE_SPEED, -REVERSE_SPEED); // reverse
        delay(400);
    }
}