
void readSerialMonitor() {
  if (Serial.available()) {
    String rxString = "";
    String strArr[9]; //Set the size of the array to equal the number of values you will be receiveing.
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
    String weahterType = strArr[0];

    String value0 = strArr[1];
    String value1 = strArr[2];
    String value2 = strArr[3];
    String value3 = strArr[4];
    String value4 = strArr[5];
    String value5 = strArr[6];
    String value6 = strArr[7];
    String value7 = strArr[8];

    //Convert string to int if you need it.
    weather_0_id = weahterType.toInt();

    serialInt[0] = value0.toInt();
    serialInt[1] = value1.toInt();
    serialInt[2] = value2.toInt();
    serialInt[3] = value3.toInt();
    serialInt[4] = value4.toInt();
    serialInt[5] = value5.toInt();
    serialInt[6] = value6.toInt();
    serialInt[7] = value7.toInt();

    serialFloat[0] = value0.toFloat();
    serialFloat[1] = value1.toFloat();
    serialFloat[2] = value2.toFloat();
    serialFloat[3] = value3.toFloat();
    serialFloat[4] = value4.toFloat();
    serialFloat[5] = value5.toFloat();
    serialFloat[6] = value6.toFloat();
    serialFloat[7] = value7.toFloat();

    Serial.println("send weather_0_id and other var: ");
    if (weather_0_id ==  666) {
      Serial.print(weather_0_id);
      Serial.print(",");
      Serial.print(serialInt[0]);
      Serial.print(",");
      Serial.print(serialInt[1]);
      Serial.print(",");
      Serial.print(serialFloat[2], 2);
      Serial.print(",");
      Serial.print(serialFloat[3], 5);
      Serial.println(",");
    }

    if (weather_0_id == 665) {
      Serial.print(weather_0_id);
      Serial.print(",");
      Serial.print(serialInt[0]);
      Serial.print(",");
      Serial.print(serialFloat[1] );
      Serial.print(",");
      Serial.print(serialFloat[2]);
      Serial.print(",");
      Serial.print(serialFloat[3] );
      Serial.print(",");
      Serial.print(serialFloat[4] );
      Serial.print(",");
      Serial.print(serialFloat[5], 2);
      Serial.print(",");
      Serial.print(serialFloat[6], 2);
      Serial.print(",");
      Serial.print(serialFloat[7], 2);
      Serial.println(",");

      Serial.print("maxNumbCloud=");
      Serial.println(serialInt[0]);
      Serial.print("cloudSpeed=");
      Serial.println(serialFloat[1] );
      Serial.print("cloudRadius=");
      Serial.println(serialFloat[2] );
      Serial.print("cloudHeightMultiplier=");
      Serial.println(serialFloat[3] );
      Serial.print("fadeEdge=");
      Serial.println(serialFloat[4] );
      Serial.print("maxFade=");
      Serial.println(serialFloat[5] );
      Serial.print("yPos=");
      Serial.println(serialFloat[6] );
      Serial.print("yOffset=");
      Serial.println(serialFloat[7] );


      Serial.println(",");
//      void runCloud(int maxNumbCloud, float cloudSpeed, float cloudRadius, float cloudHeightMultiplier, float fadeEdge, float maxFade, float yPos, float yOffset);

      //  runCloud(0maxNumbCloud, 1cloudSpeed, 2cloudRadius, 3heightMultiplier, 4fadeEdge, 5maxFade, 6yPos); // radius, heightMultiplier, fadeEdge, maxFade
      //void setCloudBeginPos(byte maxNumbCloud, int cloudRadius, float cloudHeightMultiplier, float yPos);

      setCloudBeginPos(serialInt[0], serialInt[2], serialFloat[3], serialFloat[6], serialFloat[7]);
      //void setCloudBeginPos(byte maxNumbCloud, int cloudRadius, float cloudHeightMultiplier, float yPos);

    }
    //    Serial.print(serialInt[4]);
    //    Serial.print(",");
    //    Serial.print(serialInt[5]);
    //    Serial.print(",");
    //    Serial.print(serialInt[6]);
    //    Serial.println(",");
    resetFrequentTimer();
  }

}
