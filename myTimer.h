#include <Event.h>
#include <Timer.h>

#include "Timer.h"

Timer t;

void RunEveryMinute();

void setupTimer() {
  // do every 60 sec
  //    int tickEvent = t.every(60000, RunEveryMinute);
  RunEveryMinute();
 int tickEvent2 = t.every(300000, RunEveryMinute);
  //  t.every(600000, RunEveryMinute);

  int tickEvent = t.every(50, sunrayRandomLED);

}

void updateTimer() {
  t.update();
}

void RunEveryMinute() {
  getWeatherInfo();
  printWeather();
  getTempColorForLeds();
  Serial.print("Temp feels like " );
  Serial.print( main_feels_like);

  if (year() == 1970) {
    getNtpTime();
  }
  Serial.print(" and Time is " );
  digitalClockDisplay();
}
