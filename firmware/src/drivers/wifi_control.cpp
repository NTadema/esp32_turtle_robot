#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "drivers/wifi_control.h"
#include "drivers/motors.h"

// Define credentials
const char* WIFI_SSID = "turtlebot";
const char* WIFI_PASSWORD = "1234";

// Wi-Fi UDP server
WiFiUDP udp;
const int UDP_PORT = 4210;
char packet_buffer[64]; // buffer to hold incoming packets

// Variables for storing speeds from WiFi control
int wifi_left_speed = 0;
int wifi_right_speed = 0;
unsigned long last_wifi_command_time = 0;

// Initialize Wi-Fi in Access Point mode
void wifi_control_init() {
    Serial.println("Setting up Wi-Fi AP...");

    WiFi.mode(WIFI_AP);
    WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    udp.begin(UDP_PORT);
    Serial.println("UDP server started on port " + String(UDP_PORT));
}
// Handle incoming Wi-Fi UDP packets to control motor speeds
void wifi_control_loop() {
    int packet_size = udp.parsePacket();

    // If a packet is received, read it and parse the speeds
    if (packet_size) {
        int len = udp.read(packet_buffer, sizeof(packet_buffer) - 1);
        if (len > 0) packet_buffer[len] = 0;

        // Parse speeds from "left,right"
        if (sscanf(packet_buffer, "%d,%d", &wifi_left_speed, &wifi_right_speed) == 2) {
            last_wifi_command_time = millis();
            Serial.print("UDP speeds: L=");
            Serial.print(wifi_left_speed);
            Serial.print(" R=");
            Serial.println(wifi_right_speed);
        }
    }
}