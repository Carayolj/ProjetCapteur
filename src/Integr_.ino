#include "DHT.h"
#include "TM1637Display.h"
#include "SoftwareSerial.h"
#define CLK 7
#define DIO 8
int maxtab(int* tab);
DHT dht;
float humidity;
float temperature;
int pinSensor=2;
int pin7seg=7;
int pinBouton=4;
int btn;
int tabT[100];
int tabH[100];

TM1637Display display(CLK, DIO);
SoftwareSerial BT(10,11);
void setup()
{
  pinMode(pinBouton, INPUT);
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  display.setBrightness(5);
  dht.setup(pinSensor);
  for (size_t i = 0; i < 100; i++) {
      tabT[i]=0;
      tabH[i]=0;
  }
}

void loop()
{
        delay(150);
        for (size_t i = 0; i < 100; i++) {
          tabT[i]=tabT[i+1];
          tabH[i]=tabH[i+1];
        }
        btn=digitalRead(pinBouton);
        if(btn==HIGH){
          Serial.print("\nLa plus haute temperature parmis les 100 dernieres aquisitions est:");
          Serial.print(maxtab(&tabT[0]));
          Serial.print("\n Le plus haut pourcentage d'humidité parmis les 100 dernieres aquisitions est:");
          Serial.print(maxtab(&tabH[0]));
          Serial.print("\n");

          delay(3500);
        }
         humidity = dht.getHumidity();
         temperature = dht.getTemperature();
         tabT[99]=(int) temperature;
         Serial.print("\nTemperature Stored:");
         Serial.print(tabT[99]);
         Serial.print("\nHumidité Stored:");
         Serial.print(tabH[99]);

         tabH[99]=(int) humidity;
         if (isnan(humidity) || isnan(temperature) ) {
           Serial.println("Failed to read from DHT sensor!");
           return;
         }


        Serial.print((int)humidity);
        Serial.print("\t\t");
        Serial.print(temperature, 1);
        Serial.print("\t\t");
        Serial.println(dht.toFahrenheit(temperature), 1);

        display.showNumberDec((int) temperature);
}
int maxtab(int* tab){
  int maxVal=0;
  for (size_t i = 0; i < 100; i++) {

maxVal=max(maxVal, *(tab+i));
  }
  return maxVal;
}
