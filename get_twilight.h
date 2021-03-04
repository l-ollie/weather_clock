const char* sinriseSunsetHost = "api.sunrise-sunset.org";

void getTwilightInfo() {

  if (connectToWifi() == true) {
  } else {
    Serial.println("getTwilightInfo no wifi");
    return;
  }

  Serial.print("connecting to ");
  Serial.println(sinriseSunsetHost);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;

  if (!client.connect(sinriseSunsetHost, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/json?lat=";
  url += coord_lon;
  // you can change the units. by default its
  url += "&lng=";
  url += coord_lat;
  url += "&formatted=0";
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // Send the request to the sunrise-sunset
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + sinriseSunsetHost + "\r\n" +
               "Connection: close\r\n\r\n");

  delay(500);

  // Read all the lines you get back from sunrise-sunset
  while (client.available()) {
    String line = client.readStringUntil('\n');
    //    Serial.println(line);

    // Look for the empty line, after this you get the body (info you requested)
    if (line.startsWith("{")) {


      //Deserialize the sunrise-sunset info it into a Json
      parseJsonSunrise(line);
      line = client.readStringUntil('\r');

    }
  }
  Serial.println("closing connection");
}
