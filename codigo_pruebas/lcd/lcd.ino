#include <LiquidCrystal.h>
#include <DHT11.h>

int pin=5;
DHT11 dht11(pin);

LiquidCrystal lcd(7, 8, 9, 10, 11, 12); //    ( RS, EN, d4, d5, d6, d7)

void setup()  
   {
        Serial.begin(9600);
       lcd.begin(16, 2); // Fijar el numero de caracteres y de filas
       lcd.print("Temp:"); // Enviar el mensaje
       lcd.setCursor(10,0);
       lcd.print("Hum:");
   }

void loop() 
   {
       int err;
       float temp, hum;
       if((err = dht11.read(hum, temp)) == 0)    // Si devuelve 0 es que ha leido bien
          {
             lcd.setCursor(0, 1);  // set the cursor to column 0, line 1
             lcd.print(temp);
             
             
             lcd.setCursor(10, 1);  // set the cursor to column 0, line 1
             lcd.print(hum);
             
          }
       else
          {
             Serial.println();
             Serial.print("Error Num :");
             Serial.print(err);
             Serial.println();
          }
       delay(1000);            //Recordad que solo lee una vez por segundo
   }

