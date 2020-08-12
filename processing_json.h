#include <ArduinoJson.h>

// Create Json file for openweathermap
const size_t capacityOpenWeatherMap = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(13) + 290;
StaticJsonDocument<capacityOpenWeatherMap> docOpenWeatherMap;
JsonObject weather_0;
int weather_0_id;
JsonObject main;
float main_feels_like;
JsonObject wind;
float wind_speed;
long dt;
JsonObject sys;
long sys_sunrise;
long sys_sunset ;
float coord_lon;
float coord_lat;

JsonObject results;
const char* results_sunrise;
const char* results_sunset;
const char* results_civil_twilight_begin ;
const char* results_civil_twilight_end ;


const size_t capacitySunriseSunset = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(10) + 480;
StaticJsonDocument <capacitySunriseSunset> docSunriseSunset;


void savingValues();
void parseJson(String incommingMsg);
void savingValuesSunrise ();



void parseJsonOpenWeatherMap(String incommingMsg) {
  DeserializationError err = deserializeJson(docOpenWeatherMap, incommingMsg);
  Serial.println("Deserialization json done" );
  // if the deserialization didnt work print out the error
  if (err) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(err.c_str());
  }
  savingValues();
}

void parseJsonSunrise(String incommingMsg) {
  DeserializationError err = deserializeJson(docSunriseSunset, incommingMsg);
  Serial.println("Deserialization json done" );
  // if the deserialization didnt work print out the error
  if (err) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(err.c_str());
  }
  savingValuesSunrise();
}
void savingValuesSunrise () {
  results = docSunriseSunset["results"];
  results_sunrise = results["sunrise"];
  results_sunset = results["sunset"];
  results_civil_twilight_begin = results["civil_twilight_begin"];
  results_civil_twilight_end  = results["civil_twilight_end"];

  Serial.print(" civil twilight begin is :  ");
  Serial.print(results_civil_twilight_begin);
  Serial.print(" | civil twilight ends is :  ");
  Serial.print(results_civil_twilight_end);

}


void savingValues () {
  weather_0 = docOpenWeatherMap["weather"][0];
  weather_0_id = weather_0["id"];
  main = docOpenWeatherMap["main"];
  main_feels_like = main["feels_like"];
  wind = docOpenWeatherMap["wind"];
  wind_speed = wind["speed"];
  sys = docOpenWeatherMap["sys"];
  sys_sunrise = sys["sunrise"];
  sys_sunset = sys["sunset"];
  coord_lon = docOpenWeatherMap["coord"]["lon"];
  coord_lat = docOpenWeatherMap["coord"]["lat"];
  dt = docOpenWeatherMap["dt"];
}
