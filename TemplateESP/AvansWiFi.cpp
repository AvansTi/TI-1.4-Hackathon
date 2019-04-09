#include <WiFi.h> //Wifi library
#include "AvansWiFi.h"

AvansWiFi::AvansWiFi(const char* ssid, const char* username, const char* password) :
	ssid(ssid), username(username), password(password) 
{
		
}

void AvansWiFi::connect() {
	
	Serial.print("Connecting to network: ");
	Serial.println(ssid);
	
	WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
	WiFi.mode(WIFI_STA); //init wifi mode
	esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)username, strlen(username)); //provide identity
	esp_wifi_sta_wpa2_ent_set_username((uint8_t *)username, strlen(username)); //provide username --> identity and username is same
	esp_wifi_sta_wpa2_ent_set_password((uint8_t *)password, strlen(password)); //provide password
	esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT(); //set config settings to default
	esp_wifi_sta_wpa2_ent_enable(&config); //set config settings to enable function
	WiFi.begin(ssid); //connect to wifi
	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.print(".");
		counter++;
		if(counter>=60){ //after 60 seconds timeout - reset board
			ESP.restart();
		}
	}
  
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.print("IP address set: "); 
	Serial.println(WiFi.localIP());
}

bool AvansWiFi::isConnected() {
	return (WiFi.status() == WL_CONNECTED);
}

