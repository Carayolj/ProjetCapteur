#include "DHT.h"

int bouton = 4;
int led = 13 ;

void setup() {
  pinMode(bouton, INPUT);
  pinMode(led, OUTPUT);

}
void loop() {
  int btn=digitalRead(bouton);
  digitalWrite(led, btn);
  delay(1000);

}
