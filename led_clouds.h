int quartRinScale = 1;
int quartRing[9] = {1 * quartRinScale, 2 * quartRinScale, 4 * quartRinScale, 7 * quartRinScale, 11 * quartRinScale, 16 * quartRinScale, 22 * quartRinScale, 29 * quartRinScale, 37 * quartRinScale};
float line = -40;
int ringCloud [36][2];

void setupCloudRing() {
  // setup horizontal axis
  for (int i = 0; i < 9; i++ ) {
    ringCloud[i][0] = quartRing[8 - i];
    ringCloud[9 + i][0] = quartRing[i];
    ringCloud[18 + i][0] = 83 - quartRing[8 - i];
    ringCloud[27 + i][0] = 83 - quartRing[i];
  }
}
bool cloud[36];
float cloudAmount[36];

void runClouds() {
  float cloudFadeSpeed = 0.05;


  for (int i = 0; i < NUM_LEDS; i++) {
    if ( i >=  (NUM_LEDS / 5) &&  i <=  NUM_LEDS - (NUM_LEDS / 5)) { // make the cloud wave above
      if (line >= ringCloud[i][0] && line <= ringCloud[i][0] + 25) {
        cloud[i] = true;
      }
    }
    if (cloud[i] == true) {  //  if cloud is true add cloud fade
      cloudAmount[i] += cloudFadeSpeed;
      if (cloudAmount[i] >= 1) {
        if (cloudAmount[i] >= 2) {
          cloud[i] = false;
        }
      }//  if cloud is false substract cloud fade
    } else {
      cloudAmount[i] -= cloudFadeSpeed;
      if (cloudAmount[i] < 0.1) {
        cloudAmount[i] = 0;
      }
    }

    int tempCloudAmount;
    if (cloudAmount[i] < 1) {
      tempCloudAmount = 255 * cloudAmount[i];
    } else {
      tempCloudAmount = 255;
    }

    tempCloudAmount = floor(tempCloudAmount);

    if (tempCloudAmount != 0) {
      //      leds[i].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);
      if (cloudAmount[i] < 1) {
        leds[i].setRGB( 0, 0, 0);
      } 
      else {
        leds[i].fadeToBlackBy( tempCloudAmount );
      }
      //        leds[i].fadeToBlackBy( 255  );
    }
  }


  line += 0.2;
  if (line > 150) {
    line = -25;
  }
  //  for (int i = 0; i < NUM_LEDS; i++) {
  //    //    if ( i <=  (NUM_LEDS / 4) ||  i >=  NUM_LEDS - (NUM_LEDS / 4)) {
  //    if ( i >=  (NUM_LEDS / 5) &&  i <=  NUM_LEDS - (NUM_LEDS / 5)) { // make the cloud above
  //      if (line >= ringCloud[i][0] && line <= ringCloud[i][0] + 25) {
  //        cloud[i] = true;
  //      }
  //    }
  //  }
}
