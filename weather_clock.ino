#include "wifi.h";
#include "get_weather.h";
#include "time_manager.h";
#include "get_twilight.h";
#include "led_start.h";
#include "myTimer.h";
#include "add_twilight.h";


int timer = 0;
void setup() {
  Serial.begin(115200);

  ledSetup();

  delay(100);
  getWeatherInfo();
  //getTwilightInfo();
  setupTimeConnection();
  setupTimer();
  printWeather();
  getTempColorForLeds();
  //  getTempColorForLeds();


}

void loop() {
  t.update(); // run the timer
  ledRun();
}
