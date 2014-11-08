#include "DMCC.h"
#include "Cardinal.h"
#include "RobotState.h"

#ifndef FUN_MOTOR_CONTROLLER_H
#define FUN_MOTOR_CONTROLLER_H

class FunMotorController{

	private: 
		int fd1;
		int fd2;
		void moveForwardOneSquare();
		void turnLeft();
		void turnRight();
		void turnAround();
	public:
		FunMotorController();
		~FunMotorController();
		RobotState turn(RobotState,Cardinal);
		RobotState move(RobotState,Cardinal);
};

#endif
