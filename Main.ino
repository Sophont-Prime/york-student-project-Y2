#include "motor.h"
#include <Arduino.h>
//Mot 1
#define M1D1 4 //Direction1 for Motor 1
#define M1D2 5 //Direction2 for Motor 1
#define M1S 6 //Speed for Motor 1
#define E1F A1
#define E1B A2
//Mot 2
#define M2D1 7 //Direction1 for Motor 2
#define M2D2 8 //Direction2 for Motor 2
#define M2S 9 //Speed for Motor 2
#define E2F A3
#define E2B A4

void setup(){
  Serial.begin(9600);
  motorSetup();
  sensorSetup();
  Serial.println("Setup complete");
}
void loop(){
  forwards();
  delay(500);
  stop();
}
