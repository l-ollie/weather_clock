#include <Event.h>
#include <Timer.h>

//#include "Timer.h"

Timer t;

void RunEveryMinute();
void getTempColorForLeds();

void setupTimer() {
  // do every 5 min
  t.every(300000, RunEveryMinute);
  //  t.every(50, sunrayRandomLED);
}

void updateTimer() {
  t.update();
}


void RunEveryMinute() {
  getWeatherInfo();
  printWeather();
  getTempColorForLeds();
  checkNtpWorks();
  Serial.print(" and Time is " );
  digitalClockDisplay();
}
