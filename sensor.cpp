#include <Arduino.h>
#include "TCA9548A.h"
#include "Adafruit_VL6180X.h"
#include <Wire.h>

TCA9548A I2CMux;                  // Address can be passed into the constructor

Adafruit_VL6180X vl = Adafruit_VL6180X();

void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}

void sensorSetup(){
  //  Wire.setPins(21, 22);       // ESP32 users, use setPins(sda, scl) if customised, *before* passing Wire to the library (the line below).  
  I2CMux.begin(Wire);             // Wire instance is passed to the library

  I2CMux.closeAll();              // Set a base state which we know (also the default state on power on)
}

int sensorRead(int channel){
  I2CMux.openChannel(channel);
  vl.begin();
  uint8_t distance = vl.readRange();
  I2CMux.closeChannel(channel);
  return  distance;
}
