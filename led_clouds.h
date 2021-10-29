// wind speed overview
//http://www.kuijntjes.nl/weer/windsnelheid.htm

float cloudPos[30][2];
float ringCloudLedPos[NUM_LEDS][2];
//int previousMaxNumbCloud = 0;
int counter;
void applyCloudFadeToWeatherEffect();

void setupCloudRing(float cloudRadius) {

  float theta, increment, x, y;
  float radius =  10;
  increment = 2 * PI / NUM_LEDS;
  //  theta = -increment * (NUM_LEDS / 4); // off set start of radius
  theta = -2 * PI / 4; // off set start of radius

  for (byte i = 0; i < NUM_LEDS; i++) {
    ringCloudLedPos[i][0] =  radius * cos(theta) + radius;
    ringCloudLedPos[i][1] = radius * sin(theta);
    Serial.print(i);
    Serial.print(" | x = ");
    Serial.print(ringCloudLedPos[i][0], 4);
    Serial.print(", Y = ");
    Serial.println(ringCloudLedPos[i][1], 4);
    theta -= increment;
  }
}
float cloudAmount[NUM_LEDS];

void runCloud(int maxNumbCloud, float cloudSpeed, float cloudRadius, float cloudHeightMultiplier, float fadeEdge, float maxFade, float yPos, float yOffset);

void cloudsExperiment() {
  //  Serial.println("doing experiment cloud");
  counter++;
  if (counter > 100) {
    counter = 0;
  }
  //  665,1,0.02,10,0.5,0.3,0.4,10,
  // 665,2,0.01,18,0.6,0.6,0,15,
  //  665,3,0.01,10,0.99,0.3,0.0,15,
  //  665,3,0.01,10,1,0.3,0.0,0,15,

  //    25% - 50% clouds
  //    665,3,0.001,10,1,0.3,0.0,0,15,
  //    50% - 81%
  //    665,4,0.001,10,1,0.3,0.0,2,10,
  //    665,4,-0.04,10,1,0.4,0.0,2,10,
  int maxNumbCloud = serialInt[0];
  float cloudSpeed = serialFloat[1];
  float cloudRadius = serialFloat[2];

  float heightMultiplier =  serialFloat[3];
  float fadeEdge = serialFloat[4];
  float maxFade = serialFloat[5];

  float yPos = serialFloat[6];
  float yOffset = serialFloat[7];

  runCloud(maxNumbCloud, cloudSpeed, cloudRadius, heightMultiplier, fadeEdge, maxFade, yPos, yOffset); // radius, heightMultiplier, fadeEdge, maxFade
  applyCloudFadeToWeatherEffect();
}

//===============================

void setCloudBeginPos(int maxNumbCloud, int cloudRadius, float cloudHeightMultiplier, float yPos, float yOffset);

void checkResetCloudBeginPos( int maxNumbCloud, int cloudRadius, float cloudHeightMultiplier, float yPos, float yOffset) {
  if (previousMaxNumbCloud != maxNumbCloud) {
    previousMaxNumbCloud = maxNumbCloud;
    Serial.print(" new previousMaxNumbCloud= ");
    Serial.println(previousMaxNumbCloud);
    setCloudBeginPos(maxNumbCloud, cloudRadius, cloudHeightMultiplier, yPos, yOffset);
  }
}

bool positiveYOffset;
float generateYOffset(float yPos, float yOffset) {
  float tempYPos = (yOffset * 0.5) + (random(yOffset * 0.5 * 100) / 100.0);
  if (positiveYOffset) {
    positiveYOffset = false;
  } else {
    positiveYOffset = true;
    tempYPos = -tempYPos;
  }
  Serial.print(" new yPos="); Serial.println(yPos + tempYPos);

  return yPos + tempYPos;
}


