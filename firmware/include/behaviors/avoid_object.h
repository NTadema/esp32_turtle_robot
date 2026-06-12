#pragma once

const float OBSTACLE_THRESHOLD = 15.0; // Distance in cm to consider an obstacle

enum ScanState {
    MOVE_FRONT,
    READ_FRONT,
    MOVE_LEFT,
    READ_LEFT,
    MOVE_RIGHT,
    READ_RIGHT,
    MOVE_FRONT_AGAIN,
    READ_FRONT_AGAIN
};

extern ScanState scan_state;

extern unsigned long last_time;
extern const unsigned long settle_time;

extern float front_distance;
extern float left_distance;
extern float right_distance;

extern int obstacle_left_speed;
extern int obstacle_right_speed;

void scan_environment();
void avoid_object_behavior();