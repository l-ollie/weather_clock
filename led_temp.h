byte tempColorSteps[7][3] = {
  {0, 0, 255},    // 0 - dark blue -6 - 0
  {255, 255, 255},  // 1 - white    0 - 6
  {0, 255, 255},  // 2 - light blue 6 - 12
  {0, 255, 0},    // 3 - green      12 - 18
  {255, 255, 0},  // 4 - yellow     18 - 24
  {255, 129, 0},    // 5 - orange   24 - 30
  {200, 0, 0},    // 6 - red        30
};

byte temperatureStep = 6;
int temperatureDiv[7];
int currentTempColor[3];

void setupTemperatureDiv();
void getTempColorForLeds();
void calculateTempColor(int pCurrentTempColor[]);
float returnProcentage(int a);
void  turnOffLeds2();

void setupTemperatureDiv() {
  for (int i = 0; i < 7; i++) {
    temperatureDiv[i] =  -temperatureStep + (temperatureStep * i);
  }
}

void getTempColorForLeds() {
  turnOffLeds2();
  calculateTempColor(currentTempColor);
  Serial.print("the current calculated temp color is : ");
  for (int i = 0; i < 3; i++) {
    Serial.print(currentTempColor[i]);
    Serial.print(", ");
  }
  Serial.println("");
}

void printCurrentTempColor() {
  for (int i = 0; i < NUM_LEDS; i++) { // For each pixel...
    leds[i].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);
  }
  FastLED.show();
}


void calculateTempColor(int pCurrentTempColor[]) {
  for (int i = 0; i < 6; i++) {                                                                             // check for 6 tempDiv
    if (main_feels_like >= (float)temperatureDiv[i] && main_feels_like <= (float)temperatureDiv[i + 1]) {   // check if temp is in range of this div
      float procentage = returnProcentage(i);
      Serial.print("calculated % within this temp div is : ");
      Serial.println(procentage);
      for (int b = 0; b < 3; b++) {
        pCurrentTempColor[b] = round(tempColorSteps[i][b] * ((float)1 - procentage) + (tempColorSteps[i + 1][b] * procentage)) ;
      }
      return;
    }
  }
  // if temp is not between -6 and 30
  if (main_feels_like > (float)temperatureDiv[6]) { // if its > 30 pick warm color
    for (int b = 0; b < 3; b++)
      pCurrentTempColor[b] = tempColorSteps[6][b] ;
  }
  else if (main_feels_like < (float)temperatureDiv[0]) { // if its colder then -6 pick cold color
    for (int b = 0; b < 3; b++)
      pCurrentTempColor[b] = tempColorSteps[0][b] ;
  }
}

float returnProcentage(int a) {
  float bTemp = main_feels_like + temperatureStep;
  bTemp = bTemp - (temperatureStep * a);
  return bTemp / 6;
}
