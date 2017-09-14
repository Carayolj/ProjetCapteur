#include "DHT.h"

DHT dht;
float humidity;
float temperature;
int pinSensor=2;
int pinBouton=4;
int btn;
void setup()
{
  pinMode(pinBouton, INPUT);
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");

  dht.setup(pinSensor);
}

void loop()
{
        delay(50);
btn=digitalRead(pinBouton);
        if(btn==HIGH)    {
         humidity = dht.getHumidity();
         temperature = dht.getTemperature();

        Serial.print(dht.getStatusString());
        Serial.print("\t");
        Serial.print(humidity, 1);
        Serial.print("\t\t");
        Serial.print(temperature, 1);
        Serial.print("\t\t");
        Serial.println(dht.toFahrenheit(temperature), 1);
      }

}
