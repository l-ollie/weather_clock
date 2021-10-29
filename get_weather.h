#include "processing_json.h";

// these are the credantials used for openweathermap.org
const char* city = "Leiden";
const char* openweatherapikey = "a2ed31ee07568e51c5901c4ea33082df";
const char* openWeatherMapHost = "api.openweathermap.org";

void ShowLedRandomPixCol(byte pixCol0, byte pixCol1, byte pixCol2 ); // function is in led_UI.h
void setLoadColor(byte tempLoadColor0, byte tempLoadColor1, byte tempLoadColor2);
void setWeatherType();


void getWeatherInfo() {
  //  setLoadColor(0, 100, 200);

  if (connectToWifi() == true) {
  } else {
    Serial.println("getWeatherInfo no wifi");
    return;
  }
  ShowLedRandomPixCol(0, 0, 200);

  Serial.print("connecting to ");
  Serial.println(openWeatherMapHost);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;

  if (!client.connect(openWeatherMapHost, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/data/2.5/weather?q=";
  url += city;
  // you can change the units. by default its
  url += "&units=metric";
  url += "&appid=";
  url += openweatherapikey;
  //  Serial.print("Requesting URL: ");
  //  Serial.println(url);

  // Send the request to the openweathermap
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + openWeatherMapHost + "\r\n" +
               "Connection: close\r\n\r\n");

  delay(500);

  // Read all the lines you get back from openweathermap
  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);

    // Look for the empty line, after this you get the body (info you requested)
    if (line == "\r") {

      ShowLedRandomPixCol(0, 200, 0);

      //Deserialize the openweathermap info it into a Json
      parseJsonOpenWeatherMap(client.readStringUntil('\r'));

    }
  }
  Serial.println("get weather done and closing connection");
  client.stop();
  setWeatherType();
}

void printWeather() {
  Serial.print("Current temp " );
  Serial.print( current_temp);
  Serial.print(" | Temp feels like " );
  Serial.print( main_feels_like);
  Serial.print("C ");
  Serial.print(" | weather_0_id = " );
  Serial.println(weather_0_id);
  Serial.print(" | windspeed = " );
  Serial.println(wind_speed);
  //  Serial.print(" | Sunset at ");
  //  Serial.print(hour(sys_sunset));
  //  Serial.print(":");
  //  Serial.print(minute(sys_sunset));
  //  Serial.print(" | Sunrise at");
  //
  //  Serial.print(hour(sys_sunrise));
  //  Serial.print(":");
  //  Serial.print(minute(sys_sunrise));

}
