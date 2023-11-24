#include "motor.h"
#include "sensor.h"
#include "pid.h"
#include <Arduino.h>

int Speed_init = 60;
int left_motor = 0;
int right_motor = 0;

int PID_memory = 10;
int PID_H[10];


//Ridley was here

void setup(){
  Serial.begin(9600);
  motorSetup();
  sensorSetup();
  Serial.println("Setup Complete");
  forwards();

}

void loop() 
{
  forwards();
  // An LED and when blinking shows that the code is working
  digitalWrite(LED_BUILTIN, HIGH);

  int right = sensorRead(2);
  int left = sensorRead(3);
  int front = sensorRead(4);

  
  int error = left - right;

  for(int i = 0; i<PID_memory-1; ++i){
    PID_H[i] = PID_H[i+1];
  } 
  PID_H[PID_memory-1] = error;

  float adjustment = PID(error, 0, PID_memory, PID_H)*Speed_init/55;
  if (adjustment < -40){
    adjustment = -40;
  }
  if (adjustment > 40){
    adjustment = 40;
  }

  left_motor = Speed_init + adjustment;
  right_motor = Speed_init - adjustment;

  if (front <= 50){
    stop();
    delay(250);
    turn_right(); // In following the left-hand wall algorithm the robot will only ever see a wall in front if it's a turn to the right 
    }
  else{
  if (error >= 60){
    forwards();
    delay(225);
    turn_left();
    delay(750);
    stop();
  }
  if (error <= -60){
    forwards();
    delay(225);
    turn_right();
    delay(750);
    stop();
  }
  }

  setSpeed(left_motor, right_motor);
  Serial.print("Left motor:");
  Serial.print(left_motor);
  Serial.print("   Right motor:");
  Serial.println(right_motor);
  
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);// A delay for the blinking of the LED to be noticeable - entirely bug-fixing, could be removed later
}
