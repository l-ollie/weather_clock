#include <FastLED.h>
#define NUM_LEDS 36
#define DATA_PIN 12
CRGB leds[NUM_LEDS];


byte tempColorSteps[7][3] = {
  {0, 0, 255},    // 0 - dark blue -6 - 0
  {255, 255, 255},  // 1 - white    0 - 6
  {0, 255, 255},  // 2 - light blue 6 - 12
  {0, 255, 0},    // 3 - green      12 - 18
  {255, 255, 0},  // 4 - yellow     18 - 24
  {255, 129, 0},    // 5 - orange   24 - 30
  {255, 0, 0},    // 6 - red        30
};

byte temperatureStep = 6;
int temperatureDiv[7];
int currentTempColor[3];

void setupTemperatureDiv();
void showTempOnLeds();
void calculateTempColor(int pCurrentTempColor[]);
float returnProcentage(int a);
void turnOffLeds();

void ledSetup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  turnOffLeds();
  setupTemperatureDiv();
  FastLED.setBrightness(255);
}

void setupTemperatureDiv() {
  for (int i = 0; i < 7; i++) {
    temperatureDiv[i] =  -temperatureStep + (temperatureStep * i);
  }
}

void showTempOnLeds() {
  turnOffLeds();
  calculateTempColor(currentTempColor);
  Serial.print("the current color is : ");
  for (int i = 0; i < 3; i++) {
    Serial.print(currentTempColor[i]);
    Serial.print(", ");
  }
  Serial.println("");
  Serial.print(" ========== led is ");
  Serial.print(leds[2]);
  for (int i = 0; i < NUM_LEDS; i++) { // For each pixel...
    leds[i].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);
  }
  delay(50);
  FastLED.show();
  Serial.println(" showing leds");
}

void calculateTempColor(int pCurrentTempColor[]) {
  for (int i = 0; i < 6; i++) {
    if (main_feels_like >= (float)temperatureDiv[i] && main_feels_like <= (float)temperatureDiv[i + 1]) {
      float procentage = returnProcentage(i);
      Serial.print("Color match !!!!!!!");
      for (int b = 0; b < 3; b++) {
        pCurrentTempColor[b] = round(tempColorSteps[i][b] * ((float)1 - procentage) + (tempColorSteps[i + 1][b] * procentage)) ;
      }
      return;
    }
  }
  // if temp is not between -6 and 30
  if (main_feels_like > (float)temperatureDiv[6]) { // if its > 30 pick warm color
    for (int b = 0; b < 3; b++) {
      pCurrentTempColor[b] = tempColorSteps[6][b] ;
    }
    Serial.println("Color match hot ");

  }  else if (main_feels_like < (float)temperatureDiv[0]) { // if its colder then -6 pick cold color
    for (int b = 0; b < 3; b++) {
      pCurrentTempColor[b] = tempColorSteps[0][b] ;
    }
    Serial.print("Color match cold ");
  }
}

float returnProcentage(int a) {
  float bTemp = main_feels_like + temperatureStep;
  bTemp = bTemp - (temperatureStep * a);
  return bTemp / 6;
}

void turnOffLeds() {
  FastLED.clear();
  FastLED.show();
  Serial.println(" Turning off leds");
  delay(500);
}

void fadeLeds() {
  for (int i = 0; i < NUM_LEDS; i++) { // For each pixel...
    leds[i].fadeLightBy( 10 );
  }
  FastLED.show();
}

bool twinkel[36];
float twinkelAmount[36];

void twinkelLed() {
  float twinkelSpeed = 0.1;
  int twinkelMax = 20;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (twinkel[i] == true) {
      twinkelAmount[i] += twinkelSpeed;

      if (twinkelAmount[i] > 1) {
        twinkel[i] = false;
      }

      leds[i].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);
      int TemptwinkelAmount = twinkelAmount[i] * twinkelMax;
      leds[i].addToRGB( TemptwinkelAmount );
    }
    else {
      twinkelAmount[i] -= twinkelSpeed;

      if (twinkelAmount[i] < 0.0) {
        twinkelAmount[i] = 0;
      }
      leds[i].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);
      int TemptwinkelAmount = twinkelAmount[i] * twinkelMax;
      leds[i].addToRGB(TemptwinkelAmount);
    }
    FastLED.show();
  }
}

void randomLED() {
  twinkel[ random(36)] = true;
}
