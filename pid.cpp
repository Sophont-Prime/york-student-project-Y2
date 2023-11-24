#include <Arduino.h>
#include "pid.h"

float PID(int input, int target, int PID_memory, int PID_H[]){
  float Kp = 0.15;
  float Ki = 0;
  float Kd = -0;
  
  int P = target - input;
  Serial.print(P);
  int I = 0;
  for(int i = 0; i<PID_memory; ++i){
    I = I + PID_H[i];
  } 
  int D = (PID_H[PID_memory-1] - PID_H[PID_memory-4]);
  float output = Kp*P + Ki*I + Kd*D;
  /*
  if (output < -40){
    output = -40;
  }
  if (output > 40){
    output = 40;
  }
  */
  return output;
}
