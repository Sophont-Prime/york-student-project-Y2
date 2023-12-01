#include "motor.h"
#include "sensor.h"
#include "pid.h"
#include <Arduino.h>

int Speed_init = 60;
int left_motor = 0;
int right_motor = 0;

int PID_memory = 15;
int PID_H[15];



void setup(){
  Serial.begin(9600);
  motorSetup();
  sensorSetup();
  Serial.println("Setup Complete");
  forwards();
}


void PID_inmain(int left){

  //forwards();
  int error = left-30;
  //This consults the PID memory

  for(int i = 0; i<PID_memory-1; ++i){
    PID_H[i] = PID_H[i+1];
  } 
  PID_H[PID_memory-1] = error;

  float adjustment = PID(error, 30, PID_memory, PID_H)*Speed_init/55;


  left_motor = Speed_init + adjustment;
  right_motor = Speed_init - adjustment;

  setSpeed(left_motor, right_motor);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  //read sensors
  int right = sensorRead(2);
  int left = sensorRead(3);
  int front = sensorRead(4);
  
  // An LED and when blinking shows that the code is working
  

  if (front <= 40){
    turn_right();
    }
  else if (left <= 100){
    PID_inmain(left);
    }
  //If the front sensor detects a wall closer than or equal to 40mm in distrance away from the wall55555
  //
   // In following the left-hand wall algorithm the robot will only ever see a wall in front if it's a turn to the right 
  
  
  
  
  /*
  if (error >= 75){
    forwards();
    delay(225);
    turn_left();
    delay(750);
    stop();
  }
  if (error <= -75){
    forwards();
    delay(225);
    turn_right();
    delay(750);
    stop();
  }
  */
  /*
  if (PID_H[0] == PID_H[1] && PID_H[0] <= 60 || PID_H[1] <=60 ){ 
    bool x = true;
    for(int p = 0; p<PID_memory-1; ++p){
      if (x = true && PID_H[p] != PID_H[p+1]){
        x = false;
        break;
      }
    }
    if (x == true){
      backwards();
      delay(225);
    }     
  }
  
  
  Serial.print("Left motor:");
  Serial.print(left_motor);
  Serial.print("   Right motor:");
  Serial.println(right_motor);
  */
  

  digitalWrite(LED_BUILTIN, LOW);
  delay(50);// A delay for the blinking of the LED to be noticeable - entirely bug-fixing, could be removed later
}
