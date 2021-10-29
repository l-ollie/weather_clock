byte wifiColor[3] = {0, 100, 200};
void setLoadColor(byte tempLoadColor0, byte tempLoadColor1, byte tempLoadColor2);

// loading ring animation. add 1 led every run. input 0 - 100000
void ledConnectToWifi(int inputCount) {
  byte steps = 2;
  int a = inputCount * steps;
  byte currentColor[3] = {0, 100, 200};
  int b = floor(a / NUM_LEDS);
  a = a - (NUM_LEDS * b);

  if ( (b % 2) != 0) {
    for (int d = 0; d < steps; d++) {
      leds[a + d].setRGB( 0, 0, 0);
    }
  } else {
    for (int d = 0; d < steps; d++) {
      leds[a + d].setRGB( currentColor[0], currentColor[1], currentColor[2]);
    }
  }
  FastLED.show();
}

void ShowLedRandomPixCol(byte pixCol0, byte pixCol1, byte pixCol2 ) {
  //     setLoadColor(pixCol0, pixCol1, pixCol2);

  //  Serial.println("doing showLedPharsing");
  for (int i = 0; i < NUM_LEDS; i += 2) {
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
  byte rotationSpeed = 3;
  for (int a = 0; a < rotations; a++) {   // rotate a green spot 2 x around
    for (int i = 0; i < NUM_LEDS; i += 3) {
      for (int c = 0; c < rotationSpeed; c++) {
        //        float q = ((rotationSpeed*2)-c)/(rotationSpeed*2);
        float q = 1;

        leds[i + c].setRGB( loadColor[0] *q, loadColor[1] *q, loadColor[2]*q);
      }
      FastLED.show();
      FastLED.delay(a * 2); // slowen rotation after 1 round
      FastLED.clear();
    }
  }
  FastLED.clear();
  Serial.println("Turning off leds2");
}

void setLoadColor(byte tempLoadColor0, byte tempLoadColor1, byte tempLoadColor2) {
  //  for (int i = 0; i < 3; i++) {
  loadColor[0] = tempLoadColor0;
  loadColor[1] = tempLoadColor1;
  loadColor[2] = tempLoadColor2;
  //  }
}

void showTimeIcon() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < NUM_LEDS / 4) {
      leds[i].setRGB( 0, 0, 0);
    } else {
      leds[i].setRGB(255, 20, 20);
    }
  }
  FastLED.show();
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
