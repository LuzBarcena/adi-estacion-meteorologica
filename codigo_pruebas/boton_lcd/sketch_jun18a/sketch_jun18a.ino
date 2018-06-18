#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int PULSADOR = 3;

void setup() { 
   pinMode(PULSADOR, INPUT);
   lcd.init();
   lcd.backlight();
   lcd.clear();
   lcd.print("Temp"); // Enviar el mensaje
   lcd.setCursor(13,0);
   lcd.print("Hum");
}

void loop() { 
  if (digitalRead(PULSADOR) == HIGH) {
    lcd.backlight();
    lcd.display();
   } else {
    lcd.noBacklight();
    lcd.noDisplay();
   }
}
