#include <esp_now.h>
#include <WiFi.h>

// Define the MAC address of the receiver ESP8266/ESP32 module
uint8_t receiverMACAddress[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC}; // Replace with your receiver's MAC address

// Structure to hold the data to be sent
typedef struct struct_message {
  int sensorValue;
  // Add other data you want to send here
} struct_message;

// Create a variable of the struct_message type
struct_message message;

// Callback function that will be executed when data is sent
void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
  Serial.print("Packet to: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(mac_addr[i], HEX);
    if (i < 5) Serial.print(':');
  }
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? " Sent" : " Failed");
}

void setup() {
  Serial.begin(115200);
  
  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverMACAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false; // Set to true if encryption is needed

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  // Set callback for sending data
  esp_now_register_send_cb(OnDataSent);
}

void loop() {
  // Simulated sensor value, replace this with your sensor reading
  int sensorValue = random(0, 1024);

  // Update the message structure with sensor data
  message.sensorValue = sensorValue;

  // Send the message using ESP-NOW
  esp_err_t result = esp_now_send(receiverMACAddress, (uint8_t *) &message, sizeof(message));
  if (result != ESP_OK) {
    Serial.println("Error sending the data");
  }

  delay(1000); // Change the delay according to your requirements
}
