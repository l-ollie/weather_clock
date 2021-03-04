byte wifiColor[3] = {0, 100, 200};
void setLoadColor(byte tempLoadColor0, byte tempLoadColor1, byte tempLoadColor2);

// loading ring animation. add 1 led every run. input 0 - 100000
void ledConnectToWifi(int inputCount) {
  int a = inputCount;
  byte currentColor[3] = {0, 100, 200};
//  setLoadColor(0, 100, 200);
  int b = floor(a / NUM_LEDS);
  a = a - (NUM_LEDS * b);

  if ( (b % 2) != 0) {
    for (int i = 0; i < 3; i++) // set currentColor to 0,0,0
      currentColor[i] = 0;
  } else {
    for (int i = 0; i < 3; i++)  // set currentColor to wifiColor[]
      currentColor[i] = wifiColor[i];
  }
  leds[a].setRGB( currentColor[0], currentColor[1], currentColor[2]);
  FastLED.show();
}

void ShowLedRandomPixCol(byte pixCol0,byte pixCol1,byte pixCol2 ) {
//     setLoadColor(pixCol0, pixCol1, pixCol2);

//  Serial.println("doing showLedPharsing");
  for (int i = 0; i < NUM_LEDS; i++) {
    byte randNum = random(2);
    
    if (randNum == 1) {
      leds[i].setRGB( pixCol0, pixCol1, pixCol2);
    }
    else {
      leds[i].setRGB( 0, 0, 0);
    }
  }
    FastLED.show();
}

byte loadColor[3];

void turnOffLeds2() {
  byte rotations = 2;
  for (int a = 0; a < rotations; a++) {   // rotate a green spot 2 x around
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB( 0, 0, 0);
      leds[i + 1].setRGB( loadColor[0]/4, loadColor[1]/4, loadColor[2/4]);
      leds[i + 2].setRGB( loadColor[0]/2, loadColor[1]/2, loadColor[2]/2);
      leds[i + 3].setRGB( loadColor[0], loadColor[1], loadColor[2]);
      FastLED.delay(a * 2); // slowen rotation after 1 round
      FastLED.show();
    }
  }
  FastLED.clear();
  Serial.println(" Turning off leds");
}

void setLoadColor(byte tempLoadColor0, byte tempLoadColor1, byte tempLoadColor2) {
  //  for (int i = 0; i < 3; i++) {
  loadColor[0] = tempLoadColor0;
  loadColor[1] = tempLoadColor1;
  loadColor[2] = tempLoadColor2;
  //  }
}


void fadeLeds() {
  for (int i = 0; i < NUM_LEDS; i++) { // For each pixel...
    leds[i].fadeLightBy( 10 );
  }
  FastLED.show();
}

//
//for (int i = 0; i < NUM_LEDS; i++) {
//  leds[i].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);
//}
