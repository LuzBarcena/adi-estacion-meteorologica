#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>

int pinDht11 = 13;
DHT11 dht11(pinDht11); 
LiquidCrystal_I2C lcd(0x27, 16, 2);
DS3231  Clock;

bool Century = false;
bool h12 = false;
bool PM = false;

void setup() { 
   Wire.begin();
   lcd.init();
   lcd.backlight();
   lcd.clear();
   lcd.print("Temp"); // Enviar el mensaje
   lcd.setCursor(13,0);
   lcd.print("Hum");
}

void loop() { 
   int err;
   float temp, hum;
   char fecha[6];
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
      lcd.print (Clock.getHour(h12, PM));
      lcd.print(":");
      lcd.print (Clock.getMinute());
   }
   delay(1000); 
}


