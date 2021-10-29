int sellectForground = 0;
int previousSellectForground = 255;
byte weatherEffect[NUM_LEDS]; // 1.00=100%fade, 0.00=0%fade. I add every % from the led animation to calculate the fading

void runClouds();
void runRainLight();
void runDrizzleLight();
void runDrizzleHeavy();
void runDrizzleShower();
void runExperiment();
void cloudsExperiment();
void applyWeatherFadeEffect();
void runCloud( int maxNumbCloud, float cloudSpeed, float cloudRadius, float cloudHeightMultiplier, float fadeEdge, float maxFade, float yPos, float yOffset);
void clearSky();
void applyGodRay();
void applyCloudFadeToWeatherEffect();


void weatherSetup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    weatherEffect[i] = 255;
  }
}

void setWeatherType() {
  sellectForground = weather_0_id;
}

void forgroundStart() {
  switch ( weather_0_id ) {
    case 800: // 800 clear sky
      //      clearSky();
      //      applyGodRay();
      //      sunrayLed(3);
      break;
    // ======== clouds
    case 801: // 801  clouds - 11-25%
      runCloud(3, -0.011, 5, 1, 0.4, 0.0, 0, 10); // 25% - 50%
      applyCloudFadeToWeatherEffect();
      break;
    case 802: // 802 clouds - 25-50%
      runCloud(3, -0.001, 10, 1, 0.3, 0.0, 0, 15); // 25% - 50%
      applyCloudFadeToWeatherEffect();
      break;
    case 803: // 803 clouds - 51-84%
      runCloud(4, -0.04, 10, 1, 0.4, 0.0, 2, 10); // 50% - 81%
      applyCloudFadeToWeatherEffect();
      break;
    case 804: // 804 clouds - 85-100%
      runCloud(4, -0.04, 10, 1, 0.4, 0.0, 2, 10); // 50% - 81%
      applyCloudFadeToWeatherEffect();
      break;
    // ======== rain
    case 500: // light rain,
      runRainLight();
      break;
    case 501: // medium (freeing) rain
      runRainLight();
      break;
    case 502: // heavy (intensity) rain
      runRainLight();
      break;
    case 504: // extreme rain
      runRainLight();
      break;
    case 520: // light intensity shower rain
      runRainLight();
      break;
    case 521: // medium shower rain
      runRainLight();
      break;
    case 522: // heavy shower rain
      runRainLight();
      break;
    // ======== drizzle
    case 300: // drizzle light intensity
      // experiment() 666,90,100,0.60,0,0,0,0,
      runDrizzleLight();
      break;
    case 301: // drizzle
      runDrizzleLight();
      break;
    case 302: // drizzle heavy intensity
      runDrizzleHeavy();
      break;
    case 310: // drizzle light intensity rain
      runDrizzleLight();
      break;
    case 311: // drizzle rain
      runDrizzleLight();
      break;
    case 312: // drizzle intensity rain
      runDrizzleLight();
      break;
    case 313: // drizzle rain shower
      runDrizzleLight();
      break;
    case 314: // drizzle rain shower heavy
      runDrizzleLight();
      break;
    case 321: // drizzle shower
      runDrizzleShower();
      break;
    case 666: // experiment
      runExperiment();
      break;
    case 665: // experiment
      cloudsExperiment();
      break;
    default:
      break;
  }


  // print if sellectForground is different
  if (previousSellectForground != sellectForground) {
    Serial.print("changing weather conditions" );
    Serial.print("weather_0_id = " );
    Serial.print(weather_0_id);
    Serial.print(" | and forground program selected : " );
    Serial.print(sellectForground);
    Serial.println(" ");
    previousSellectForground = sellectForground;
  }

  applyWeatherFadeEffect();
}

void applyWeatherFadeEffect() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (weatherEffect[i] != 255) { // if i dont have to fade, skip this. 0 is complete dark
      byte fade = 255 - weatherEffect[i];
      leds[i].fadeToBlackBy(fade);
      if (i == 22 && weatherEffect[22] <= 255 && weatherEffect[22] != 0 ) {
        Serial.print(" | weatherEffect:");
        Serial.print(weatherEffect[i]);
        Serial.print(" | fade:");
        Serial.println(fade);

      }
    }

    weatherEffect[i] = 255;
  }
}
