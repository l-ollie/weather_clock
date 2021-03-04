#define FASTLED_ALLOW_INTERRUPTS 0 // this removes the flickering of the leds

#include <FastLED.h>
#define NUM_LEDS 36
#define DATA_PIN 13
CRGB leds[NUM_LEDS];

void turnOffLeds();
void setupTemperatureDiv();
void turnOffLeds2();
//void ledRun();
void setupCloudRing();
void setLoadColor(byte tempLoadColor0, byte tempLoadColor1, byte tempLoadColor2);

void ledSetup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setMaxRefreshRate(400);
  setLoadColor(150, 200, 100);
  setupTemperatureDiv();
  FastLED.setBrightness(50);
  turnOffLeds2();
  setupCloudRing();
}

#include "led_UI.h";
#include "led_temp.h";
#include "led_background_color.h";
#include "led_forground.h";
#include "led_clouds.h";
#include "led_rain.h";

void runTwighlight();

void ledRun() {
  //        delay(20);
  readSerialMonitor();
  //FastLED.clear();
  backgroundStart();

  forgroundStart();
runTwighlight();
  //int ledi = 30;
  //Serial.print("led[30] R:");
  //Serial.print(leds[ledi].r);
  //Serial.print(", G:");
  //Serial.print(leds[ledi].g);
  //Serial.print(", B:");
  //Serial.println(leds[ledi].b);

  //leds[i].r
  //CRGB color = CRGB(leds[i].r,leds[i].g,leds[i].b);


  FastLED.show();
  //    FastLED.delay(5);

  //  FastLED.delay(2);
};

void turnOffLeds() {
  FastLED.clear();
  FastLED.show();
  Serial.println(" Turning off leds");
  delay(500);
}
