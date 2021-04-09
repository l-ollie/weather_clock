
void fillBackground();
void sunrayLed(byte power);
byte sellectBackground = 0;
byte previousSellectBackground = 0;
void printBackgroundSetting();

void backgroundStart() {
  if (previousSellectBackground != sellectBackground ) {
    printBackgroundSetting();
    previousSellectBackground = sellectBackground;
  }
  if (main_feels_like > 30.00) { // give sunray to backgound if temp is higher then 30
    sellectBackground = 1;
  }
  else if  (main_feels_like > 20.00) {
    sellectBackground = 2;// fill backgound when temp is higher then 30
  } else {
    sellectBackground = 0;
  }

  switch (sellectBackground) {
    case 1:
      sunrayLed(2); // heavy sunray
      break;
    case 2:
      sunrayLed(1); // milde sunray
      break;
    default:
      fillBackground();
      break;
  }
}

void printBackgroundSetting() {
  Serial.print("Background sellection is :  ");
  Serial.println(sellectBackground);
}


void fillBackground() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);
  }
}

bool sunray[18];
float sunrayAmount[18];

void sunrayLed(byte power) {
  //  power 1 for little sunray strength or 2 for more sunray strength
  uint8_t halfNUM_LEDS = NUM_LEDS / 2;
  //  float sunrayFadeSpeed = 0.05 * power;
  float sunrayFadeSpeed = 0.005;
  int sunrayMax = 27 * power;

  for (uint8_t i = 0; i < halfNUM_LEDS; i++) {
    if (sunray[i] == true) {  //  if sunray is true add sunray fade
      sunrayAmount[i] += sunrayFadeSpeed;

      if (sunrayAmount[i] >= 1) { // if sunray is 100% go back
        sunrayAmount[i] = 1;
        sunray[i] = false;    //  if sunray is false substract sunray fade
      }
      leds[i].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);                   // color half 1 of bg to current temp color
      leds[i + halfNUM_LEDS].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);    // color half 2 of bg to current temp color
      uint8_t TempSunrayAmount = sunrayAmount[i] * sunrayMax;                                               // calculate the sunray fade for sunray
      leds[i] += CRGB( TempSunrayAmount, TempSunrayAmount, TempSunrayAmount / 2);                       // add sunray fade to half 1
      leds[i + halfNUM_LEDS] += CRGB( TempSunrayAmount, TempSunrayAmount, TempSunrayAmount / 2);        // add sunray fade to half 2
//      runRain(i);
    }
    else { // is sunray is false substract sunray fade
      sunrayAmount[i] -= sunrayFadeSpeed;

      if (sunrayAmount[i] <= 0.0) {
        sunrayAmount[i] = 0;
        leds[i].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);                   // color half 1 of bg to current temp color
        leds[i + halfNUM_LEDS].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);    // color half 2 of bg to current temp color
      } else {
        leds[i].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);                   // color half 1 of bg to current temp color
        leds[i + halfNUM_LEDS].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);    // color half 2 of bg to current temp color
        uint8_t TempSunrayAmount = sunrayAmount[i] * sunrayMax;                                               // calculate the sunray fade for sunray
        leds[i] += CRGB( TempSunrayAmount, TempSunrayAmount, TempSunrayAmount / 2);                       // add sunray fade to half 1
        leds[i + halfNUM_LEDS] += CRGB( TempSunrayAmount, TempSunrayAmount, TempSunrayAmount / 2);        // add sunray fade to half 2
      }
//      runRain(i);
    }
  }
}


void sunrayRandomLED() {
  sunray[ random(18)] = true;
}
