#include <DHT.h>              //DTH Library
#include <DHT_U.h>            //DTH Library

#define DHTPIN 6                    //what pin we're connected to DTH Sensor
#define DHTTYPE DHT22                //DHT 11

DHT dht(DHTPIN, DHTTYPE);            //DTH Object Declaration

#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); //TX RX


void setup() {
  dht.begin();
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {

  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  // Read humidity
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

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
  Serial.println("Transmitter...");
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


  //float example = 33.546600;
  //float example = 75.456912;
  String buf;
  buf += F("TC: ");
  buf += String(t, 2);
  buf += F(" TF: ");
  buf += String(f, 2);

  buf += F(" IC: ");
  buf += String(hic, 2);
  buf += F(" IF: ");
  buf += String(hif, 2);


  //Serial.println(buf);
  mySerial.println(buf);//send a string on button press
  delay(1000);//delay little for better serial communication


}
