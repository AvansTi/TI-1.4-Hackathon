// Temprature
#include <OneWire.h>
#include <DallasTemperature.h>
// Delay
#include "MillisDelay.h"



// LED Settings
bool ledStatus = false; // status
#define ledPin 21 // Internal led pin
MillisDelay ledDelay;

// Temprature sensor
// Data wire is plugged into pin 
#define ONE_WIRE_BUS 26 // A0
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
MillisDelay tempratureDelay;


void toggleLed() {
  ledStatus = !ledStatus;
  digitalWrite(ledPin, ledStatus);
}

float getTemprature() {
  DS18B20.requestTemperatures(); 
  float tempC = DS18B20.getTempCByIndex(0);
  return tempC;
}

void setup() {

  pinMode(ledPin, OUTPUT);

  // Open serial connection for debugging
  Serial.begin(115200);
  delay(10);

  
  // Connect to WiFi
  avansWifi.connect();

  ledDelay.start(250);
  tempratureDelay.start(1000);
}

void loop() {

    if (tempratureDelay.isFinished()) {
		Serial.print("Current temprature: ");
        Serial.println(getTemprature());
        tempratureDelay.restart();
    }
    if (ledDelay.isFinished()) {
		toggleLed();
        ledDelay.restart();
    }      
}
