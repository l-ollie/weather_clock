int quartRinScale = 1;
//int quartRing[9] = {1 * quartRinScale, 2 * quartRinScale, 4 * quartRinScale, 7 * quartRinScale, 11 * quartRinScale, 16 * quartRinScale, 22 * quartRinScale, 26 * quartRinScale, 30 * quartRinScale};
int quartRing[9];
byte cloudLength = 80;
float line = -cloudLength;
float line2 = cloudLength;
int ringSize;
int ringCloud [36][2];
void upperCloud(float &localLine,float cloudSpeed);

void applyCloudShade();


void setupCloudRing() {
  // create the leds for ring
  for (int i = 0; i < 9; i++ ) {
    quartRing[i] = i * i;
  }
  ringSize += quartRing[8] * 2 + cloudLength;
  // setup horizontal axis
  for (int i = 0; i < 9; i++ ) {
    ringCloud[i][0] = quartRing[8 - i];
    ringCloud[9 + i][0] = quartRing[i];
    ringCloud[18 + i][0] = (quartRing[8] * 2) - quartRing[8 - i];
    //    ringCloud[18 + i][0] = (quartRing[8] * 2+(quartRing[9]-quartRing[8])) - quartRing[8 - i];
    ringCloud[27 + i][0] = (quartRing[8] * 2) - quartRing[i];
  }

//  Serial.print(" === = = = == ============   ring size is ");
//  Serial.println(ringSize);
  //ringSize = ringSize*2;

}
bool cloud[36];
float cloudAmount[36];

void runClouds() {
  upperCloud(line,0.2);
  upperCloud(line2,0.2);
  applyCloudShade();
}

//===============================

/*cloud props 
  width
  offset
  cloudSpeed
  fadeMax
  fadingSpeed
 */

void upperCloud(float &localLine, float cloudSpeed) {
  // move the cloud width from left to right and loop
  localLine += cloudSpeed; // 0.02
  if (localLine > ringSize) {
    localLine = -cloudLength;
  }
  float cloudMaxFade = 0.05;
  float cloudFadeSpeed = 0.0004;
  byte numled5th = NUM_LEDS / 5;
  byte NumLedMinusNumled5th = NUM_LEDS - numled5th;

  for (int i = 0; i < NUM_LEDS; i++) {
    if ( i >=  numled5th &&  i <=  NumLedMinusNumled5th) { // make the cloud wave above
      if (localLine >= ringCloud[i][0] && localLine <= ringCloud[i][0] + cloudLength) {
        cloud[i] = true;
      }
    }
    if (cloud[i] == true) {  //  if cloud is true add cloud fade. 0 = darkness
      cloudAmount[i] -= cloudFadeSpeed;
      if (cloudAmount[i] <= cloudMaxFade) {
        cloud[i] = false;
        cloudAmount[i] = cloudMaxFade;
      }//  if cloud is false substract cloud fade
    } else {
      cloudAmount[i] += cloudFadeSpeed;
      if (cloudAmount[i] >= 1.00) {
        cloudAmount[i] = 1.00;
      }
    }
  }
}


void applyCloudShade() {
  float tempCloudAmountPercentage;
  int tempCloudAmount;

  for (int i = 0; i < NUM_LEDS; i++) {
    if (cloudAmount[i] != 1) {
      weatherEffect[i] *= (cloudAmount[i] * 0.9); // 1 = dark. 0 = light.
      //      if (i == 18) {
      //          Serial.print(" | cloudAmount:");
      //          Serial.print(cloudAmount[i]);
      //          Serial.print(" | weatherEffect:");
      //          Serial.println(weatherEffect[i]);
      //          previousCloudAmount = cloudAmount[i];
      //      }
    }
  }
}
