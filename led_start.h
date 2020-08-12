
#include <FastLED.h>
#define NUM_LEDS 36
#define DATA_PIN 12
CRGB leds[NUM_LEDS];

void turnOffLeds();
void setupTemperatureDiv();
void turnOffLeds2();
void ledRun();
void setupCloudRing();

void ledSetup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  setupTemperatureDiv();
  FastLED.setBrightness(255);
  turnOffLeds2();
  setupCloudRing();
}

#include "led_temp.h";
#include "led_background_color.h";
#include "led_UI.h";
#include "led_forground.h";
#include "led_clouds.h";
#include "led_rain.h";



void ledRun() {
  backgroundStart();
  forgroundStart();
  FastLED.delay(2);
  FastLED.show();
  FastLED.delay(2);
};

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
