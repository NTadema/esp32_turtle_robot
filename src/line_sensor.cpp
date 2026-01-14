#include <Arduino.h>
#include "line_sensor.h"

// Variables to store sensor values
int left_line_sensor_value;
int center_line_sensor_value;
int right_line_sensor_value;
int Black_Line = 500; //Define the threshold value for black line detection

// Initialize line tracking sensors
void trace_sensor_init(){
    pinMode(LINE_SENSOR_LEFT_PIN, INPUT);
    pinMode(LINE_SENSOR_CENTER_PIN, INPUT);
    pinMode(LINE_SENSOR_RIGHT_PIN, INPUT);
}

// Check if center sensor detects the line
bool check_line_center(){
    center_line_sensor_value = analogRead(LINE_SENSOR_CENTER_PIN);
    if (center_line_sensor_value > Black_Line){
        return true;
    } else {
        return false;
    }
}

