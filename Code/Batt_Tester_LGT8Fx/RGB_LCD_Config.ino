void display_data(){  
  
  // Voltages
  if(VBatt1 < 1.7 && VBatt1 > 1.3 && PrintedBatt1 == 0){
    tft.fillRect(0, 30, 116, 30, ST77XX_BLACK);
    tft.setFont(&FreeSerif12pt7b); 
    tft.setTextSize(0);
    tft.setCursor(0, 50);
    tft.setTextColor(ST77XX_MAGENTA);
    tft.print("NoBattery");
    PrintedBatt1 = 1;
    PrintedRev1 = 0;
    PrintedV1 = 0;
  }
  else if(VBatt1 < 1.2 && PrintedRev1 == 0){
    tft.fillRect(0, 30, 116, 30, ST77XX_BLACK);
    tft.setFont(&FreeSerif12pt7b); 
    tft.setTextSize(0);
    tft.setCursor(0, 50);
    tft.setTextColor(ST77XX_RED);
    tft.print("Reversed ");
    PrintedRev1 = 1;
    PrintedBatt1 = 0;
    PrintedV1 = 0;
  }
  else if(VBatt1 > 1.7){
    tft.setFont(); 
    tft.setCursor(0, 30);
    tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
    tft.setTextSize(4);
    tft.print(VBatt1,2);
    PrintedBatt1 = 0;
    PrintedRev1  = 0;
    if(PrintedV1 == 0){
      tft.setTextSize(0);
      tft.setFont(&FreeSerif12pt7b);   
      tft.setTextColor(ST77XX_GREEN);
      tft.setCursor(97, 55);
      tft.print("V");
      PrintedV1 = 1;
    }
  }
  if(VBatt2 < 1.7 && VBatt2 > 1.3 && PrintedBatt2 == 0){
    tft.fillRect(122, 30, 116, 30, ST77XX_BLACK);
    tft.setFont(&FreeSerif12pt7b); 
    tft.setTextSize(0);
    tft.setCursor(125, 50);
    tft.setTextColor(ST77XX_MAGENTA);
    tft.print("NoBattery");
    PrintedBatt2 = 1;
    PrintedRev2 = 0;
    PrintedV2 = 0;
  }
  else if(VBatt2 < 1.2 && PrintedRev2 == 0){
    tft.fillRect(122, 30, 116, 30, ST77XX_BLACK);
    tft.setFont(&FreeSerif12pt7b); 
    tft.setTextSize(0);
    tft.setCursor(125, 50);
    tft.setTextColor(ST77XX_RED);
    tft.print("Reversed ");
    PrintedRev2 = 1;
    PrintedBatt2 = 0;
    PrintedV2 = 0;
  }
  else if(VBatt2 > 1.7){
    tft.setFont(); 
    tft.setCursor(125, 30);
    tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
    tft.setTextSize(4);
    tft.print(VBatt2,2);
    PrintedBatt2 = 0;
    PrintedRev2 = 0;
    if(PrintedV2 == 0){
      tft.setTextSize(0);
      tft.setFont(&FreeSerif12pt7b);   
      tft.setTextColor(ST77XX_GREEN);
      tft.setCursor(221, 55);
      tft.print("V");
      PrintedV2 = 1;
    }
  }

  
  // Currents
  if(IBatt1 < 1){
    tft.setFont(); 
    tft.setCursor(0, 65);
    tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
    tft.setTextSize(4);
    tft.print(IBatt1*1000,0);
    if(IBatt1 < 0.1 && IBatt1 > 0.01){
      tft.fillRect(48, 65, 20, 30, ST77XX_BLACK);
    }
    else if(IBatt1 < 0.01){
      tft.setCursor(0, 65);
      tft.print("000");
    }
    if(PrintedmA1 == 0){
      tft.setTextSize(0);
      tft.fillRect(20, 65, 72, 30, ST77XX_BLACK);
      tft.setFont(&FreeSerif12pt7b);   
      tft.setTextColor(ST77XX_CYAN);
      tft.setCursor(78, 90);
      tft.print("mA");
      PrintedmA1 = 1;
      PrintedA1  = 0;
    }
  }
  else if(IBatt1 > 1){
    tft.setFont(); 
    tft.setCursor(0, 65);
    tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
    tft.setTextSize(4);
    tft.print(IBatt1,2);
    if(PrintedA1 == 0){
      tft.setTextSize(0);
      tft.setFont(&FreeSerif12pt7b);   
      tft.setTextColor(ST77XX_CYAN);
      tft.setCursor(97, 90);
      tft.print("A");
      PrintedA1  = 1;
      PrintedmA1 = 0;
    }
  }
  if(IBatt2 < 1){
    tft.setFont(); 
    tft.setCursor(125, 65);
    tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
    tft.setTextSize(4);
    tft.print(IBatt2*1000,0);
    if(IBatt2 < 0.1 && IBatt2 > 0.01){
      tft.fillRect(173, 65, 20, 30, ST77XX_BLACK);
    }
    else if(IBatt2 < 0.01){
      tft.setCursor(125, 65);
      tft.print("000");
    }
    if(PrintedmA2 == 0){
      tft.setTextSize(0);
      tft.fillRect(145, 65, 72, 30, ST77XX_BLACK);
      tft.setFont(&FreeSerif12pt7b);   
      tft.setTextColor(ST77XX_CYAN);
      tft.setCursor(202, 90);
      tft.print("mA");
      PrintedmA2 = 1;
      PrintedA2  = 0;
    }
  }
  else if(IBatt2 > 1){
    tft.setFont(); 
    tft.setCursor(125, 65);
    tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
    tft.setTextSize(4);
    tft.print(IBatt2,2);
    if(PrintedA2 == 0){
      tft.setTextSize(0);
      tft.setFont(&FreeSerif12pt7b);   
      tft.setTextColor(ST77XX_CYAN);
      tft.setCursor(221, 90);
      tft.print("A");
      PrintedA2  = 1;
      PrintedmA2 = 0;
    }
  }


  // Currents Setting
  tft.setFont();
  tft.setTextSize(2);
  tft.setCursor(55, 142);
  tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
  tft.print(ISet1,3);
  tft.setCursor(178, 142);
  tft.print(ISet2,3);


  // Capacity Printing
  if(Capacity1 < 1000 && Capacity1 > 100){
    tft.fillRect(54, 104, 15, 22, ST77XX_BLACK);
    tft.setFont();
    tft.setTextSize(3);
    tft.setTextColor(0xDF00, ST77XX_BLACK);
    tft.setCursor(0, 104);
    tft.print(Capacity1,0);
  }
  else if(Capacity1 < 100 && Capacity1 > 10){
    tft.fillRect(36, 104, 33, 22, ST77XX_BLACK);
    tft.setFont();
    tft.setTextSize(3);
    tft.setTextColor(0xDF00, ST77XX_BLACK);
    tft.setCursor(0, 104);
    tft.print(Capacity1,0);
  }
  else if(Capacity1 < 10){
    tft.fillRect(54, 104, 15, 22, ST77XX_BLACK);
    tft.setFont();
    tft.setTextSize(3);
    tft.setTextColor(0xDF00, ST77XX_BLACK);
    tft.setCursor(0, 104);
    tft.print(Capacity1,1);
  }
  else{
    tft.setFont();
    tft.setTextSize(3);
    tft.setTextColor(0xDF00, ST77XX_BLACK);
    tft.setCursor(0, 104);
    tft.print(Capacity1,0);
  }


  if(Capacity2 < 1000 && Capacity2 > 100){
    tft.fillRect(178, 104, 15, 22, ST77XX_BLACK);
    tft.setFont();
    tft.setTextSize(3);
    tft.setTextColor(0xDF00, ST77XX_BLACK);
    tft.setCursor(124, 104);
    tft.print(Capacity2,0);
  }
  else if(Capacity2 < 100 && Capacity2 > 10){
    tft.fillRect(160, 104, 33, 22, ST77XX_BLACK);
    tft.setFont();
    tft.setTextSize(3);
    tft.setTextColor(0xDF00, ST77XX_BLACK);
    tft.setCursor(124, 104);
    tft.print(Capacity2,0);
  }
  else if(Capacity2 < 10){
    tft.fillRect(178, 104, 15, 22, ST77XX_BLACK);
    tft.setFont();
    tft.setTextSize(3);
    tft.setTextColor(0xDF00, ST77XX_BLACK);
    tft.setCursor(124, 104);
    tft.print(Capacity2,1);
  }
  else{
    tft.setFont();
    tft.setTextSize(3);
    tft.setTextColor(0xDF00, ST77XX_BLACK);
    tft.setCursor(124, 104);
    tft.print(Capacity2,0);
  }

  // Time Printing
  tft.setFont();    // Set a custom font
  tft.setTextSize(2);
  tft.setCursor(12, 220);
  tft.setTextColor(ST77XX_ORANGE,ST77XX_BLACK);
  tft.print("0");
  tft.print(hours1);
  tft.print(":");
  if(minutes1 < 10){
    tft.print("0");
    tft.print(minutes1);
  }else{tft.print(minutes1);}
  tft.print(":");
  if(seconds1 < 10){
    tft.print("0");
    tft.print(seconds1);
  }else{tft.print(seconds1);}
  tft.setCursor(134, 220);
  tft.print("0");
  tft.print(hours2);
  tft.print(":");
  if(minutes2 < 10){
    tft.print("0");
    tft.print(minutes2);
  }else{tft.print(minutes2);}
  tft.print(":");
  if(seconds2 < 10){
    tft.print("0");
    tft.print(seconds2);
  }else{tft.print(seconds2);}
}



