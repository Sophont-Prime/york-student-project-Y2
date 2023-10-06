#include <Arduino.h>

Define M1D1 4; //Direction1 for Motor 1
Define M1D2 5; //Direction2 for Motor 1
Define M1S 6; //Speed for Motor 1
Define M2D1 7; //Direction1 for Motor 2
Define M2D2 8; //Direction2 for Motor 2
Define M2S 9; //Speed for Motor 2

/*
Motors require one of the Direction pins to be High and one to be Low to define direction.
The Speed pin must be a PWM signal that defines the speed. If the signal is too small (~30) the motor won't move
*/

void setup(){
  pinMode(M1D1, OUTPUT);
  pinMode(M1D2, OUTPUT);
  pinMode(M1S, OUTPUT);
  pinMode(M2D1, OUTPUT);
  pinMode(M2D2, OUTPUT);
  pinMode(M2S, OUTPUT);
  Serial.println("Setup successful, don't panic");
  
}

void loop(){
  
}
