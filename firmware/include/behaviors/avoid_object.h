#pragma once

#define SAFE_DISTANCE 12
#define DANGER_DISTANCE 10
#define SCAN_ANGLE_LEFT 130
#define SCAN_ANGLE_CENTER 100
#define SCAN_ANGLE_RIGHT 60

// Declare variables
extern float center_distance;
extern float left_distance;
extern float right_distance;

extern unsigned long turn_start_time;
extern bool is_turning;
extern const unsigned long TURN_DURATION;

void scan_environment(float &center_distance, float &left_distance, float &right_distance);
void avoid_object_behavior(float center_distance, float left_distance, float right_distance);


