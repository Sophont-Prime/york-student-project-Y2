#include <Arduino.h>
#include "motor.h"

/*
Motors require one of the Direction pins to be High and one to be Low to define direction.
The Speed pin must be a PWM signal that defines the speed. If the signal is too small (~30) the motor won't move
*/

void forwards(){
  digitalWrite(M1D1, HIGH);
  digitalWrite(M2D1, HIGH);
}

void stop(){
  digitalWrite(M1D1, LOW);
  digitalWrite(M2D1, LOW);
}

void setSpeed(){
    analogWrite(M1S, 160);
    analogWrite(M2S, 160);
  }

void encoderRead(){
  int i = 0;
  while(i != 50) {
    delay(5);
    Serial.print(analogRead(E1F));
    Serial.print("    ");
    Serial.println(analogRead(E1B));
    i += 1;
  }
}

void motorSetup(){
  pinMode(M1D1, OUTPUT);
  pinMode(M1D2, OUTPUT);
  pinMode(M1S, OUTPUT);
  pinMode(E1F, INPUT);
  pinMode(E1B, INPUT);
  
  pinMode(M2D1, OUTPUT);
  pinMode(M2D2, OUTPUT);
  pinMode(M2S, OUTPUT);
  
  setSpeed();
}
