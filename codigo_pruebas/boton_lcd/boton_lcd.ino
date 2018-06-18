#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>
#include <SD.h>
#include <SPI.h>

File myFile;
int pinCS = 53;
int pinDht11 = 13;
DHT11 dht11(pinDht11); 
LiquidCrystal_I2C lcd(0x27, 16, 2);
DS3231  Clock;

bool Century = false;
bool h12 = false;
bool PM = false;
int pinLDR = A5;
int PULSADOR = 3;

void setup() { 
   pinMode(PULSADOR, INPUT);
   Wire.begin();
   lcd.init();
   lcd.backlight();
   lcd.clear();
   lcd.print("Temp"); // Enviar el mensaje
   lcd.setCursor(13,0);
   lcd.print("Hum");
   SD.begin();
}

int escritos = 0;

void loop() { 
   int err;
   float temp, hum;
   int lum;
   char fecha[6];
   char hora[9];
   char medicion[256];
   if ( (err = dht11.read(hum, temp) ) == 0 ) {    // Si devuelve 0 es que ha leido bien
      lcd.setCursor(0, 1);  // set the cursor to column 0, line 1
      lcd.print((int) temp);;
      lcd.print((char) 223);
      lcd.print("C");
      lcd.setCursor(13, 1);  // set the cursor to column 0, line 1
      lcd.print((int) hum);
      lcd.print("%");
      lcd.setCursor (6, 0);
      sprintf (fecha, "%02d/%02d", Clock.getDate(), Clock.getMonth(Century));
      lcd.print(fecha);
      lcd.setCursor(6, 1);
      sprintf (hora, "%02d:%02d:%02d", Clock.getHour(h12, PM), Clock.getMinute(), Clock.getSecond());
      lcd.print (Clock.getHour(h12,PM));
      lcd.print (":");
      lcd.print (Clock.getMinute());
      lum = 1023 - analogRead(pinLDR);
      sprintf (medicion, "%s,%s,%d,%d,%d", fecha, hora, (int) temp, (int) hum, lum);
      myFile = SD.open("STATION.CSV", FILE_WRITE);
      myFile.println (medicion);
      myFile.close();
   }
   if (digitalRead(PULSADOR) == HIGH) {
      lcd.backlight();
      lcd.display();
   } else {
      lcd.noBacklight();
      lcd.noDisplay();
   }
   delay(1000);
}
