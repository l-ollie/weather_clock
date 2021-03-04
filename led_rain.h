bool rainDrop[36];
float rainDropAmount[36];

void  runRain(int i) {
  int halfNUM_LEDS = NUM_LEDS / 2;
//  for (int i = 0; i < halfNUM_LEDS; i++) {
    if (i < NUM_LEDS / 2) {
//      leds[i].setRGB( 0, 0, 0);
            leds[i] = CRGB( 0, 0, 0 );                       // add sunray fade to half 1

//    }
  }
}
