#pragma once

// Line tracking sensor pin definitions
#define LINE_SENSOR_LEFT_PIN 32
#define LINE_SENSOR_CENTER_PIN 35
#define LINE_SENSOR_RIGHT_PIN 34

// Line tracking sensor pin definitions
void trace_sensor_init();

// Sensor reading functions
bool check_line_center();