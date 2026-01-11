#include <Arduino.h>
#include "trace_sensor.h"

// Variables to store sensor values
int left_line_sensor_value;
int center_line_sensor_value;
int right_line_sensor_value;
int Black_Line = 500; //Define the threshold value for black line detection

// Initialize line tracking sensors
void trace_sensor_init(){
    pinMode(LEFT_LINE_SENSOR, INPUT);
    pinMode(CENTER_LINE_SENSOR, INPUT);
    pinMode(RIGHT_LINE_SENSOR, INPUT);
}

// Check if center sensor detects the line
bool check_line_center(){
    center_line_sensor_value = analogRead(CENTER_LINE_SENSOR);
    if (center_line_sensor_value > Black_Line){
        return true;
    } else {
        return false;
    }
}