void setCloudBeginPos( int maxNumbCloud, int cloudRadius, float cloudHeightMultiplier, float yPos, float yOffset) {
  Serial.print("setting cloud begin | total width: ");
  Serial.print(ringCloudLedPos[ledRight][0] + (cloudRadius * 1));
  Serial.print(", ringCloudLedPos[ledRight][0]:");
  Serial.print(ringCloudLedPos[ledRight][0]);
  Serial.print(", ");
  setupCloudRing(cloudRadius);
  for (int i = 0; i < maxNumbCloud; i++) {
    float xPos =  ((ringCloudLedPos[ledRight][0] + (cloudRadius * 2) ) / maxNumbCloud) * i ; // calculate the begin pos clouds
    cloudPos[i][0] = xPos;
    cloudPos[i][1] = generateYOffset(yPos, yOffset);
    Serial.print(i);
    Serial.print(" xPos=");
    Serial.print(xPos);
    Serial.print(", ");

  }

}


void applyCloudFadeToWeatherEffect() {
  float tempCloudAmountPercentage;
  int tempCloudAmount;

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i == 22 ) { // test send msg
      temp++;
      if (temp > 100) {
        temp = 0;
                Serial.println();
                Serial.print(" clAm[22] =");
                Serial.print(cloudAmount[i]);
      }
    }

    if (cloudAmount[i] < 1.00) {
      weatherEffect[i] *= cloudAmount[i]; // 0.0=dark | 1.00=light
    }
    cloudAmount[i] = 1.00;
  }
}

//================================================ new code

float easeEffect(float procentage){
//    return sq(procentage);
//    return procentage;
//   return -(cos(PI * procentage) - 1) / 2;
return 1 - pow(1 - procentage, 3);
}

float calculateLedProcentage( float tempLow, float tempHigh, float ledDistance ) {
  float proces =  ledDistance - tempLow;
  float maxProcent = tempHigh - tempLow;
  float procentage =  proces / maxProcent;
  procentage= 1 - procentage;
  return  easeEffect(procentage);
  
//  sq(1 - procentage);
}

float calculateLedBrightness(float calCloudRadius, float ledDistance, float fadeEdge, float maxFade, int thisLed) {
  float darkCloud = calCloudRadius - (fadeEdge * calCloudRadius);
  float cloudBorder = calCloudRadius;
  if (ledDistance <= darkCloud) {
    return maxFade;
  } else if (ledDistance > darkCloud && ledDistance < cloudBorder) {
    float revProcentage =  calculateLedProcentage(darkCloud, cloudBorder, ledDistance);
    maxFade = 1 - maxFade; // reverce the maxFade
    return 1 - ( (maxFade * cloudAmount[thisLed]) * revProcentage); // get current reverse brightness and reverse result
  } else if (ledDistance >= cloudBorder) {
    return 1;
  }
}

float getAngle(float AbsoluteX, float AbsoluteY) {
  float theta ;
  theta  = atan2(AbsoluteY, AbsoluteX);
  float angleDegree = theta * 180 / 3.14159265;
  return theta;
}

float getDistance(float AbsoluteX, float AbsoluteY, int thisLed) {
  AbsoluteX = fabs(AbsoluteX);
  AbsoluteY = fabs(AbsoluteY);
  float distance = sqrt(sq(AbsoluteX) + sq(AbsoluteY));
  return distance;
}

float getCloudRadius(float AbsoluteX, float AbsoluteY, float cloudRadius, float cloudHeightMultiplier, int thisLed) {
  float theta = getAngle(AbsoluteX, AbsoluteY);
  float borderX = cloudRadius * cos(theta);
  float borderY = (cloudRadius * cloudHeightMultiplier) * sin(theta);
  float angleDegree = theta * 180 / 3.14159265;
  return getDistance(borderX, borderY, 0);
}

float calCloudSpeed() {
  return wind_speed * 0.002;
}

