#include <Arduino.h>
#include "drivers/ultrasonic_sensor.h"

// Initialize ultrasonic sensor pins
void ultrasonic_sensor_init() {
    pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
}

float read_distance(){
    // Send a microsecond pulse to trigger the ultrasonic sensor
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

    // Read the duration of the echo pulse
    unsigned long duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, 30000);

    // Read the echo pin and calculate distance
    float distance = duration * 0.0343 / 2; // Convert to cm
    return distance;
}

float read_distance_median() {
    const int num_samples = 7;
    float samples[num_samples];

    int valid_count = 0;

    // Collect samples
    for (int sample_index = 0; sample_index < num_samples; sample_index++) {
        float distance = read_distance();

        // Reject invalid readings (0 = timeout, very large = no echo)
        if (distance > 0 && distance < 400) {
            samples[valid_count++] = distance;
        }

        delay(20); // small spacing between pings
    }

    // Fallback if nothing valid
    if (valid_count == 0) {
        return 400; // treat as "far away"
    }

    // Sort valid samples (insertion sort)
    for (int sort_index = 1; sort_index < valid_count; sort_index++) {
        float current_value = samples[sort_index];
        int insert_pos = sort_index - 1;

        while (insert_pos >= 0 && samples[insert_pos] > current_value) {
            samples[insert_pos + 1] = samples[insert_pos];
            insert_pos--;
        }
        samples[insert_pos + 1] = current_value;
    }

    return samples[valid_count / 2]; // median
}


