#include <SoftwareSerial.h>

// definicion de variables que refieren a los pones

int pinLed = 13;

int pinLDR = A2;

int umbral = 600;

void setup() {
  Serial.begin(9600);
  
  pinMode(pinLed, OUTPUT);
  pinMode(pinLDR, INPUT);
  
  digitalWrite(pinLed, LOW);
  
  Serial.println("ARFUINO proyecto01-v2: iniciado");
}

void loop() {
  
  if (analogRead(pinLDR) < umbral) {
    digitalWrite(pinLed, HIGH);
  } else {
    digitalWrite(pinLed, LOW);
  }
  Serial.println(analogRead(pinLDR));
  
  delay(500);
}
