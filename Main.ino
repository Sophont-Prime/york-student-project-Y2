//#include <Arduino.h>
#include "motor.h"
#include "TCA9548A.h"
#include "Adafruit_VL6180X.h"
#include <Wire.h>
TCA9548A I2CMux;                  // Address can be passed into the constructor

Adafruit_VL6180X vl = Adafruit_VL6180X();

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
int Speed_init = 60;
int left_motor = 0;
int right_motor = 0;

int PID_memory = 10;
int PID_H[10];

//Ridley was here
float PID(int input, int target){
  float Kp = 0.5;
  float Ki = 0.0;
  float Kd = 1;

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

/*
Motors require one of the Direction pins to be High and one to be Low to define direction.
The Speed pin must be a PWM signal that defines the speed. If the signal is too small (~30) the motor won't move
*/



void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}

int SensorRead(int channel){
  I2CMux.openChannel(channel);
  vl.begin();
  uint8_t distance = vl.readRange();
  I2CMux.closeChannel(channel);
  return  distance;
}

void setup(){
  motorSetup();
  forwards();
  Serial.begin(9600); 
  Serial.println("program started");
  I2CMux.begin(Wire);             // Wire instance is passed to the library
  I2CMux.closeAll();
}

void loop() 
{
  // An LED and when blinking shows that the code is working
  digitalWrite(LED_BUILTIN, HIGH);
  Wire.begin();

  //int right = SensorRead(2);
  //int left = SensorRead(3);
  //int front = SensorRead(4);  

  // Initial Sensor+Motor Testing: the robot tries to drive in a straight line but requires more tuning, might not even require PID but would require a lot of tuning
  /*
  else {
    left_motor = 60;
    right_motor = 60;
    if (left<=40){
      left_motor = 140-left*2;
    }
    if (right<=40){
      right_motor = 140-right*2;
    }
  }*/
  /*
  int error = left - right;
  float adjustment = PID(error, 0);
  left_motor = Speed_init + adjustment;
  right_motor = Speed_init - adjustment;
  if (front <= 40){
    left_motor = 0;
    right_motor = 0;
  }
  */


  left_motor = 60;
  right_motor = 60;
  setSpeed(left_motor, right_motor);
  turn_left();
  delay(1000);
  Serial.print("Left:");
  Serial.print(left_motor);
  Serial.print("   Right:");
  Serial.println(right_motor);
  
  
  I2CMux.closeAll();
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);// A delay for the blinking of the LED to be noticeable - entirely bug-fixing, could be removed later
}
