#include <Arduino.h>

#define M1D1 4 //Direction1 for Motor 1
#define M1D2 5 //Direction2 for Motor 1
#define M1S 6 //Speed for Motor 1
#define E1F A1
#define E1B A2

#define M2D1 7 //Direction1 for Motor 2
#define M2D2 8 //Direction2 for Motor 2
#define M2S 9 //Speed for Motor 2
#define E2F A3
#define E2B A4

/*
Motors require one of the Direction pins to be High and one to be Low to define direction.
The Speed pin must be a PWM signal that defines the speed. If the signal is too small (~30) the motor won't move
*/

void forwards(){
  digitalWrite(M1D1, HIGH);
}

void backwards(){
  digitalWrite(M1D2, HIGH);
}

void setSpeed(){
  analogWrite(M1S, 255);
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

void setup(){
  Serial.begin(9600);
  pinMode(M1D1, OUTPUT);
  pinMode(M1D2, OUTPUT);
  pinMode(M1S, OUTPUT);
  pinMode(E1F, INPUT);
  pinMode(E1B, INPUT);
  
  pinMode(M2D1, OUTPUT);
  pinMode(M2D2, OUTPUT);
  pinMode(M2S, OUTPUT);
  
  setSpeed();
  Serial.println("Setup successful, don't panic");
  delay(500);
}

void loop(){
  /*forwards();
  encoderRead();
  digitalWrite(M1D1, LOW);
  Serial.println("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
  backwards();
  encoderRead();
  digitalWrite(M1D2, LOW);
  Serial.println("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
  */
  delay(5);
  Serial.print(analogRead(E1F));
  Serial.print("    ");
  Serial.println(analogRead(E1B));
}
