#include <Arduino.h>
#include "motor.h"

//mot 1
#define M1D1 4 //Direction1 for Motor 1
#define M1D2 5 //Direction2 for Motor 1
#define M1S 6 //Speed for Motor 1
#define E1F A1
#define E1B A2
//mot 2
#define M2D1 7 //Direction1 for Motor 2
#define M2D2 8 //Direction2 for Motor 2
#define M2S 9 //Speed for Motor 2
#define E2F A6
#define E2B A7

/*
Motors require one of the Direction pins to be High and one to be Low to define direction.
The Speed pin must be a PWM signal that defines the speed. If the signal is too small (~30) the motor won't move
*/

void forwards(){
  digitalWrite(M1D1, HIGH);
  digitalWrite(M2D1, HIGH);
  digitalWrite(M1D2, LOW);
  digitalWrite(M2D2, LOW);
}

void reverse(){
  stop();
  setSpeed(30, 30);
  digitalWrite(M1D1, LOW);
  digitalWrite(M2D1, LOW);
  digitalWrite(M1D2, HIGH);
  digitalWrite(M2D2, HIGH);
  delay(400);
  forwards();
}

void stop(){
  digitalWrite(M1D1, LOW);
  digitalWrite(M2D1, LOW);
  digitalWrite(M1D2, LOW);
  digitalWrite(M2D2, LOW);
}

void setSpeed(int S1, int S2){
  if (S1 <= 0){
    S1 = 0;
  }
  if (S1 >= 255){
    S1 = 255;
  }
  if (S2 <= 0){
    S2 = 0;
  }
  if (S2 >= 255){
    S2 = 255;
  }
  
  analogWrite(M1S, S1);
  analogWrite(M2S, S2*1.1);
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
  
  setSpeed(60, 60);
}

void turn_right(){
  setSpeed(50, 50);
  stop();
  digitalWrite(M1D1, HIGH);
  digitalWrite(M2D2, HIGH);
  delay(500);
  stop();
  delay(150);
}

void turn_left(){
  stop();
  digitalWrite(M1D2, HIGH);
  digitalWrite(M2D1, HIGH);
  delay(500);
  stop();
  delay(100);
  forwards();
}
