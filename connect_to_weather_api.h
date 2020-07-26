#include "processing_json.h";

// these are the credantials used for openweathermap.org
const char* city = "Leiden";
const char* openweatherapikey = "a2ed31ee07568e51c5901c4ea33082df";
const char* openWeatherMapHost = "api.openweathermap.org";

void getWeatherInfo() {

  if (connectToWifi() == true) {
  } else {
    Serial.println("getWeatherInfo no wifi");
    return;
  }

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
//      Serial.println("I read the last line");

      //Deserialize the openweathermap info it into a Json
      parseJsonOpenWeatherMap(client.readStringUntil('\r'));

    }
  }
  Serial.println("closing connection");
}
