#include <Event.h>
#include <Timer.h>

#include "Timer.h"

Timer t;

void RunEveryMinute();

void setupTimer() {
  // do every 60 sec
  //    int tickEvent = t.every(60000, RunEveryMinute);

  t.every(600000, RunEveryMinute);
  t.every(50, randomLED);

}

void updateTimer() {
  t.update();
}

void RunEveryMinute() {
  getWeatherInfo();
  showTempOnLeds();
  Serial.print("Temp feels like " );
  Serial.print( main_feels_like);
  Serial.print(" and Time is " );

if(year()==1970){
  getNtpTime();
}

  digitalClockDisplay();
}