// ----- button 1 callback functions

// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).
void click1() {
  if(mod1 == 0 && DSG1 == 0){
    tft.fillRect(65, 165, 50, 17, ST77XX_BLACK);
    tft.setFont(&FreeSerif12pt7b);    // Set a custom font
    tft.setTextSize(0);
    tft.setTextColor(0x05C0);
    tft.setCursor(64, 180);
    tft.print("CHG");
    mod1 = 1;
  }
  else if(mod1 == 1 && CHG1 == 0){
    tft.fillRect(65, 165, 50, 17, ST77XX_BLACK);
    tft.setFont(&FreeSerif12pt7b);    // Set a custom font
    tft.setTextSize(0);
    tft.setTextColor(0xFB36);
    tft.setCursor(64, 180);
    tft.print("DSG");
    mod1 = 0;
  }
}  // click1


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick1() {
  if(CHG1 == 0 && DSG1 == 0){
    Capacity1 = 0;
  }
}  // doubleclick1


// This function will be called once, when the button1 is pressed for a long time.
void longPressStart1() {
  if(CHG1 == 0 && DSG1 == 0 && mod1 == 1 && VBatt1 >= 2){
    tft.fillRect(58, 190, 53, 17, ST77XX_BLACK);
    delay(10);
    tft.setFont(&FreeSerif12pt7b);    // Set a custom font
    tft.setTextSize(0);
    tft.setTextColor(ST77XX_RED);
    tft.setCursor(61, 205);
    tft.print("CHG");
    CHG1 = 1;
    lastTime1 = millis();
    startTime1 = millis();
  }
  else if(CHG1 == 0 && DSG1 == 0 && mod1 == 0 && VBatt1 >= Batt_Low){
    tft.fillRect(58, 190, 53, 17, ST77XX_BLACK);
    delay(10);
    tft.setFont(&FreeSerif12pt7b);    // Set a custom font
    tft.setTextSize(0);
    tft.setTextColor(ST77XX_RED);
    tft.setCursor(64, 205);
    tft.print("DSG");
    DSG1 = 1;
    lastTime1  = millis();
    startTime1 = millis();
  }
  else{
    digitalWrite(CHG1_en, LOW);
    digitalWrite(DSG1_en, HIGH);
    tft.fillRect(58, 190, 52, 17, ST77XX_BLACK);
    delay(10);
    tft.setFont(&FreeSerif12pt7b);    // Set a custom font
    tft.setTextSize(0);
    tft.setTextColor(ST77XX_MAGENTA);
    tft.setCursor(58, 205);
    tft.print("Done");
    CHG1 = 0;
    DSG1 = 0;
  }
}  // longPressStart1




