#include "motor.h"
#include <Arduino.h>

void setup(){
  Serial.begin(9600);
}
void loop(){
  forwards();
  delay(500);
  stop();
}
