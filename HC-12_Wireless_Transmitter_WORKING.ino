// Wireless Transmitter, built date: 02.18.2019

#include <SoftwareSerial.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 6                     // DHT22 Pin
#define DHTTYPE DHT22                // DHT22

DHT dht(DHTPIN, DHTTYPE);            // DTH Object Declaration

SoftwareSerial mySerial(3, 2);       // HC-12 TX, HC-12 RX

void setup() {
  dht.begin();
  Serial.begin(9600);
  delay(100);
  Serial.println("Transmitter...");
  mySerial.begin(9600);
}

void loop() {

  delay(2000);   // Send signal every 1 minute

  // Read humidity
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  //float a = 00;

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  // Print DTH11 Values in Serial Monitor
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C | "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C | "));
  Serial.print(hif);
  Serial.println(F("°F"));

  /*
    // Combines values into one string
    String buf;
    //buf += F("PP");
    //buf += String(a, 2);
    buf += F("HM: ");
    buf += String(h, 2);
    buf += F(" TC: ");
    buf += String(t, 2);
    buf += F(" TF: ");
    buf += String(f, 2);
    buf += F(" IC: ");
    buf += String(hic, 2);
    buf += F(" IF: ");
    buf += String(hif, 2);
  */


  String buf1;
  String buf2;
  String buf3;
  buf1 += F("HM: ");        // Humidity
  buf1 += String(h, 2);
  buf2 += F("TC: ");        // Temperature in Celsis
  buf2 += String(t, 2);
  buf3 += F("TF: ");        // Temperature in Fahrenheit
  buf3 += String(f, 2);


  mySerial.println(buf1);      // Send a string on button press
  Serial.print("Sending "); Serial.println(buf1);
  delay(2000);
  mySerial.println(buf2);      // Send a string on button press
  Serial.print("Sending "); Serial.println(buf2);
  delay(2000);
  mySerial.println(buf3);      // Send a string on button press
  Serial.print("Sending "); Serial.println(buf3);
  delay(2000);                // Delay little for better serial communication
}
