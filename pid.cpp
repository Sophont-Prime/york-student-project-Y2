#include "pid.h"

int PID_memory = 10;
int PID_H[10];

int PID(int input, int target){
  float Kp = 1;
  float Ki = 0.0;
  float Kd = 3;

  for(int i = 0; i<PID_memory-1; ++i){
    PID_H[i] = PID_H[i+1];
  } 
  PID_H[PID_memory] = input;
  
  int P = target - input;

  int I = 0;
  for(int i = 0; i<PID_memory; ++i){
    I = I + PID_H[i];
  } 

  int D = (PID_H[PID_memory] - PID_H[0])/PID_memory;

  float output = Kp*P + Ki*I + Kd*D;
  return output;
}
