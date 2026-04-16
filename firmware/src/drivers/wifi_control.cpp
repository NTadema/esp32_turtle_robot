#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "drivers/wifi_control.h"
#include "drivers/motors.h"

// Define credentials
const char* WIFI_SSID = "turtlebot";
const char* WIFI_PASSWORD = "1234";

WiFiUDP udp;
const int UDP_PORT = 4210;

char packetBuffer[64]; // buffer to hold incoming packets

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

void wifi_control_loop() {
    int packetSize = udp.parsePacket();

    if (packetSize) {
        int len = udp.read(packetBuffer, sizeof(packetBuffer) - 1);
        if (len > 0) packetBuffer[len] = 0;

        // Parse speeds from "left,right"
        int leftSpeed = 0;
        int rightSpeed = 0;
        if (sscanf(packetBuffer, "%d,%d", &leftSpeed, &rightSpeed) == 2) {
            set_motors_speed(leftSpeed, rightSpeed);
            last_command_time = millis();
            Serial.print("UDP speeds: L=");
            Serial.print(leftSpeed);
            Serial.print(" R=");
            Serial.println(rightSpeed);
        }
    }
}