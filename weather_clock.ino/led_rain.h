bool rainDrop[36];
float rainDropAmountOnLed[36];
int long rainDroperTimer;
int long rainDroperTimer2 = 10;
int long rainDroperTimer3 = 20;


void rainSetup() {
  for (byte i = 0; 1 < NUM_LEDS; i++) {
    rainDropAmountOnLed[i] = 1;
  }
}

void createRainfall(int dropRainMinTime, int dropRainMaxTime, float drupletMaxFade, int long &rainDroperTimer, byte DrupletOnLedRangeBegin, byte DrupletOnLedRangeEnd);
void createDruplet(int dropRainMinTime, int dropRainMaxTime, float drupletMaxFade, int long &rainDroperTimer, byte DrupletOnLedRangeBegin, byte DrupletOnLedRangeEnd);
void fadeDrupelets(float rainFade);


//==================== rain pre-settings ====================

void runExperiment() { // now heavy rain
  // medium rain 666,50,60,0.10,0.00050, // maybe more in the middle // 666,40,42,0.00,0.00200,
  // heavy rain 666,10,15,0.05,0.00200, // 666,20,25,0.00,0.00200,
  // heavy drizzle 666,10,15,0.30,0.00200,
  // medium drizzle
  // light drizzle 666,10,15,0.50,0.00100,
// ice 666,20,25,0.20,0.000100,

//  createRainfall(serialInt[0], serialInt[1], serialFloat[2], rainDroperTimer, 0, 36);
    createRainfall(serialInt[0], serialInt[1], serialFloat[2], rainDroperTimer,  9, 27);
 
  fadeDrupelets(serialFloat[3]);
}
void runExperiment2() { // now heavy rain
  // medium rain 666,50,60,0.10,0.00050, // maybe more in the middle // 666,40,42,0.00,0.00200,
  // heavy rain 666,10,15,0.05,0.00200, // 666,20,25,0.00,0.00200,
  // heavy drizzle 666,10,15,0.30,0.00200,
  // medium drizzle
  // light drizzle 666,10,15,0.50,0.00100,
// ice 666,20,25,0.20,0.000100,

  createRainfall(serialInt[0], serialInt[1], serialFloat[2], rainDroperTimer, 9, 27);
  //0.00045
  fadeDrupelets(serialFloat[3]);
}

void runRainLight() {
  createRainfall(100, 500, 0, rainDroperTimer, 9, 27);
  fadeDrupelets(0.00045);
}

void runDrizzleLight() {
  createRainfall(400, 500, 0.2, rainDroperTimer, 9, 17);
  createRainfall(400, 500, 0.2, rainDroperTimer2, 14, 22);
  createRainfall(400, 500, 0.2, rainDroperTimer3, 19, 27);
  fadeDrupelets(0.0010);
}

void runDrizzleHeavy() {
  byte DrupletOnLedRangeBegin = 30;
  byte DrupletOnLedRangeEnd = 100;
  float drupletMaxFade = 0.15;
  createRainfall(DrupletOnLedRangeBegin, DrupletOnLedRangeEnd, drupletMaxFade, rainDroperTimer, 9, 17);
  createRainfall(DrupletOnLedRangeBegin, DrupletOnLedRangeEnd, drupletMaxFade, rainDroperTimer2, 13, 22);
  createRainfall(DrupletOnLedRangeBegin, DrupletOnLedRangeEnd, drupletMaxFade, rainDroperTimer3, 20, 27);
  fadeDrupelets(0.0010);
}

void runDrizzleShower() {

};

//==================== rain mechanic ====================


void createRainfall(int dropRainMinTime, int dropRainMaxTime, float drupletMaxFade, int long &rainDroperTimer, byte DrupletOnLedRangeBegin, byte DrupletOnLedRangeEnd) { // check if time to create another druplet
  if (millis() == 0) {
    createDruplet(dropRainMinTime, dropRainMaxTime, drupletMaxFade, rainDroperTimer, DrupletOnLedRangeBegin, DrupletOnLedRangeEnd);
  }
  if (millis() >= rainDroperTimer) {
    createDruplet(dropRainMinTime, dropRainMaxTime, drupletMaxFade, rainDroperTimer, DrupletOnLedRangeBegin, DrupletOnLedRangeEnd);
  }
}

void createDruplet(int dropRainMinTime, int dropRainMaxTime, float drupletMaxFade, int long &rainDroperTimer, byte DrupletOnLedRangeBegin, byte DrupletOnLedRangeEnd) { // create new druplet timer and add druplet to led
  rainDroperTimer = millis() + random(dropRainMinTime, dropRainMaxTime);
  rainDropAmountOnLed[random8  (DrupletOnLedRangeBegin, DrupletOnLedRangeEnd)] = drupletMaxFade;
}

void fadeDrupelets(float rainFade) {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (rainDropAmountOnLed[i] < 1) {
      rainDropAmountOnLed[i] += rainFade;
      weatherEffect[i] *= rainDropAmountOnLed[i];
    }
    else {
      rainDropAmountOnLed[i] = 1;
    }
  }
}
