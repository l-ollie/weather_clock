void RunEveryMinute();
void getTempColorForLeds();
void RunEveryMinute();

void setupFrequentTimer();
void resetFrequentTimer();

unsigned long frequentTimerDuration = 300000 ; // 5 minutes
//unsigned long frequentTimerDuration = 20000 ; // 20sec
unsigned long frequentTimer;

void setupFrequentTimer() {
  frequentTimer = millis() + frequentTimerDuration;
}

void resetFrequentTimer() {
  Serial.println("==================================resetting timer now");
  setupFrequentTimer();
}

void updateTimer() {
  if (millis()  >=frequentTimer ) {
    resetFrequentTimer();
    RunEveryMinute(); 
  }
}

void RunEveryMinute() {
  getWeatherInfo();
  printWeather();
  getTempColorForLeds();
  checkNtpWorks();
  Serial.print(" and Time is " );
  digitalClockDisplay();
  //  return true; // repeat? true
  resetFrequentTimer();
}
