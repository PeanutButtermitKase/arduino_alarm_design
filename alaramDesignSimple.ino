/*
Author @ Nydia R. Varela-Rosales
Version v1 2022

Description: Alarm upon presence is detected, laser points out towards 
intruder, sensor of humidity, temperature is always present

Requires:

- DHT sensor
- Buzzer
- obstacle sensor
- laser

*/

#include <Wire.h>
#include "DHT.h"
#define DHTPIN 3     // Digital pin connected to the DHT sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11    // DHT 11
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);
// initialize timer structure
const int buzzer = 9; // buzzer to arduino pin 9
const int lasser = 7; // laser 
// set obstacle detector 
int LED = 13; // Use the onboard Uno LED
int isObstaclePin = 2;  // This is our input pin
int isObstacle = HIGH;  // HIGH MEANS NO OBSTACLE
void setup() {
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(lasser, OUTPUT);  
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  // set obstacle inits 
  pinMode(LED, OUTPUT);
  pinMode(isObstaclePin, INPUT);
  dht.begin();
}
void loop() {
  // Wait a few seconds between measurements.
     // read obstacle 
   isObstacle = digitalRead(isObstaclePin);
   const int globalTime = 500;
   if (isObstacle == LOW) {
    tone(buzzer, 100); // Send 1KHz sound signal...
    delay(globalTime);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(globalTime);        // ...for 1sec
    digitalWrite(LED, HIGH);
    digitalWrite(lasser, HIGH);
    delay(globalTime);
    digitalWrite(lasser, LOW);
    delay(globalTime);
   }
  delay(1000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(h);
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  if (t >= 28) {
      tone(buzzer, 500); // Send 1KHz sound signal...
      delay(1000);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(1000);        // ...for 1sec
    }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}
