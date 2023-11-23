#include "motor.h"
#include "sensor.h"
#include "pid.h"
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

int Speed_init = 60;
int left_motor = 0;
int right_motor = 0;

void setup(){
  Serial.begin(9600);
  motorSetup();
  sensorSetup();
  Serial.println("Setup complete");
  forwards();
}
void loop(){
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("1");
  int right = sensorRead(2);
  int left = sensorRead(3);
  int front = sensorRead(4);
  Serial.print("2");
  int error = left - right;
  Serial.print("3");
  float adjustment = PID(error, 0)*Speed_init/55;
  if (adjustment < -40){
    adjustment = -40;
  }
  if (adjustment > 40){
    adjustment = 40;
  }
  left_motor = Speed_init + adjustment;
  right_motor = Speed_init - adjustment;
  Serial.print("4");
  if (front <= 40){
    turn_left();
    turn_left();
    forwards();
  }
  setSpeed(left_motor, right_motor);
  Serial.print("Left motor:");
  Serial.print(left_motor);
  Serial.print("   Right motor:");
  Serial.println(right_motor);
  Serial.println("5");
  digitalWrite(LED_BUILTIN, LOW);
  delay(25);
}
