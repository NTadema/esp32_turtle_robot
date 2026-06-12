#pragma onc
#include <WiFiUdp.h>

// Define credentials
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

// Wi-Fi UDP server
extern WiFiUDP udp;
extern const int UDP_PORT;
extern char packet_buffer[64]; // buffer to hold incoming packets

// Control state
extern int wifi_left_speed;
extern int wifi_right_speed;
extern unsigned long last_wifi_command_time;

// Initialize WiFi
void wifi_control_init();

// Handle WiFi connections
void wifi_control_loop();