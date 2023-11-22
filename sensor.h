//sensor.h

//Send byte to assigned bus
void TCA9548A(uint8_t bus);

//Runs through sensor setup (Begins wire instance to be passed to wire library)
void sensorSetup();

//Reads the passed sensor channel - notable channels are 2, 3 and 4 (R, L, F)
void sensorRead(int channel);
