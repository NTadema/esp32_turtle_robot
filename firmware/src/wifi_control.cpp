#include "wifi_control.h"

// Define credentials
const char* WIFI_SSID = "turtlebot";
const char* WIFI_PASSWORD = "1234";

WiFiUDP udp;
const int UDP_PORT = 4210;

char packetBuffer[255]; // buffer to hold incoming packets

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

// Handle incoming Wi-Fi commands
void wifi_control_loop() {
    int packetSize = udp.parsePacket();
    if (packetSize) {
        // Read the incoming packet
        int len = udp.read(packetBuffer, 255);
        if (len > 0) packetBuffer[len] = '\0'; // Null-terminate the string

        String cmd = String(packetBuffer);

        if(cmd == "UP") Forward();
        else if(cmd == "DOWN") Backward();
        else if(cmd == "LEFT") Left();
        else if(cmd == "RIGHT") Right();
        else if(cmd == "STOP") Stop();

        last_command_time = millis(); // Update last command time
        Serial.println("Received command: " + cmd);
    }
}
