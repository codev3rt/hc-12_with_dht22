// Wireless Receiver, built date: 02.18.2019

#include <SoftwareSerial.h>

SoftwareSerial myReceiver(50, 51);    // HC-12 TX, HC-12 RX

// IMPORTANT: ELEGOO_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Elegoo_TFTLCD.h FOR SETUP.
//Technical support:goodtft@163.com

#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
//#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Elegoo_TFTLCD tft;

//Variables
unsigned long startMillis;           //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 1000;   //the value is a number of milliseconds

void setup() {

  Serial.begin(9600);
  delay(100);
  Serial.println("Receiver...");
  myReceiver.begin(9600);
  readTempSensor();      // Read DHT22 Sensor Wirelessly
  startMillis = millis();  // Initial start time

  Serial.println(F("TFT LCD test"));

#ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.4\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Elegoo 2.4\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = tft.readID();
  if (identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if (identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if (identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  } else if (identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if (identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if (identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if (identifier == 0x0101)
  {
    identifier = 0x9341;
    Serial.println(F("Found 0x9341 LCD driver"));
  }
  else if (identifier == 0x1111)
  {
    identifier = 0x9328;
    Serial.println(F("Found 0x9328 LCD driver"));
  }
  else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier = 0x9328;

  }
  tft.begin(identifier);
  tft.setRotation(3);
  tft.fillScreen(BLACK);

}

void loop() {

  // Start Timing to next temperature read
  currentMillis = millis();
  if (currentMillis - startMillis >= period)
  {
    readTempSensor();
    startMillis = currentMillis;  //IMPORTANT to save the start time of the current .
  }
}


void  readTempSensor() {

  String input = myReceiver.readString();   // Read string

  // Display Text on top of the LCD
  tft.setCursor(28, 10);
  tft.setTextColor(RED);  tft.setTextSize(2);
  tft.println("OUTDOOR TEMPERATURE");
  tft.drawLine(10, 35, 310, 35, WHITE);


  // Temperatue in Celsius
  if (input.substring(0, 2) == "TC") {

    String TemperatureC = input.substring(4, 10);         // All characters between 4 and 10
    int TC = TemperatureC.toInt();                        // Convert Celsius from input.substring to integer for final Display

    if (TC >= 1) {
      tft.setTextColor(WHITE); tft.setTextSize(6);
      tft.setCursor(28, 50);
      tft.println("C");
      tft.fillRect(100, 46, 210, 50, RED);
      tft.setTextColor(BLACK);
      tft.setCursor(200, 50);
      tft.println(TC);

      tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.setCursor(60, 45);
      tft.println((char)223);
    }
    else {
      // If Temperature drops below 0, change display to Blue
      tft.setTextColor(WHITE); tft.setTextSize(6);
      tft.setCursor(28, 50);
      tft.println("C");
      tft.fillRect(100, 46, 210, 50, BLUE);
      tft.setTextColor(BLACK);
      tft.setCursor(200, 50);
      tft.println(TC);

      tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.setCursor(60, 45);
      tft.println((char)223);
    }
  }

  // Temperatue in Fahrenheit
  if (input.substring(0, 2) == "TF") {

    String TemperatureF = input.substring(4, 10);         // All characters between 4 and 10
    int TF = TemperatureF.toInt();                        // Convert Fahrenheit from input.substring to integer for final Display

    if (TF >= 33) {
      tft.setTextColor(WHITE); tft.setTextSize(6);
      tft.setCursor(28, 110);
      tft.println("F");
      tft.fillRect(100, 106, 210, 50, RED);
      tft.setTextColor(BLACK);
      tft.setCursor(200, 110);
      tft.println(TF);

      tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.setCursor(60, 105);
      tft.println((char)223);
    }
    // If Temperature drops below 33, change display to Blue
    else {
      tft.setTextColor(WHITE); tft.setTextSize(6);
      tft.setCursor(28, 110);
      tft.println("F");
      tft.fillRect(100, 106, 210, 50, BLUE);
      tft.setTextColor(BLACK);
      tft.setCursor(200, 110);
      tft.println(TF);

      tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.setCursor(60, 105);
      tft.println((char)223);
    }
  }
  if (input.substring(0, 2) == "HM") {

    String Humidity = input.substring(4, 10);         // All characters between 4 and 10
    int HM = Humidity.toInt();                        // Convert Humidity from input.substring to integer for final Display

    tft.setTextColor(WHITE); tft.setTextSize(6);
    tft.setCursor(28, 170);
    tft.println("%");
    tft.fillRect(100, 166, 210, 50, RED);
    tft.setTextColor(BLACK);
    tft.setCursor(200, 170);
    tft.println(HM);
  }
}
