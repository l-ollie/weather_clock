#include "wifi.h";
#include "connect_to_weather_api.h";
#include "time_manager.h";
#include "get_twilight.h";


int timer = 0;
void setup() {

  Serial.begin(115200);
  delay(100);
  getWeatherInfo();
  getTwilightInfo();
  setupTimeConnection();
}

void loop() {
  timer++;
  //  time_t sunRise =  sys_sunrise + 2;
  //  time_t sunSet =  sys_sunset + 2;


  Serial.print("Temp feels like " );
  Serial.print( main_feels_like);
  Serial.print("C | Sunrise at ");
  Serial.print(hour(utcToLocalTime(sys_sunrise)));
  Serial.print(":");
  Serial.print(minute(utcToLocalTime(sys_sunrise)));
  Serial.print(" | Sunset at ");
  Serial.print(hour(utcToLocalTime(sys_sunset)));
  Serial.print(":");
  Serial.print(minute(utcToLocalTime(sys_sunset)));
  Serial.print(" | Time & date ");

  digitalClockDisplay();

  delay(10000);
  if (timer >= 4) {
    timer = 0;
    getWeatherInfo();
  }
}
