#include "esp_wpa2.h" //wpa2 library for connections to Enterprise networks

class AvansWiFi {
	
	public:
		AvansWiFi(const char* ssid, const char* username, const char* password);
		
		void connect();
		bool isConnected();
	
	
	private:
		const char* ssid;
		const char* username;
		const char* password;
		int counter;
	
};