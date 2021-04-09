/*
Bugs
applyTwilight - wanneer actief, lijkt hij even in helderheid omhoog te gaan



  weather type codes
  https://openweathermap.org/weather-conditions#Weather-Condition-Codes-2

  https://openweathermap.org/current#data

  http://api.openweathermap.org/data/2.5/weather?q=Leiden&appid=a2ed31ee07568e51c5901c4ea33082df





====== Group 2xx: Thunderstorm
ID  Main  Description Icon
200 Thunderstorm  thunderstorm with light rain   11d
201 Thunderstorm  thunderstorm with rain   11d
202 Thunderstorm  thunderstorm with heavy rain   11d
210 Thunderstorm  light thunderstorm   11d
211 Thunderstorm  thunderstorm   11d
212 Thunderstorm  heavy thunderstorm   11d
221 Thunderstorm  ragged thunderstorm  11d
230 Thunderstorm  thunderstorm with light drizzle  11d
231 Thunderstorm  thunderstorm with drizzle  11d
232 Thunderstorm  thunderstorm with heavy drizzle  11d

 /*
    default  0  clear
    1  clouds - light 
    x2  clouds - heavy
    3  rain - light
    x4  rain - heavy
    5  drizzle - light : 300
    6 drizzle - medium : 301
    7  drizzle - heavy : 302,312,314,321
    
    x7  snow - light
    x8  snow - heavy
    x9  thunder - rain - light
    x10  thunder - rain - heavy
    x11  thunder - drizzle - light
    x12  thunder - drizzle - heavy
 * /


====== Group 3xx: Drizzle
ID  Main  Description Icon
300 Drizzle light intensity drizzle  09d
301 Drizzle drizzle  09d
302 Drizzle heavy intensity drizzle  09d
310 Drizzle light intensity drizzle rain   09d
311 Drizzle drizzle rain   09d
312 Drizzle heavy intensity drizzle rain   09d
313 Drizzle shower rain and drizzle  09d
314 Drizzle heavy shower rain and drizzle  09d
321 Drizzle shower drizzle   09d
====== Group 5xx: Rain
ID  Main  Description Icon
500 Rain  light rain   10d
501 Rain  moderate rain  10d
502 Rain  heavy intensity rain   10d
503 Rain  very heavy rain  10d
504 Rain  extreme rain   10d
511 Rain  freezing rain  13d
520 Rain  light intensity shower rain  09d
521 Rain  shower rain  09d
522 Rain  heavy intensity shower rain  09d
531 Rain  ragged shower rain   09d
====== Group 6xx: Snow
ID  Main  Description Icon
600 Snow  light snow   13d
601 Snow  Snow   13d
602 Snow  Heavy snow   13d
611 Snow  Sleet  13d
612 Snow  Light shower sleet   13d
613 Snow  Shower sleet   13d
615 Snow  Light rain and snow  13d
616 Snow  Rain and snow  13d
620 Snow  Light shower snow  13d
621 Snow  Shower snow  13d
622 Snow  Heavy shower snow  13d
====== Group 7xx: Atmosphere
ID  Main  Description Icon
701 Mist  mist   50d
711 Smoke Smoke  50d
721 Haze  Haze   50d
731 Dust  sand/ dust whirls  50d
741 Fog fog  50d
751 Sand  sand   50d
761 Dust  dust   50d
762 Ash volcanic ash   50d
771 Squall  squalls  50d
781 Tornado tornado  50d
====== Group 800: Clear
ID  Main  Description Icon
800 Clear clear sky  01d 01n
====== Group 80x: Clouds
ID  Main  Description Icon
801 Clouds  few clouds: 11-25%   02d 02n
802 Clouds  scattered clouds: 25-50%   03d 03n
803 Clouds  broken clouds: 51-84%  04d 04n
804 Clouds  overcast clouds: 85-100%   04d 04n

  Json
  https://arduinojson.org/book/deserialization_tutorial6.pdf#page=12

  https://arduinojson.org/v6/assistant/


  install huzzah board
  https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/using-arduino-ide



  wifi status
  0 : WL_IDLE_STATUS when Wi-Fi is in process of changing between statuses
  1 : WL_NO_SSID_AVAILin case configured SSID cannot be reached
  3 : WL_CONNECTED after successful connection is established
  4 : WL_CONNECT_FAILED if connection failed
  6 : WL_CONNECT_WRONG_PASSWORD if password is incorrect
  7 : WL_DISCONNECTED if module is not configured in station mode
*/
