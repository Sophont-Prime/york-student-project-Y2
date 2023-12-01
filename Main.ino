#include "motor.h"
#include "sensor.h"
#include "pid.h"
#include <Arduino.h>

int Speed_init = 60;
int left_motor = 0;
int right_motor = 0;

int PID_memory = 15;
int PID_H[15];

//This is the array and adjacent array necessary code
int turn_memory[120];
int arraycount = 0;

//This bool tells us if the maze has been solved
bool mazesolved = false;
int millis_zero = 0;
int millis_true = 0;
//This is the counter for number of lefts
int left_count = 0;

void solution(){
  int length = 120;
  /*
  0 - turn around
  1 - left
  2 - right
  3 - not left
  4 - not right
  */
  int simplificators[8][3] = {
    {1, 0, 2}, 
    {2, 0, 1}, 
    {3, 0, 2}, 
    {4, 0, 1},
    {1, 0, 1},
    {2, 0, 2},
    {1, 0, 4},
    {2, 0, 3}
  };
  int simplifications[8] = {0, 0,  1, 2, 3, 4, 2, 1};


  bool no_changes = false;
  while (no_changes = false){
    no_changes = true;
    for(int i = 0; i<length-2; i++){
      for(int j = 0; j<8; j++){
        if(turn_memory[i] == simplificators[j][0] && turn_memory[i+1] == simplificators[j][1] && turn_memory[i+2] == simplificators[j][2]){
          turn_memory[i] = simplifications[j];
          turn_memory[i+1] = -1;
          turn_memory[i+2] = -1;
          no_changes = false;
        }
      }
    }
  }
}


void setup(){
  Serial.begin(9600);
  motorSetup();
  sensorSetup();
  Serial.println("Setup Complete");
  forwards();
}

void loop() {
  // An LED and when blinking shows that the code is working
  digitalWrite(LED_BUILTIN, HIGH);

  int right = sensorRead(2);
  int left = sensorRead(3);
  int front = sensorRead(4);

  
  //int error = left - right;
  int error = left-40;
  //This consults the PID memory
  for(int i = 0; i<PID_memory-1; ++i){
    PID_H[i] = PID_H[i+1];
  } 
  PID_H[PID_memory-1] = error;

  float adjustment = PID(error, 40, PID_memory, PID_H)*Speed_init/55;


  left_motor = Speed_init + adjustment;
  right_motor = Speed_init - adjustment;
  //If the front sensor detects a wall closer than or equal to 40mm in distrance away from the wall55555
  if (front <= 40){
    turn_right(); // In following the left-hand wall algorithm the robot will only ever see a wall in front if it's a turn to the right
    turn_right();
    turn_memory[arraycount] = 0;
    arraycount += 1;
  }
  
  if (error >= 60){
    forwards();
    delay(225);
    turn_left();
    delay(750);
    stop();
    if (arraycount == 121){
      delay(5000000000000);
      Serial.println("Increase size of turn_memory array");
    }
    turn_memory[arraycount] = 1;
    arraycount += 1;
    if (left_count == 0){
      millis_zero = millis();
      left_count += 1;
    }
    if (left_count >= 1){
      left_count += 1;
    }
    if (left_count = 3){
      millis_true = millis() - millis_zero;
      if (millis_true <= 5500){
        stop();
        mazesolved = true;
        //dance
        while (true){
          turn_right();
          turn_left();
          turn_right();
          turn_left();
          turn_right();
          turn_right();
          turn_right();
        }
      }
    }
  }
  /*
  if (error <= -60){
    forwards();
    delay(225);
    turn_right();
    delay(750);
    stop();
    array[arraycount] = 2;
    arraycount += 1;
    left_count = 0;
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
  */
  setSpeed(left_motor, right_motor);
  Serial.print("Left motor:");
  Serial.print(left_motor);
  Serial.print("   Right motor:");
  Serial.println(right_motor);
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);// A delay for the blinking of the LED to be noticeable - entirely bug-fixing, could be removed later
  if (mazesolved = true){
    solution();
  } 
  }
}
