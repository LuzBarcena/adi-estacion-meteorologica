#include <DS3231.h>
#include <Wire.h>
DS3231  Clock;
byte year, month, date, DoW, hour, minute, second;

bool Century = false;
bool h12 = false;
bool PM = false;

void setup() { 
// Se inicial la interfaz I2c
  Wire.begin();
  // Se inicia la Comunicación Serial
  /* Clock.setSecond((byte) 0);
   Clock.setMinute((byte) 24); 
   Clock.setHour((byte) 20); 
   Clock.setDate((byte) 24); 
   Clock.setMonth((byte) 5); 
   Clock.setYear((byte) 18);*/
  Serial.begin(9600);

}
void loop() { 
//Se rescata la información
  //Se imprime
      char mes[3];
      
      sprintf (mes, "%02d", Clock.getMonth(Century));
      Serial.print(Clock.getYear(), DEC);
      Serial.print("-");
      //Serial.print(Clock.getMonth(Century), DEC);
      Serial.print(mes);
      Serial.print("-");
      Serial.print(Clock.getDate(), DEC);
      Serial.print(" ");
      Serial.print(Clock.getHour(h12, PM), DEC); //24-hr
      Serial.print(":");
      Serial.print(Clock.getMinute(), DEC);
      Serial.print(":");
      Serial.println(Clock.getSecond(), DEC);


 
 delay(1000); 
}
