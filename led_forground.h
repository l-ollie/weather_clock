byte sellectForground = 0;
byte previousSellectForground = 255;
void runClouds();
void runRain();

void forgroundStart() {
  // check weather code and make switch code
  if (weather_0_id >= 800 && weather_0_id < 900 ) { // check if code is between 800-900 clear or clouds code from OpenWeather
    if (weather_0_id = 800) { // check if clear sky
      sellectForground = 0;
    } else {
      sellectForground  = 1; // otherwise set set stage to clouds
    }
  }
  else if (weather_0_id >= 500 && weather_0_id < 600 ) { // check if code is between 500-600 rain code from OpenWeather
    sellectForground  = 2;
  } else {
    sellectForground  = 0; // if no special case then no forground
  }
  sellectForground = 1 ;
  switch ( sellectForground ) {
    case 0: // no forground
      break;
    case 1: // set clouds
      runClouds();
      
      break;
    case 2:
//      runRain();
      break;
    default:
      break;
  }

  // print if sellectForground is different
  if (previousSellectForground != sellectForground) {
    Serial.print("weather_0_id = " );
    Serial.print(weather_0_id);
    Serial.print(" | and forground program selected : " );
    Serial.print(sellectForground);
    Serial.println(" ");

    previousSellectForground = sellectForground;
  }
}
