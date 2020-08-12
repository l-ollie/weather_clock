byte wifiColor[3] = {0, 100, 200};

// loading ring animation. add 1 led every run. input 0 - 100000
void ledConnectToWifi(int inputCount) {
  int a = inputCount;
  byte currentColor[3] = {0, 100, 200};
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


void ShowLedPharsingJson() {
  byte currentColor[3] = {0, 200, 0};

//  Serial.println("doing showLedPharsing");
  for (int i = 0; i < NUM_LEDS; i++) {
    byte randNum = random(2);
    
    if (randNum == 1) {
      leds[i].setRGB( currentColor[0], currentColor[1], currentColor[2]);
    }
    else {
      leds[i].setRGB( 0, 0, 0);
    }
  }
    FastLED.show();
}

void turnOffLeds2() {
  byte rotations = 2;
  for (int a = 0; a < rotations; a++) {   // rotate a green spot 2 x around
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB( 0, 0, 0);
      leds[i + 1].setRGB( 0, 70, 0);
      leds[i + 2].setRGB( 0, 127, 0);
      leds[i + 3].setRGB( 0, 255, 0);
      FastLED.delay(a * 2); // slowen rotation after 1 round
      FastLED.show();
    }
  }
  FastLED.clear();
  Serial.println(" Turning off leds");
}


//
//for (int i = 0; i < NUM_LEDS; i++) {
//  leds[i].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);
//}
