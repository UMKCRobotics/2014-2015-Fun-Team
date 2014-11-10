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
		/*
		 * Given a robot state with a current direction and a direction in which to
		 * turn, phsyically turn the robot and return a new robotstate which has the robot turned that way
		 *
		 * @param: Robotstate - The current state of the robot
		 * @param: Cardinal - The direction which the robot should turn to face
		 * @return A robot state representing the robot after the turn
		 */
		RobotState turn(RobotState,Cardinal);
		/**
		 * Given a robot state with a current position and a direction which to move in
		 * phsyically move the robot and return the updated robot state
		 * @param: Robotstate - The current state of the robot
		 * @param: Cardinal - The direction which the robot should move. Will turn robot to face if not already facing
		 * @return A robot state representing the robot after the movement
		 */
		RobotState move(RobotState,Cardinal);
};

#endif
