// THIS FUNCTION WILL MAP THE float VALUES IN THE GIVEN RANGE
// This function was built using ChatGPT.

float linearizeVoltage(float x, float* xValues, float* yValues, int points) {
  // If x is out of bounds, clamp it to the min or max
  if (x <= xValues[0]) return yValues[0];
  if (x >= xValues[points - 1]) return yValues[points - 1];

  // Find the interval x is in
  for (int i = 0; i < points - 1; i++) {
    if (x >= xValues[i] && x <= xValues[i + 1]) {
      // Linear interpolation formula
      float x0 = xValues[i];
      float x1 = xValues[i + 1];
      float y0 = yValues[i];
      float y1 = yValues[i + 1];
      return y0 + (y1 - y0) * ((x - x0) / (x1 - x0));
    }
  }
  // Should never reach here
  return 0.0;
}


//This functions will calculate the curret, voltage, power and energy values
void get_values()
{
  float rawVBatt1  = 0;
  float rawVBatt2  = 0;
  float rawIBatt1  = 0; 
  float rawIBatt2  = 0;
  float rawISet1   = 0;
  float rawISet2   = 0;
 

  // For loops is for averaging measured values we choose 50.
  // If needed this value can be increased to get more stable readings.

  for(int x = 0; x < 50; x++){
    rawVBatt1 += analogRead(V1P)  * (referenceVoltage / 4095.0); 
    rawVBatt2 += analogRead(V2P)  * (referenceVoltage / 4095.0);   
    rawIBatt1 += analogRead(I1P)  * (referenceVoltage / 4095.0);
    rawIBatt2 += analogRead(I2P)  * (referenceVoltage / 4095.0);  
    rawISet1 += analogRead(I1_setP) * (referenceVoltage / 4095.0);  
    rawISet2 += analogRead(I2_setP) * (referenceVoltage / 4095.0);
    delay(1);
  }

  rawVBatt1 = rawVBatt1/50;
  rawVBatt2 = rawVBatt2/50;
  rawIBatt1 = rawIBatt1/50;
  rawIBatt2 = rawIBatt2/50;
  rawISet1  = rawISet1/50;
  rawISet2  = rawISet2/50;

  VBatt1 = linearizeVoltage(rawVBatt1, Batt1VoltagePoints, correspondingVBatt1, numPointsVBatt1) ;
  VBatt2 = linearizeVoltage(rawVBatt2, Batt2VoltagePoints, correspondingVBatt2, numPointsVBatt2) ;
  IBatt1 = linearizeVoltage(rawIBatt1, Batt1CurrentPoints, correspondingIBatt1, numPointsIBatt1) ;
  IBatt2 = linearizeVoltage(rawIBatt2, Batt2CurrentPoints, correspondingIBatt2, numPointsIBatt2) ;
  ISet1  = linearizeVoltage(rawISet1,  Set1CurrentPoints,  correspondingISet1,  numPointsISet1) ;
  ISet2  = linearizeVoltage(rawISet2,  Set2CurrentPoints,  correspondingISet2,  numPointsISet2) ;

  //Voltage calibration:
  /*Serial.print("Battery1 Voltage: ");         
  Serial.print(rawVBatt1,4);                  
  Serial.print("  , Battery2 Voltage: "); 
  Serial.println(rawVBatt2,4);*/

  //Current Batt1 calibration:
  /*Serial.print("Battery1 Current: ");        
  Serial.print(rawIBatt1,4);
  Serial.print("  , Battery1 Setting: ");        
  Serial.println(rawISet1,4);*/

  //Current Batt2 calibration:
  /*Serial.print("Battery2 Current: "); 
  Serial.print(rawIBatt2,4);                 
  Serial.print("  , Battery2 Setting: "); 
  Serial.println(rawISet2,4);*/

  


/* Calibration Processs: 
     Voltage Readings:
         - We connect an accurate and stable voltage source to 2 inputs with an accurate voltmeter.
         - Uncomment Voltage calibration serial print code.
         - Set the voltage source for an example to 1V then open the terminal to see the MCU readings
           in my case Input Battery1 = 0.503V and Input Battery2 = 0.501V, record these readings 
           in the Batt1VoltagePoints Batt2VoltagePoints Lists with respect to corresponding voltages in 
           correspondingVBatt1 and correspondingVBatt2 lists.
         - repeat this step with different voltages until reaching an accurate readings in LCD equal to 
           voltmeter in our available voltage range, in my case is 0-4.5V range.

      Current Readings:
         - We connect 2 terminlas of the Shunt resistor to a constant current source (screenshot of the location is included).
         - We use an accurate and stable constant current load in series with an accurate ammeter.
         - Uncomment Current Batt1/2 calibration serial print code.
         - Set the current for an example to 0.5A then see the MCU readings in my case readings = 2.978V
           record these readings in the Batt1CurrentPoints List with respect to corresponding currents in 
           correspondingIBatt1 list.
         - Don't forget to calibrate zero ampare point first.
         - Repeat this step with different loads until reaching an accurate readings in LCD equal to 
           ammeter in our available current range, in my case is 0-1A range.
         - Make this calibration method for both batteries in both polarities!!.

       For Set Point readings:
         - Connect the power supply to battery terminals with accurate ammeter in series.
         - Set a point with potitiometer in PCB and monitor the current on the ammeter 
         - Then record ammeter readings for examble 0.25A then see the MCU readings in my case readings = 0.248V
           record these readings in the Set1CurrentPoints List with respect to corresponding currents in 
           correspondingISet1 list.
         - Don't forget to calibrate zero ampare point first.
         - Repeat these steps for both battery slots.
         */

}


