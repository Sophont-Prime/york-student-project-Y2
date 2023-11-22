//sensor.h

//Runs through sensor setup (Begins wire instance to be passed to wire library)
void sensorSetup();

//Reads the passed sensor channel - notable channels are 2, 3 and 4 (R, L, F)
int sensorRead(int channel);
