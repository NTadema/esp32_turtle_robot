#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "motors.h"

extern unsigned long last_command_time;

// extern WiFi credentials
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

// Initialize WiFi
void wifi_control_init();

// Handle WiFi connections
void wifi_control_loop();