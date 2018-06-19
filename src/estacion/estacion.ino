#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>
#include <SD.h>
#include <SPI.h>
#include "config.h"

int tiempo = 0;
int pinCS = 53;
int pinDht11 = 13;
File myFile;
DHT11 dht11(pinDht11); 
LiquidCrystal_I2C lcd(0x27, 16, 2);
DS3231  Clock;
Stream *esp8266 = &Serial3;

bool Century = false;
bool h12 = false;
bool PM = false;
int pinLDR = A5;
int pinBoton = 3;
int escritos = 0;
/*Manejo de delays*/
#define INTERVALO_ENVIO 60000
#define INTERVALO_PANTALLA_ENC 30000
#define INTERVALO_PANTALLA_ACT 5000
unsigned long t_envio = 0;
unsigned long t_pantalla_enc = 0;
unsigned long t_pantalla_act = 0;
unsigned long actual;

void setup() {
    Serial.begin(115200);
    Serial3.begin(115200);

    pinMode(pinBoton, INPUT);
    pinMode (pinLDR, INPUT);
    
    Wire.begin();
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.print("Temp");
    lcd.setCursor(13,0);
    lcd.print("Hum");
    SD.begin();
    
    esp8266-> setTimeout(15000);

    delay (1000);
    Serial.println ("Inicializar WIFI");
    wifi_init_client (esp8266);
 
    Serial.println ("Conectar a Red");
    wifi_connect_ssid (esp8266, WIFI_SSID, WIFI_PASSWORD);
    
    Serial.print("Time: ");
    actual = millis();
    Serial.println(actual);    //prints time since program started
}

void loop() {
    float temp, hum;
    int lum;
    char* fecha;
    char* hora;
    char post_data[1024];
    
    chequear_boton();
    if (transcurrio_tiempo(t_envio, INTERVALO_ENVIO)) { // se mandan datos cada 60 segundos
        if ( dht11.read(hum, temp) == 0 ) {    // Si devuelve 0 es que leyo bien
            mostrar_dht11(temp, hum);
            fecha = get_fecha();
            hora = get_hora();
            mostrar_hora(fecha);
            lum = medicion_luminosidad();
            guardar_sd(fecha, hora, temp, hum, lum);
            sprintf (post_data, "luminosidad=%d&temperatura=%d&humedad=%d&fecha=%s&hora=%s",lum, (int) temp, (int) hum, fecha, hora);
            http_post (esp8266, SERVER_HOST, SERVER_PORT, SERVER_RESOURCE, post_data);
            free(fecha);
            free(hora);
        }
        actual = millis();
        t_envio = actual;
    }
    
    if (transcurrio_tiempo(t_pantalla_act, INTERVALO_PANTALLA_ACT)) {
        if ( dht11.read(hum, temp) == 0 ) {    // Si devuelve 0 es que leyo bien
            mostrar_dht11(temp, hum);
            fecha = get_fecha();
            mostrar_hora(fecha);
        }
        actual = millis();
        t_pantalla_act = actual;
    }
    delay(100); 
}

bool transcurrio_tiempo(unsigned long variable, unsigned long tiempo) {
    actual = millis();
    if ( ((actual - variable) > tiempo) || (actual < variable) ){
        return true;
    }
    return false;
}

void chequear_boton() {
    actual = millis();
    if (digitalRead(pinBoton) == HIGH) {
        lcd.backlight();
        lcd.display();
        t_pantalla_enc = actual;
    } else {
      if ( transcurrio_tiempo(t_pantalla_enc, INTERVALO_PANTALLA_ENC) ) {
          lcd.noBacklight();
          lcd.noDisplay();
      }
    }
}

void mostrar_dht11(float temp, float hum) {
    lcd.setCursor(0, 1);
    lcd.print((int) temp);
    lcd.print((char) 223);
    lcd.print("C");
    lcd.setCursor(13, 1);
    lcd.print((int) hum);
    lcd.print("%");
}

int medicion_luminosidad() {
    int lum;
    lum = 1023 - analogRead(pinLDR);
    return lum;
}

void guardar_sd(char* fecha, char* hora, float temp, float hum, int lum) {
    char medicion[256];
    sprintf (medicion, "%s,%s,%d,%d,%d", fecha, hora, (int) temp, (int) hum, lum);
    myFile = SD.open("STATION.CSV", FILE_WRITE);
    myFile.println (medicion);
    myFile.close();
}

char* get_hora() {
    char hora[9];
    sprintf (hora, "%02d:%02d:%02d", Clock.getHour(h12, PM), Clock.getMinute(), Clock.getSecond());
    return strdup(hora);
}

char* get_fecha() {
    char fecha[6];
    sprintf (fecha, "%02d/%02d", Clock.getDate(), Clock.getMonth(Century));
    return strdup(fecha);
}

void mostrar_hora(char* fecha) {
    lcd.setCursor(6, 0);
    lcd.print(fecha);
    lcd.setCursor(6, 1);
    lcd.print (Clock.getHour(h12,PM));
    lcd.print (":");
    lcd.print (Clock.getMinute());
}
