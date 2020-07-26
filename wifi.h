#include <ESP8266WiFi.h>

const char* ssid     = "VGV7519632769";
const char* password = "ukPf3dU6Kd9P";

bool connectToWifi() {
  Serial.println("Connecting to WiFi network");
  // Check if already conneted to a WiFi network
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Already conneted to WiFi network");
    return true;
  } 

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  return true;
}
