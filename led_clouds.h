int quartRinScale = 1;
//int quartRing[9] = {1 * quartRinScale, 2 * quartRinScale, 4 * quartRinScale, 7 * quartRinScale, 11 * quartRinScale, 16 * quartRinScale, 22 * quartRinScale, 26 * quartRinScale, 30 * quartRinScale};
int quartRing[9];
byte lineSize = 80;
float line = -lineSize;
float line2 = lineSize;
int ringSize;
int ringCloud [36][2];
void lowerCloud();
void lowerCloud2();
void applyCloudShade();


void setupCloudRing() {
  // create the leds for ring
  for (int i = 0; i < 9; i++ ) {
    quartRing[i] = i * i;
  }

    ringSize += quartRing[8]*2+lineSize;
  
  // setup horizontal axis
  for (int i = 0; i < 9; i++ ) {
    ringCloud[i][0] = quartRing[8 - i];
    ringCloud[9 + i][0] = quartRing[i];
    ringCloud[18 + i][0] = (quartRing[8] * 2) - quartRing[8 - i];
    //    ringCloud[18 + i][0] = (quartRing[8] * 2+(quartRing[9]-quartRing[8])) - quartRing[8 - i];

    ringCloud[27 + i][0] = (quartRing[8] * 2) - quartRing[i];
  }



  Serial.print(" === = = = == ============   ring size is ");
  Serial.println(ringSize);
  //ringSize = ringSize*2;

}
bool cloud[36];
float cloudAmount[36];

void runClouds() {

  //  for (int i = 0; i < NUM_LEDS; i++) {
  //    //    if ( i <=  (NUM_LEDS / 4) ||  i >=  NUM_LEDS - (NUM_LEDS / 4)) {
  //    if ( i >=  (NUM_LEDS / 5) &&  i <=  NUM_LEDS - (NUM_LEDS / 5)) { // make the cloud above
  //      if (line >= ringCloud[i][0] && line <= ringCloud[i][0] + 25) {
  //        cloud[i] = true;
  //      }
  //    }
  //  }

  lowerCloud();
  lowerCloud2();
  applyCloudShade();
}

void lowerCloud() {
  // speed of cloud
  line += 0.02;
  if (line > ringSize) {
    line = -lineSize;
  }
  
  float cloudFadeSpeed = 0.0004;
  for (int i = 0; i < NUM_LEDS; i++) {
    if ( i >=  (NUM_LEDS / 5) &&  i <=  NUM_LEDS - (NUM_LEDS / 5)) { // make the cloud wave above
      if (line >= ringCloud[i][0] && line <= ringCloud[i][0] + lineSize) {
        cloud[i] = true;
      }
    }
    if (cloud[i] == true) {  //  if cloud is true add cloud fade
      cloudAmount[i] += cloudFadeSpeed;
      if (cloudAmount[i] >= 1) {
        cloud[i] = false;
        cloudAmount[i] = 1;
      }//  if cloud is false substract cloud fade
    } else {
      cloudAmount[i] -= cloudFadeSpeed;
      if (cloudAmount[i] < 0.1) {
        cloudAmount[i] = 0;
      }
    }
  }
}


void lowerCloud2() {
    // speed of cloud
  line2 += 0.020;
  if (line2 > ringSize) {
    line2 = -lineSize;
  }
  
  float cloudFadeSpeed = 0.0004;
  for (int i = 0; i < NUM_LEDS; i++) {
    if ( i >=  (NUM_LEDS / 5) &&  i <=  NUM_LEDS - (NUM_LEDS / 5)) { // make the cloud wave above
      if (line2 >= ringCloud[i][0] && line2 <= ringCloud[i][0] + lineSize) {
        cloud[i] = true;
      }
    }
    if (cloud[i] == true) {  //  if cloud is true add cloud fade
      cloudAmount[i] += cloudFadeSpeed;
      if (cloudAmount[i] >= 1) {
        cloud[i] = false;
        cloudAmount[i] = 1;
      }//  if cloud is false substract cloud fade
    } else {
      cloudAmount[i] -= cloudFadeSpeed;
      if (cloudAmount[i] < 0.1) {
        cloudAmount[i] = 0;
      }
    }
  }
}



void applyCloudShade() {

  int tempCloudAmount;
  for (int i = 0; i < NUM_LEDS; i++) {

    //    tempCloudAmount = floor(tempCloudAmount);
    if (cloudAmount[i] < 1) {
      tempCloudAmount = 230 * cloudAmount[i];
    } else {
      tempCloudAmount = 230;
    }


    if (tempCloudAmount != 0) {
      //      leds[i].setRGB( currentTempColor[0], currentTempColor[1], currentTempColor[2]);

      leds[i].fadeToBlackBy( tempCloudAmount );
    }
    //        leds[i].fadeToBlackBy( 255  );
  }
}
