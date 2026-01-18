#include "wifi_control.h"

// Define credentials
const char* WIFI_SSID = "turtlebot";
const char* WIFI_PASSWORD = "1234";
WiFiServer server(80); // HTTP server on port 80

// Initialize Wi-Fi in Access Point mode
void wifi_control_init() {
    Serial.println("Setting up Wi-Fi AP...");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    server.begin();
    Serial.println("Wi-Fi server started");
}

// Handle incoming Wi-Fi commands
void wifi_control_loop() {
    WiFiClient client = server.available();
    if (client) {
        Serial.println("New client connected");
        String request = client.readStringUntil('\r'); // simple HTTP request line
        Serial.println(request);
        client.flush();

        // Check URL for commands
        if (request.indexOf("code=UP") != -1) Forward();
        else if (request.indexOf("code=DOWN") != -1) Backward();
        else if (request.indexOf("code=LEFT") != -1) Left();
        else if (request.indexOf("code=RIGHT") != -1) Right();
        else if (request.indexOf("code=OK") != -1) Stop();

        // Send HTTP response
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/plain");
        client.println("Connection: close");
        client.println();
        client.println("Command received");

        delay(1);
        client.stop();
        Serial.println("Client disconnected");
    }
}
