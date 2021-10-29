#define FASTLED_ALLOW_INTERRUPTS 0 // this removes the flickering of the leds

#include <FastLED.h>
//#define NUM_LEDS 86 this is defined in the main script
#define DATA_PIN 13
CRGB leds[NUM_LEDS];

int ledLeft = NUM_LEDS / 4;
int ledRight = NUM_LEDS / 4 * 3;

byte halfNUM_LEDS = NUM_LEDS / 2;
void turnOffLeds();
void setupTemperatureDiv();
void turnOffLeds2();
//void ledRun();
void setupCloudRing(float cloudRadius);
void setLoadColor(byte tempLoadColor0, byte tempLoadColor1, byte tempLoadColor2);

void ledSetup(byte minBrightness) {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setMaxRefreshRate(400);
  FastLED.setBrightness(minBrightness);
  FastLED.setDither(BINARY_DITHER);
  setLoadColor(150, 200, 100);
  setupTemperatureDiv();
  turnOffLeds2();
  setupCloudRing(20);
}

#include "led_UI.h";
#include "led_temp.h";
#include "led_background_color.h";
#include "led_forground.h";
#include "led_clouds.h";
#include "led_rain.h";



void runTwighlight();

void ledRun() {
  //  readSerialMonitor();
  //FastLED.clear();

  backgroundStart();

  forgroundStart();

  runTwighlight();


  //leds[i].r
  //CRGB color = CRGB(leds[i].r,leds[i].g,leds[i].b);
  FastLED.show();

};

void turnOffLeds() {
  FastLED.clear();
  FastLED.show();
  Serial.println("Turning off leds1");
  delay(50);
}
