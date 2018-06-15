
void setup()
  {  Serial.begin(115200);
     Serial2.begin(115200);
    delay(2000);
    Serial2.write("AT+RST\r\n");
    show();
    delay(2000);
    Serial2.write("AT+CWMODE=1\r\n"); 
    show();
    delay(5000);
    Serial2.write("AT+CIFSR\r\n"); 
    show();
    delay(5000);
    Serial2.write("AT+CIPSTART=\"TCP\",\"192.168.0.13\",80\r\n");
    delay(500);
    show();
    http_send("POST /guardar.php HTTP/1.1\r\n");
    http_send("Host: 192.168.0.13\r\n");
    http_send("Content-Length: 39\r\n");
    http_send("Content-Type: application/x-www-form-urlencoded\r\n");
    http_send("\r\n");
    http_send("temperatura=35&humedad=20&luminosidad=2\r\n");
    delay(500);
    Serial2.write("AT+CIPCLOSE\r\n");
    show();
  }

void show() {
  while ( Serial2.available() ) {
    Serial.write(Serial2.read());
  }
}

void http_send(char* data) {
  delay(500);
  int count_bytes = strlen(data);
  char enviar[128];
  sprintf(enviar,"AT+CIPSEND=%d\r\n",count_bytes);
  Serial2.write(enviar);
  show();
  delay(100);
  Serial2.write(data);
  show();
}

void loop() {
  if (Serial2.available()) {
    Serial.write(Serial2.read());
  }
  if (Serial.available()) {
    //Serial2.write(Serial.read());
    
  }
}
