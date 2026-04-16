#include <Arduino.h>
#include "drivers/line_sensor.h"

// Variables to store sensor values
int left_line_sensor_value;
int center_line_sensor_value;
int right_line_sensor_value;
int black_Line = 1000; //Define the threshold value for black line detection

// Initialize line tracking sensors
void trace_sensor_init(){
    pinMode(LINE_SENSOR_LEFT_PIN, INPUT);
    pinMode(LINE_SENSOR_CENTER_PIN, INPUT);
    pinMode(LINE_SENSOR_RIGHT_PIN, INPUT);
}

// Check if center sensor detects the line
bool check_line_center(){
    center_line_sensor_value = analogRead(LINE_SENSOR_CENTER_PIN);
    if (center_line_sensor_value < black_Line){
        return true;
    } else {
        return false;
    }
}

// Check if left sensor detects the line
bool check_line_left(){
    left_line_sensor_value = analogRead(LINE_SENSOR_LEFT_PIN);
    if (left_line_sensor_value < black_Line){
        return true;
    } else {
        return false;
    }
}

// Check if right sensor detects the line
bool check_line_right(){
    right_line_sensor_value = analogRead(LINE_SENSOR_RIGHT_PIN);
    if (right_line_sensor_value < black_Line){
        return true;
    } else {
        return false;
    }
}


