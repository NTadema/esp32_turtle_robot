#pragma once

// Line tracking sensor pin definitions
#define LEFT_LINE_SENSOR 32
#define CENTER_LINE_SENSOR 35
#define RIGHT_LINE_SENSOR 34

// Line tracking sensor pin definitions
void trace_sensor_init();

// Sensor reading functions
bool check_line_center();