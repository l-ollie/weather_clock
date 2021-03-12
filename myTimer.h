#include <Event.h>
#include <Timer.h>

#include "Timer.h"

Timer t;

void RunEveryMinute();

void setupTimer() {
  // do every 60 sec
  // int tickEvent = t.every(60000, RunEveryMinute);
  // int tickEvent2 = t.every(300000, RunEveryMinute);
  t.every(300000, RunEveryMinute);

  //  int tickEvent = t.every(50, sunrayRandomLED);

  t.every(50, sunrayRandomLED);

}

void updateTimer() {
  t.update();
}


void RunEveryMinute() {
  getWeatherInfo();
  printWeather();
  getTempColorForLeds();

  printWeather();
  checkNtpWorks();

  Serial.print(" and Time is " );
  digitalClockDisplay();
}
