
void readSerialMonitor() {
  if (Serial.available()) {
    String rxString = "";
    String strArr[8]; //Set the size of the array to equal the number of values you will be receiveing.
    //Keep looping until there is something in the buffer.
    while (Serial.available()) {
      //Delay to allow byte to arrive in input buffer.
      delay(2);
      //Read a single character from the buffer.
      char ch = Serial.read();
      //Append that single character to a string.
      rxString += ch;
    }
    int stringStart = 0;
    int arrayIndex = 0;
    for (int i = 0; i < rxString.length(); i++) {
      //Get character and check if it's our "special" character.
      if (rxString.charAt(i) == ',') {
        //Clear previous values from array.
        strArr[arrayIndex] = "";
        //Save substring into array.
        strArr[arrayIndex] = rxString.substring(stringStart, i);
        //Set new string starting point.
        stringStart = (i + 1);
        arrayIndex++;
      }
    }
    //Put values from the array into the variables.
    String value1 = strArr[0];
    String value2 = strArr[1];
    String value3 = strArr[2];
    String value4 = strArr[3];
    String value5 = strArr[4];
    String value6 = strArr[5];
    String value7 = strArr[6];
    String value8 = strArr[7];

    //Convert string to int if you need it.
    weather_0_id = value1.toInt();
   serialInt[0] = value2.toInt();
    serialInt[1] = value3.toInt();
    serialInt[2] = value4.toInt();
    serialInt[3] = value5.toInt();
    serialInt[4] = value6.toInt();
    serialInt[5] = value7.toInt();
    serialInt[6] = value8.toInt();

       serialFloat[0] = value2.toFloat();
    serialFloat[1] = value3.toFloat();
    serialFloat[2] = value4.toFloat();
    serialFloat[3] = value5.toFloat();
    serialFloat[4] = value6.toFloat();
    serialFloat[5] = value7.toFloat();
    serialFloat[6] = value8.toFloat();
    
    Serial.print("send weather_0_id and other var: ");
    Serial.print(weather_0_id);
    Serial.print(",");
    Serial.print(serialInt[0]);
    Serial.print(",");
    Serial.print(serialInt[1]);
    Serial.print(",");
    Serial.print(serialFloat[2]);
    Serial.print(",");
    Serial.print(serialInt[3]);
    Serial.print(",");
    Serial.print(serialInt[4]);
    Serial.print(",");
    Serial.print(serialInt[5]);
    Serial.print(",");
    Serial.print(serialInt[6]);
    Serial.println(",");
  }

}
