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

void PID_inmain(int left){

  //forwards();
  int error = left-25;
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

  if (left > 200){
    forwards();
    delay(400);
    stop();
    setSpeed(40, 40);
    turn_left();
    int front = sensorRead(4);
    forwards();
    if (arraycount == 121){
      Serial.println("Increase size of turn_memory array");
      delay(5000000000000);
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
          Serial.println("Maze complete");
          digitalWrite(LED_BUILTIN,HIGH);
          delay(500);
          digitalWrite(LED_BUILTIN,LOW);
          delay(500);
        }
      }
    }
  }

  //If the front sensor detects a wall closer than or equal to 30mm in distrance away from the wall, the robot will then turn towards the gap
  if (front <= 30){
    // In following the left-hand wall algorithm the robot will only ever see a wall in front of itself if it is required to turn to the right
    turn_right();
    turn_right();
    turn_memory[arraycount] = 0;
    arraycount += 1;
    int front = sensorRead(4);
  }
    
  if (left <= 12){
    reverse();
  }
  if (right <= 12){
    reverse();
  }
  
  PID_inmain(left);

  /*
  //This code is for testing purposes and adjusting the PID
  setSpeed(left_motor, right_motor);
  Serial.print("Left motor:");
  Serial.print(left_motor);
  Serial.print("   Right motor:");
  Serial.println(right_motor);
  */
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);// A delay for the blinking of the LED to be noticeable - entirely bug-fixing, could be removed later
  if (mazesolved = false){
    //Read algorithm log
    //Simplify algorithm log
    solution();
    //Execute
  }
}