// ... and the same for button 2:

void click2() {
  if(mod2 == 0 && DSG2 == 0){
    tft.fillRect(188, 165, 50, 17, ST77XX_BLACK);
    tft.setFont(&FreeSerif12pt7b);    // Set a custom font
    tft.setTextSize(0);
    tft.setTextColor(0x05C0);
    tft.setCursor(188, 180);
    tft.print("CHG");
    mod2 = 1;
  }
    else if(mod2 == 1 && CHG2 == 0){
    tft.fillRect(189, 165, 50, 17, ST77XX_BLACK);
    tft.setFont(&FreeSerif12pt7b);    // Set a custom font
    tft.setTextSize(0);
    tft.setTextColor(0xFB36);
    tft.setCursor(188, 180);
    tft.print("DSG");
    mod2 = 0;
  }
}  // click2


void doubleclick2() {
  if(CHG2 == 0 && DSG2 == 0){
    Capacity2 = 0;
  }
}  // doubleclick2


void longPressStart2() {
  if(CHG2 == 0 && DSG2 == 0 && mod2 == 1 && VBatt2 >= 2){
    tft.fillRect(182, 190, 53, 17, ST77XX_BLACK);
    delay(10);
    tft.setFont(&FreeSerif12pt7b);    // Set a custom font
    tft.setTextSize(0);
    tft.setTextColor(ST77XX_RED);
    tft.setCursor(185, 205);
    tft.print("CHG");
    CHG2 = 1;
    lastTime2 = millis();
    startTime2 = millis();
  }
  else if(CHG2 == 0 && DSG2 == 0 && mod2 == 0 && VBatt2 >= Batt_Low){
    tft.fillRect(182, 190, 53, 17, ST77XX_BLACK);
    delay(10);
    tft.setFont(&FreeSerif12pt7b);    // Set a custom font
    tft.setTextSize(0);
    tft.setTextColor(ST77XX_RED);
    tft.setCursor(186, 205);
    tft.print("DSG");
    DSG2 = 1;
    lastTime2 = millis();
    startTime2 = millis();
  }
  else{
    digitalWrite(CHG2_en, LOW);
    digitalWrite(DSG2_en, HIGH);
    tft.fillRect(182, 190, 53, 17, ST77XX_BLACK);
    delay(10);
    tft.setFont(&FreeSerif12pt7b);    // Set a custom font
    tft.setTextSize(0);
    tft.setTextColor(ST77XX_MAGENTA);
    tft.setCursor(182, 205);
    tft.print("Done");
    CHG2 = 0;
    DSG2 = 0;
  }
}  // longPressStart2