void channel1_calc(){
  if(CHG1 == 1){
    if(VBatt1 >= 2 && IBatt1Low == 0){
      digitalWrite(CHG1_en, HIGH);
    
      // Calculate the elapsed time in seconds
      unsigned long currentMillis1 = millis();
      float elapsedTime = (currentMillis1 - lastTime1) / 1000.0;  // Time in seconds
      lastTime1 = currentMillis1;
      // Calculate the capacity in mAh
      float currentCapacity_mAh = (IBatt1 * 1000 * elapsedTime) / 3600.0;  // (mA * seconds) / 3600 = mAh
      Capacity1 += currentCapacity_mAh;
      unsigned long elapsedSeconds = (currentMillis1 - startTime1) / 1000.0; // Time in seconds
      hours1 = elapsedSeconds / 3600;
      minutes1 = (elapsedSeconds % 3600) / 60;
      seconds1 = elapsedSeconds % 60;
      if(seconds1 > 5 && IBatt1 < 0.1){IBatt1Low = 1;}
    }
    else{
      digitalWrite(CHG1_en, LOW);
      tft.fillRect(58, 190, 52, 17, ST77XX_BLACK);
      tft.setFont(&FreeSerif12pt7b);    // Set a custom font
      tft.setTextSize(0);
      tft.setTextColor(ST77XX_MAGENTA);
      tft.setCursor(58, 205);
      tft.print("Done");
      CHG1 = 0;
      IBatt1Low = 0;
    }
  }
  if(DSG1 == 1){
    if(VBatt1 >= Batt_Low){
      digitalWrite(DSG1_en, LOW);
    
      // Calculate the elapsed time in seconds
      unsigned long currentMillis1 = millis();
      float elapsedTime = (currentMillis1 - lastTime1) / 1000.0;  // Time in seconds
      lastTime1 = currentMillis1;
      // Calculate the capacity in mAh
      float currentCapacity_mAh = (IBatt1 * 1000 * elapsedTime) / 3600.0;  // (mA * seconds) / 3600 = mAh
      Capacity1 += currentCapacity_mAh;
      unsigned long elapsedSeconds = (currentMillis1 - startTime1) / 1000.0; // Time in seconds
      hours1 = elapsedSeconds / 3600;
      minutes1 = (elapsedSeconds % 3600) / 60;
      seconds1 = elapsedSeconds % 60;
    }
    else{
      digitalWrite(DSG1_en, HIGH);
      tft.fillRect(58, 190, 52, 17, ST77XX_BLACK);
      tft.setFont(&FreeSerif12pt7b);    // Set a custom font
      tft.setTextSize(0);
      tft.setTextColor(ST77XX_MAGENTA);
      tft.setCursor(58, 205);
      tft.print("Done");
      DSG1 = 0;
    }
  }
}

void channel2_calc(){
  if(CHG2 == 1){
    if(VBatt2 >= 2 && IBatt2Low == 0){
      digitalWrite(CHG2_en, HIGH);
    
      // Calculate the elapsed time in seconds
      unsigned long currentMillis2 = millis();
      float elapsedTime = (currentMillis2 - lastTime2) / 1000.0;  // Time in seconds
      lastTime2 = currentMillis2;
      // Calculate the capacity in mAh
      float currentCapacity_mAh = (IBatt2 * 1000 * elapsedTime) / 3600.0;  // (mA * seconds) / 3600 = mAh
      Capacity2 += currentCapacity_mAh;
      unsigned long elapsedSeconds = (currentMillis2 - startTime2) / 1000.0; // Time in seconds
      hours2 = elapsedSeconds / 3600;
      minutes2 = (elapsedSeconds % 3600) / 60;
      seconds2 = elapsedSeconds % 60;
      if(seconds2 > 5 && IBatt2 < 0.1){IBatt2Low = 1;}
    }
    else{
      digitalWrite(CHG2_en, LOW);
      tft.fillRect(182, 190, 53, 17, ST77XX_BLACK);
      tft.setFont(&FreeSerif12pt7b);    // Set a custom font
      tft.setTextSize(0);
      tft.setTextColor(ST77XX_MAGENTA);
      tft.setCursor(182, 205);
      tft.print("Done");
      CHG2 = 0;
      IBatt2Low = 0;
    }
  }
  if(DSG2 == 1){
    if(VBatt2 >= Batt_Low){
      digitalWrite(DSG2_en, LOW);
    
      // Calculate the elapsed time in seconds
      unsigned long currentMillis2 = millis();
      float elapsedTime = (currentMillis2 - lastTime2) / 1000.0;  // Time in seconds
      lastTime2 = currentMillis2;
      // Calculate the capacity in mAh
      float currentCapacity_mAh = (IBatt2 * 1000 * elapsedTime) / 3600.0;  // (mA * seconds) / 3600 = mAh
      Capacity2 += currentCapacity_mAh;
      unsigned long elapsedSeconds = (currentMillis2 - startTime2) / 1000.0; // Time in seconds
      hours2 = elapsedSeconds / 3600;
      minutes2 = (elapsedSeconds % 3600) / 60;
      seconds2 = elapsedSeconds % 60;
    }
    else{
      digitalWrite(DSG2_en, HIGH);
      tft.fillRect(182, 190, 53, 17, ST77XX_BLACK);
      tft.setFont(&FreeSerif12pt7b);    // Set a custom font
      tft.setTextSize(0);
      tft.setTextColor(ST77XX_MAGENTA);
      tft.setCursor(182, 205);
      tft.print("Done");
      DSG2 = 0;
    }
  }
}
