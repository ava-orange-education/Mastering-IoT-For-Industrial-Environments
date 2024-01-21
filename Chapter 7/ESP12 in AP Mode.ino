#include <ESP8266WiFi.h>

const char *apSSID = "NodeMCU_AP";
const char *apPassword = "password123";

void setup() {
    Serial.begin(115200);

    // Set up NodeMCU as an Access Point
    WiFi.softAP(apSSID, apPassword);

    // Obtain and print the Access Point's IP address
    IPAddress apIP = WiFi.softAPIP();
    Serial.print("Access Point IP address: ");
    Serial.println(apIP);
}

void loop() {
    // Check if there are clients connected to the Access Point
    if (WiFi.softAPgetStationNum() > 0) {
        Serial.println("Client connected to Access Point!");
    }

    // Your loop code
}
