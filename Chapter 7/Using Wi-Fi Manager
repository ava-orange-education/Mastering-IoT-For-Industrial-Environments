#include <WiFiManager.h>

WiFiManager wifiManager;

void setup() {
  Serial.begin(115200);
  wifiManager.setHostname("MyESPDevice");

  if (!wifiManager.autoConnect("MyESPDevice-AP")) {
    Serial.println("Failed to connect to WiFi or configure.");
    // Add code to handle the failure, e.g., deep sleep or error recovery.
  }

  // WiFiManager handles connection and saves credentials, no need to code it.
}

void loop() {
  // Your application logic here.
}
