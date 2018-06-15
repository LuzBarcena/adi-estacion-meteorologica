#include <TinyGPS.h>

TinyGPS gps;

void setup()
{
  Serial.begin(115200);
  Serial3.begin(9600);
}

void loop() {
  bool newData = false;

  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (Serial3.available()) {
      char c = Serial3.read();
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData) {
    float flat, flon;
    gps.f_get_position(&flat, &flon);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
  }
}
