#include <Arduino.h>

/*
Define M1D1 D4; //Direction1 for Motor 1
Define M1D2 D5; //Direction2 for Motor 1
Define M1S D6; //Speed for Motor 1
Define E1F A1;
Define E1B A2;

Define M2D1 D7; //Direction1 for Motor 2
Define M2D2 D8; //Direction2 for Motor 2
Define M2S D9; //Speed for Motor 2
Define E2F A3;
Deinfe E2B A4;
*/

/*
Motors require one of the Direction pins to be High and one to be Low to define direction.
The Speed pin must be a PWM signal that defines the speed. If the signal is too small (~30) the motor won't move
*/

void setup(){
  Serial.begin(9600);
  pinMode(M1D1, OUTPUT);
  pinMode(M1D2, OUTPUT);
  pinMode(M1S, OUTPUT);
  
  pinMode(M2D1, OUTPUT);
  pinMode(M2D2, OUTPUT);
  pinMode(M2S, OUTPUT);
  
  Serial.println("Setup successful, don't panic");
  
}

void forwards(){
  
}

void setspeed(){
M1S = 
}

void loop(){
  Serial.begin(9600);
  
  Serial.println("Not this file!");  
}
