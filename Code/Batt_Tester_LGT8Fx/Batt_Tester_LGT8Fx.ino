// Code Created by Make 2 Fix (Eng.Ahmed Hafez)
//18/09/2024

#include <avr/io.h>
#include <avr/interrupt.h>
#include <Adafruit_GFX.h>           // Core graphics library
#include <Adafruit_ST7789.h>        // Hardware-specific library for ST7789
#include <SPI.h>                    // Arduino SPI library
#include <Fonts/FreeSerif12pt7b.h>  // Add a custom font
#include <OneButton.h>

// ST7789 TFT module connections
#define TFT_CS   10  // define chip select pin
#define TFT_DC   6   // define data/command pin
#define TFT_RST  7   // define reset pin, or set to -1 and connect to Arduino RESET pin
//  SDA to pin 11
//  SCL to pin 13

#define CH1_mode   9   // define button to control channel 1
#define CH2_mode   8   // define button to control channel 2
#define CHG1_en    4
#define CHG2_en    2
#define DSG1_en    5
#define DSG2_en    3


// Analog Pin Config
#define V1P     17
#define V2P     16
#define I1P     A7
#define I2P     A6
#define I1_setP 14
#define I2_setP 15

// Initialize Adafruit ST7789 TFT library

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation.

// To use this mode we have to modify Adafruit-GFX-Library as shown in the
// following link:
// https://github.com/adafruit/Adafruit-GFX-Library/pull/313

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


// OPTION 2 lets you interface the display using ANY TWO or THREE PINS,
// tradeoff being that performance is not as fast as hardware SPI above.
#define TFT_MOSI 11  // Data out
#define TFT_CLK 13  // Clock out

//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK,TFT_RST);   // Uncomment to use option 2

float p = 3.1415926;

// Define the reference voltage for the Arduino (usually 5V)
const float referenceVoltage = 5.00;

// Number of calibration points
const int numPointsVBatt1 = 8; 
const int numPointsVBatt2 = 8; 
const int numPointsIBatt1 = 12; 
const int numPointsIBatt2 = 12; 
const int numPointsISet1  = 7; 
const int numPointsISet2  = 7; 




// Calibration points
float Batt1VoltagePoints[]  = {0.0, 0.503,  0.751,  1.00,   1.506,  1.755,  2.008,  2.256};
float correspondingVBatt1[] = {0.0, 1.009,  1.500,  2.001,  3.002,  3.500,  4.001,  4.500};

float Batt2VoltagePoints[]  = {0.0, 0.501,  0.747,  0.997,  1.504,  1.754,  2.007,  2.256};
float correspondingVBatt2[] = {0.0, 1.009,  1.500,  2.001,  3.002,  3.500,  4.001,  4.500};

float Batt1CurrentPoints[]  = {1.431, 1.691,  1.951,  2.209,  2.365,  2.465, 2.571,  2.726,  2.978,  3.235,  3.491,  3.574};
float correspondingIBatt1[] = {1.00,  0.750,  0.500,  0.250,  0.100,  0.0,   0.100,  0.250,  0.500,  0.750,  1.000,  1.080};

float Batt2CurrentPoints[]  = {1.432, 1.701,  1.962,  2.212,  2.364,  2.469, 2.585,  2.736,  2.990,  3.249,  3.509,  3.568};
float correspondingIBatt2[] = {1.00,  0.750,  0.500, 0.250,  0.100,  0.0,   0.100,  0.250,  0.500,  0.750,  1.000,  1.060};

float Set1CurrentPoints[]   = {0.0,  0.094,  0.248,  0.505,  0.766,  1.033,  1.605};
float correspondingISet1[]  = {0.0,  0.100,  0.250,  0.500,  0.750,  1.000,  1.500};

float Set2CurrentPoints[]   = {0.0,  0.091,  0.246,  0.504,  0.770,  1.031,  1.585};
float correspondingISet2[]  = {0.0,  0.100,  0.250,  0.500,  0.750,  1.000,  1.500};

// The more point is taken the more accurate measured values,but with more memory usage.


//variables
float VBatt1  = 0;
float VBatt2  = 0;
float IBatt1  = 0; 
float IBatt2  = 0;
float ISet1   = 0;
float ISet2   = 0; 
float Capacity1 = 0;
float Capacity2 = 0;
float Batt_Low  = 2.9; 
unsigned long previousMillis = 0;
unsigned long loop_delay = 100;
unsigned long currentMillis = 0;
unsigned long lastTime1  = 0;
unsigned long lastTime2  = 0;
unsigned long startTime1 = 0;
unsigned long startTime2 = 0;
int hours1   = 0;
int minutes1 = 0;
int seconds1 = 0;
int hours2   = 0;
int minutes2 = 0;
int seconds2 = 0;

