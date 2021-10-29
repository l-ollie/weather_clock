int temp;

// this is for the serialRead_multi_var
float serialFloat[7];
int serialInt[7];
int previousMaxNumbCloud = 0;
#define NUM_LEDS 86

#include "wifi.h";
#include "get_weather.h";
#include "get_time.h";
#include "get_twilight.h";
#include "led_start.h";
#include "myOwnTimer.h";
#include "add_twilight.h";

#include "serialRead_multi_var.h";


//int timer = 0;
void setup() {

  Serial.begin(115200);
  weatherSetup();
  ledSetup(minBrightness);
  getWeatherInfo();
  //getTwilightInfo();
  calculateTwilight();
  setupTimeConnection();
  setupFrequentTimer();
  printWeather();
  getTempColorForLeds();

}



void loop() {
  updateTimer();
  ledRun();
  readSerialMonitor();

}
