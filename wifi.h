#include <ESP8266WiFi.h>

const char* ssid     = "H369AEA6A4F-2.4GHz";
const char* password = "7EF267E3CC5D";
void ledConnectToWifi(int inputCount); // function is in led_UI.h
void turnOffLeds2();

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
  int loadingAmout = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    ledConnectToWifi(loadingAmout);
    loadingAmout++;
    if(loadingAmout>72){
        return false;
    }
    Serial.println(WiFi.status());
  }
  Serial.println("");
  turnOffLeds2();
  return true;
}
