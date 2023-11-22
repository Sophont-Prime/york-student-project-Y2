//motor.h

//It's a function that sets the motors fowards
void forwards();

//Stops motor
void stop();

//Sets motor speed to two variables S1 and S2 corresponding to left motor and right motor
void setSpeed(int S1, int S2);

//Reads the encoder, add more detail later
void encoderRead();

//Motor setup code
void motorSetup();

//Makes the robot turn left 90 degrees
void turn_left();
