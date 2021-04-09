//byte sunrise_hour;
//byte sunrise_minute;
//
//byte sunset_hour;
//byte sunset_minute;

bool nightTime = false;

byte sunSetRiseTotalMinutes = 120; // total time for night tot day transfer
byte maxBrightness = 255;
byte minBrightness = 80;

byte currentBrightness = 0;
byte brightnessSpeed = 1;

byte previousBrightness;


byte previousMinute;

void applyBrightness(byte currentBrightness ) {
  int convertedCurrentBrightness = map(currentBrightness, 0, sunSetRiseTotalMinutes, minBrightness, maxBrightness);
  FastLED.setBrightness( convertedCurrentBrightness);
  Serial.print("apply twilight brightness : ");
  Serial.print(convertedCurrentBrightness);
  Serial.print(" | ");

}



void calculateTwilight() { // this function is being runed every 60 sec
  int addLocalTime = 7200; //
  int sunset = sys_sunset + addLocalTime;
  int sunrise = sys_sunrise + addLocalTime;
  int sunTimeMarginSeconds = (sunSetRiseTotalMinutes / 2) * 60; // get half of the rise time minutes and convert into seconds
  unsigned long int currentTime = now();
  int sunsetBegin = sunset - sunTimeMarginSeconds;
  int sunsetEnd = sunset + sunTimeMarginSeconds;
  int sunriseBegin = sunrise - sunTimeMarginSeconds;
  int sunriseEnd = sunrise + sunTimeMarginSeconds;

  if (currentTime > sunriseEnd && currentTime < sunsetBegin) {  // check if its daytime
    applyBrightness(sunSetRiseTotalMinutes); // 0 is daytime
    Serial.print(" day/night mode = day ");

  } else if (currentTime > sunsetBegin && currentTime < sunsetEnd) { // if not check if its sunset time
    int b = sunSetRiseTotalMinutes - ((currentTime - sunsetBegin) / 60);
    Serial.print("sunset time | calculated brightness is ");
    Serial.print(b);
    Serial.print(" | ");
    applyBrightness(b);

    //    applyBrightness(floor((currentTime - sunsetBegin) / 60) );
  } else if (currentTime > sunsetEnd && currentTime < sunriseBegin) { // if not check if its night time
    applyBrightness(0 );
    Serial.print(" day/night mode = night ");

  } else if (currentTime > sunriseBegin && currentTime < sunriseEnd) { // if not check if its sunrise time
    applyBrightness(sunSetRiseTotalMinutes - floor((sunsetBegin - currentTime) / 60));

    int b = (sunsetBegin - currentTime) / 60;
    Serial.print("sunrise time | calculated brightness is ");
    Serial.print(b);
    Serial.print(" | ");
    applyBrightness(b);

  }
  digitalClockDisplay();
}

void runTwighlight() {
  if (minute() != previousMinute) {
    previousMinute = minute();
    //    checkForNightTime();
    //    brightnessFade();
    //    applyBrightness();
    calculateTwilight();

  }
}

//void calculateSunriseSunset() {
//  sunrise_hour = hour(sys_sunrise) + 2; // add 2 hours to the ntp
//  if (sunrise_hour > 24) {
//    sunrise_hour - 24;
//  }
//  sunrise_minute = minutes(sys_sunrise);
//
//  sunset_hour = hour(sys_sunset) + 2; // add 2 hours to the ntp
//  if (sunset_hour > 24) {
//    sunset_hour - 24;
//  }
//  sunset_minute = minutes(sys_sunset);
//}
