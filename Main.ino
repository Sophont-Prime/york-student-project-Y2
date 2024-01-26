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
bool no_changes = false;

//This bool tells us if the maze has been solved
bool mazesolved = false;
int millis_zero = 0;
int millis_true = 0;
//This is the counter for number of turns, it is utilised in tracking whether the robot has reached the end of the maze or not
int right_count = 0;

void solution(){
  int length = 120;
  /*
  0 - turn around
  1 - left
  2 - right
  3 - not left
  4 - not right
  5 - skip
  */
  int simplificators[5][2] = {
    {1, 2}, 
    {3, 2}, 
    {4, 1},
    {1, 1},
    {2, 2},
  };
  int simplifications[5] = {0, 1, 2, 3, 4};


  bool no_changes = false;
  while (no_changes = false){
    no_changes = true;
    for(int i = 0; i<length-1; i++){
      if (turn_memory[i] == 0){
        int a = 1;
        int b = 1;
        int no_solution = 0;
        while (no_solution == 0){
          for (int j = 0; j<5; j++){
              if (turn_memory[i-a] == simplificators[j][1] && turn_memory[i+b] == simplificators[j][2] || turn_memory[i-a] == simplificators[j][2] && turn_memory[i+b] == simplificators[j][1]){
                turn_memory[i-a] = 5;
                turn_memory[i+b] = 5;
                turn_memory[i] = simplifications[j];
                no_solution = 1;
              }
          if (turn_memory[i-a] == 3 || 4){
            a = a + 1;
          }
          if (turn_memory[i+b] == 3 || 4){
            b = b + 1;
          } 

            }
          }
      }
    }
  }
}

void solution_consult(){
  no_changes = false;
  while (no_changes = false){
    no_changes = true;
    if (turn_memory[arraycount] == 5 || turn_memory[arraycount] == 0 || turn_memory[arraycount] == 3 || turn_memory[arraycount] == 4){
      //If next instruction is null or in an edge case, bypass
      arraycount +=1;
      no_changes = false;
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

  float adjustment = PID(error, 0, PID_memory, PID_H)*Speed_init/55;


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
    right_count = 0;
  }
  
  //If the front sensor detects a wall closer than or equal to 30mm in distrance away from the wall, the robot will then turn towards the gap
  if (front <= 30){
    // In following the left-hand wall algorithm the robot will only ever see a wall in front of itself if it is required to turn to the right
    turn_right();
    forwards();
    turn_memory[arraycount] = 2;
    arraycount += 1;
    int front = sensorRead(4);
    if (front <= 30){
      turn_right();
      forwards();
      arraycount -=1;
      turn_memory[arraycount] = 0;
      arraycount +=1;
    }
    if (right_count == 0){
      millis_zero = millis();
      right_count += 1;
    }
    if (right_count >= 1){
      right_count += 1;
    }
    if (right_count = 3){
      millis_true = millis() - millis_zero;
      if (4000 <= millis_true <= 5500){
        stop();
        mazesolved = true;
        //dance
        int h = 0;
        while (h <= 30){
          Serial.println("Maze complete");
          digitalWrite(LED_BUILTIN,HIGH);
          delay(500);
          digitalWrite(LED_BUILTIN,LOW);
          delay(500);
          h += 1;
        }
      }
      right_count = 0;
    }
  }
    
  if (left <= 12){
    reverse();
  }
  if (right <= 12){
    reverse();
  }
  forwards();
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
  //If the maze has been solved but a solution has not been derived then derive a solution
  if (mazesolved == true){
    //Read algorithm log
    //Simplify algorithm log
    solution();
    //A solution has been found and can be utilised - so it is
    arraycount = 0;
    while (mazesolved == true){
      forwards();
      PID_inmain(left);
      int right = sensorRead(2);
      int left = sensorRead(3);
      int front = sensorRead(4);
      if (left <= 12){
        reverse();
      }
      if (right <= 12){
        reverse();
      }
      if (left > 20 && turn_memory[arraycount] == 1){
        forwards();
        delay(400);
        stop();
        setSpeed(40, 40);
        turn_left();
      }
      if (right > 20 && turn_memory[arraycount] == 2){
        turn_right();
      }
      solution_consult();
      arraycount +=1;

    }
  }
}
