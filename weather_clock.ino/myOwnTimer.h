void RunFrequentTimerTask();
void getTempColorForLeds();
void RunFrequentTimerTask();

//void setupFrequentTimer();
//void resetFrequentTimer();

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
  if (millis() >= frequentTimer ) {
    RunFrequentTimerTask();
  }
  if (millis() >= 100) { // if millis has been reset to 0, reset until 100 millis has been reached
    resetFrequentTimer();
}

void RunFrequentTimerTask() {
  getWeatherInfo();
  printWeather();
  getTempColorForLeds();
  checkNtpWorks();
  Serial.print(" and Time is " );
  digitalClockDisplay();
  resetFrequentTimer();
}


//bool toggle_led(void *) {
//  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // toggle the LED
//  return true; // repeat? true
//}
