#define PIN_LUM A0
#include "config.h"

Stream *esp8266 = &Serial3;

void setup()	{
	pinMode (PIN_LUM, INPUT);

	Serial.begin(115200);
	Serial3.begin(115200);
	esp8266-> setTimeout(15000);

	delay (1000);
	Serial.println ("Inicializar WIFI");
	wifi_init_client (esp8266);
	
	Serial.println ("Conectar a Red");
	wifi_connect_ssid (esp8266, WIFI_SSID, WIFI_PASSWORD);
}

void loop() {
	Serial.println ("Enviar datos via http");
	char post_data[1024];
	int luminosidad = analogRead (PIN_LUM);

	sprintf (post_data, "luminosidad=%d", (int)(((luminosidad)*100)/1023));
	http_post (esp8266, SERVER_HOST, SERVER_PORT, SERVER_RESOURCE, post_data);
	delay (5000);
}

