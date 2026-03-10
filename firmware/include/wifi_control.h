#pragma once

extern unsigned long last_command_time;

// extern WiFi credentials
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

// Initialize WiFi
void wifi_control_init();

// Handle WiFi connections
void wifi_control_loop();