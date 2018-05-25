#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
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

}

/* void ajustar_hora() {
   Clock.setSecond((byte) 0);
   Clock.setMinute((byte) 24); 
   Clock.setHour((byte) 20); 
   Clock.setDate((byte) 24); 
   Clock.setMonth((byte) 5); 
   Clock.setYear((byte) 18);

}*/

void loop() { 
      lcd.clear ();
      lcd.setCursor (0, 0);
      char texto[17];
      sprintf (texto, "%02d-%02d %02d:%02d:%02d",
        Clock.getDate(),
        Clock.getMonth(Century),
        Clock.getHour(h12, PM),
        Clock.getMinute(),
        Clock.getSecond()
      );
      lcd.print (texto);


 
 delay(1000); 
}