//LCD Latching Parameters
bool PrintedBatt1 = 0;
bool PrintedBatt2 = 0;
bool PrintedRev1  = 0;
bool PrintedRev2  = 0;
bool PrintedV1 = 0;
bool PrintedV2 = 0;
bool PrintedA1 = 0;
bool PrintedA2 = 0;
bool PrintedmA1 = 0;
bool PrintedmA2 = 0;
bool IBatt1Low = 0;
bool IBatt2Low = 0;
bool mod1 = 0;
bool mod2 = 0;
bool CHG1 = 0;
bool CHG2 = 0;
bool DSG1 = 0;
bool DSG2 = 0;


OneButton button1;
OneButton button2;


void setup() {
  // setup OneButton
  Serial.begin(9600);               //for testing
  pinMode(CHG1_en, OUTPUT);
  pinMode(CHG2_en, OUTPUT);
  pinMode(DSG1_en, OUTPUT);
  pinMode(DSG2_en, OUTPUT);
  button1.setup(CH1_mode, INPUT_PULLUP, true);
  button2.setup(CH2_mode, INPUT_PULLUP, true);

  digitalWrite(DSG1_en, HIGH);
  digitalWrite(DSG2_en, HIGH);
  analogReadResolution(12);         // Changing the ADC resolution to 12 bit

  // link the button 1 functions.
  button1.attachClick(click1);
  button1.attachDoubleClick(doubleclick1);
  button1.attachLongPressStart(longPressStart1);
  // link the button 2 functions.
  button2.attachClick(click2);
  button2.attachDoubleClick(doubleclick2);
  button2.attachLongPressStart(longPressStart2);
  
  // if the display has CS pin try with SPI_MODE0
  tft.init(240, 240, SPI_MODE0);    // Init ST7789 display 240x240 pixel

  tft.setRotation(2);               // if the screen is flipped, remove this command
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setFont(&FreeSerif12pt7b);    // Set a custom font
  tft.setTextSize(0);               // Set text size. We are using custom font so you should always set text size as 0
  tft.setCursor(20, 70);            // Set position (x,y)
  tft.setTextColor(ST77XX_WHITE);   // Set color of text. We are using custom font so there is no background color supported
  tft.println("Battery Tester");    // Print a text or value
  tft.setCursor(25, 120);
  tft.print("Smile Dude :)");
  delay(1000); 
  tft.setCursor(160, 220);
  tft.print("M2F"); 
  delay(500);
  tft.fillScreen(ST77XX_BLACK);
  tft.setFont(&FreeSerif12pt7b);    // Set a custom font
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(0, 20);
  tft.print("Channel1");
  tft.setCursor(125, 20);
  tft.print("Channel2");
  
  tft.setTextColor(0x0638);
  tft.setCursor(5, 155);
  tft.print("Iset:");
  tft.setCursor(128, 155);
  tft.print("Iset:");
  tft.setCursor(4, 180);
  tft.print("mode:");
  tft.setCursor(128, 180);
  tft.print("mode:");
  tft.setCursor(5, 205);
  tft.print("state:");
  tft.setCursor(128, 205);
  tft.print("state:");
  
  
  tft.setTextColor(0xDF00);
  tft.setCursor(70, 122);
  tft.print("mAh");
  tft.setCursor(194, 122);
  tft.print("mAh");
  tft.setTextColor(0xFB36);
  tft.setCursor(64, 180);
  tft.print("DSG");
  tft.setCursor(188, 180);
  tft.print("DSG");
  
  


  tft.drawRoundRect(0, 134, 117, 78, 10, ST77XX_WHITE);
  tft.drawRoundRect(123, 134, 117, 78, 10, ST77XX_WHITE);
  tft.drawFastVLine(119, 0, 240, ST77XX_WHITE);
  tft.drawFastVLine(120, 0, 240, ST77XX_WHITE);
}



void loop() {
  // keep watching the push button:
  button1.tick();
  button2.tick();
  currentMillis = millis();
  channel1_calc();
  channel2_calc();
  if (currentMillis - previousMillis >= loop_delay)
  {
    get_values();
    display_data();
    previousMillis = currentMillis;
  } 
}
