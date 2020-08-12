#include "wifi.h";
#include "connect_to_weather_api.h";
#include "time_manager.h";
#include "get_twilight.h";
#include "led_start.h";
#include "myTimer.h";


int timer = 0;
void setup() {
  ledSetup();


  Serial.begin(115200);
  delay(100);
//  getWeatherInfo();
  getTwilightInfo();
  setupTimeConnection();
  setupTimer();
  getTempColorForLeds();

}

void loop() {

  t.update(); // run the timer
  ledRun();
//  Serial.print("Temp feels like " );
//  Serial.print( main_feels_like);
  //  Serial.print("C | Sunrise at ");
  //  Serial.print(hour(utcToLocalTime(sys_sunrise)));
  //  Serial.print(":");
  //  Serial.print(minute(utcToLocalTime(sys_sunrise)));
  //  Serial.print(" | Sunset at ");
  //  Serial.print(hour(utcToLocalTime(sys_sunset)));
  //  Serial.print(":");
  //  Serial.print(minute(utcToLocalTime(sys_sunset)));
  //  Serial.print(" | Time & date ");


}
