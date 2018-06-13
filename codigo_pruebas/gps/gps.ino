
char dato=' ';

void setup()
{
 Serial.begin(115200);            
 Serial3.begin(9600); 
}


void loop()
{
  if(Serial3.available())
  {
    dato=Serial3.read();
    Serial.print(dato);
  }
}

