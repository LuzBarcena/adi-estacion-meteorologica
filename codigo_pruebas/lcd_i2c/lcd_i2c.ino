#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27, 16, 2);
 int restante = 10;
void setup()
{
   lcd.init();
   lcd.backlight();
   lcd.clear();
}
 
void loop()
{
   if (restante > 0) {
     lcd.clear ();
     lcd.setCursor(0, 0);
     lcd.print ("Explosion en:");
     lcd.setCursor(0, 1);
     lcd.print (restante);
     lcd.setCursor(3, 1);
     lcd.print ("segundos");
     restante --;
   } else {
     lcd.clear ();
     lcd.setCursor(0, 0);
     lcd.print ("BOOOOM");
   }
   delay (1000);
}
