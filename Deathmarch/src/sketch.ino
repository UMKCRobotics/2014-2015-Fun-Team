#include "MotorController.h"

FunMotorController mc;
RobotState state;

void setup()
{
	state.currentDirection = NORTH;
	mc.move(state,NORTH);	
}

void loop()
{
	
}