void runCloud( int maxNumbCloud, float cloudSpeed, float cloudRadius, float cloudHeightMultiplier, float fadeEdge, float maxFade, float yPos, float yOffset) {
  checkResetCloudBeginPos(maxNumbCloud, cloudRadius, cloudHeightMultiplier, yPos, yOffset);

  for (int thisCloud = 0; thisCloud < maxNumbCloud; thisCloud++) {
    if (cloudSpeed < 0.0000) {
      cloudPos[thisCloud][0] += calCloudSpeed();
    } else {
      cloudPos[thisCloud][0] += cloudSpeed;
    }
    if ( cloudPos[thisCloud][0] > ringCloudLedPos[ledRight][0] + cloudRadius) {
      cloudPos[thisCloud][0] = - cloudRadius;
      cloudPos[thisCloud][1] = generateYOffset(yPos, yOffset);
    }

    for (int thisLed = 0; thisLed < NUM_LEDS; thisLed++) {
      if (ringCloudLedPos[thisLed][0] < cloudPos[thisCloud][0] + cloudRadius && ringCloudLedPos[thisLed][0] > cloudPos[thisCloud][0] - cloudRadius) {// check horizontal axis if led is in cloud
        if (ringCloudLedPos[thisLed][1] < cloudPos[thisCloud][1] + (cloudRadius * cloudHeightMultiplier) && ringCloudLedPos[thisLed][1] > cloudPos[thisCloud][1] - (cloudRadius * cloudHeightMultiplier)) { // check vertical axis if led is in cloud
          float x1 = cloudPos[thisCloud][0];
          float y1 = cloudPos[thisCloud][1];
          float x2 = ringCloudLedPos[thisLed][0];
          float y2 = ringCloudLedPos[thisLed][1];

          float AbsoluteX = x2 - x1; // x from led to center cloud
          float AbsoluteY = y2 - y1; // y from led to center cloud

          float ledDistance = getDistance(AbsoluteX, AbsoluteY, thisLed);
          float cloudRadiusForLed = getCloudRadius(AbsoluteX, AbsoluteY, cloudRadius, cloudHeightMultiplier, thisLed);
          float ledBrightness = calculateLedBrightness(cloudRadiusForLed, ledDistance, fadeEdge, maxFade, thisLed);
          if (ledBrightness < cloudAmount[thisLed]) {
            if (ledBrightness < 0) {
              cloudAmount[thisLed] = 0;
            } else {
              cloudAmount[thisLed] = ledBrightness;
            }
          }
        }
      }
    }
  }
}

// ========== godrays for clear sky

bool godRayBool[NUM_LEDS];
double godRayShine[NUM_LEDS];
//long int godRayTimer = 0;
//int godRayDurance = 2000;

void addGodRay() {
  byte tempGod = random(halfNUM_LEDS);

  godRayBool[tempGod] = true;
  Serial.print("add god ray on led:");
  Serial.println(tempGod);
}

//float shineMax, float godRayShineSpeed
void clearSky() {
  float godRayShineSpeed = 0.5;
  float shineMax = 255;


  if (godRayTimer < millis()) {
    addGodRay();
    godRayTimer = godRayDurance + millis();
  }

  for (int i = 0; i < halfNUM_LEDS; i++ ) {
    if (godRayBool[i] == true) {
      godRayShine[i] += godRayShineSpeed;
      godRayShine[halfNUM_LEDS + i] += godRayShineSpeed;

      if ( godRayShine[i] > shineMax ) {
        godRayBool[i] = false;
      }

    } else if (godRayBool[i] == false) {
      godRayShine[i] -= godRayShineSpeed;
      godRayShine[halfNUM_LEDS + i] -= godRayShineSpeed;
      if (godRayShine[i] <= 0) {
        godRayShine[i] = 0.0;
        godRayShine[halfNUM_LEDS + i] = 0.0;
      }
    }

  }
}

void applyGodRay() {
  counter++;
  if (counter > 100) {
    counter = 0;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i == 1 && counter == 0) {
      Serial.print("god ray 1 =");
      Serial.print(godRayShine[i]);
      Serial.print("   godRayBool[1]=");
      Serial.println( godRayBool[i]);
    }
    leds[i].fadeLightBy(godRayShine[i]);
  }
}
