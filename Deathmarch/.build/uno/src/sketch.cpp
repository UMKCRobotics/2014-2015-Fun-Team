#include <Arduino.h>
#include "MotorController.h"
void setup();
void loop();
#line 1 "src/sketch.ino"
//#include "MotorController.h"

FunMotorController mc;
RobotState state;

void setup()
{
	state.currentDirection = NORTH;
	mc.move(state,NORTH);	
	mc.move(state,WEST);
}

void loop()
{
	
}
