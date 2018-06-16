#include <Wire.h>

#define led_rojo 7
#define led_verde 8

void setup()
{
  Serial.begin(9600);
  pinMode(led_verde, OUTPUT);
  pinMode(led_rojo, OUTPUT);
  digitalWrite(led_rojo, LOW);
  digitalWrite(led_verde, LOW);
}

void loop()
{
  printVolts();
}
 
 void printVolts()
{
  int sensorValue = analogRead(A0); //read the A0 pin value
  float voltage = sensorValue * (9.00 / 1023.00) * 2; //convert the value to a true voltage.
  Serial.print("voltage = ");
  Serial.print(voltage); //print the voltage to LCD
  Serial.println(" V");
  for (int i = 0; i < (int) voltage; i++) {
    delay(200);
    Serial.println(i);
    digitalWrite(led_rojo, HIGH);
    delay(200);
    digitalWrite(led_rojo, LOW);
  }
  delay(250);

  int dec1 = (((int)(voltage*10)) % 10);
  for (int i = 0; i < dec1; i++) {
    delay(200);
    Serial.println(i);
    digitalWrite(led_verde, HIGH);
    delay(200);
    digitalWrite(led_verde, LOW);
  }
  delay(2000);
}
