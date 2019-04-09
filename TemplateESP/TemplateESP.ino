// WiFi
#include <WiFi.h> //Wifi library
#include "AvansWiFi.h"
// Temprature
#include <OneWire.h>
#include <DallasTemperature.h>
// Delay
#include "MillisDelay.h"


// __EDIT__ Eduroam info
#define USERNAME "username@avans.nl" //Eduroam username <<>>@avans.nl
#define PASSWORD "password" //your Eduroam password
AvansWiFi avansWifi("eduroam", USERNAME, PASSWORD); // Helper class for Avans WiFi

// Webserver on port 80 (default)
WebServer server(80);


// LED Settings
bool ledStatus = false; // status
#define ledPin 21 // Internal led pin
MillisDelay ledDelay;

// Temprature sensor
// Data wire is plugged into pin 
#define ONE_WIRE_BUS 26 // A0
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
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

  // WiFi is not connected
  if (!avansWifi.isConnected()) {
      avansWifi.connect(); // Reconnect to WiFi
  } else { 
      // We are connected, so we can do anything!
      //delay(250);
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
}
