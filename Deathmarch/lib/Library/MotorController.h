#include "Cardinal.h"
#include "RobotState.h"
#include "SerialCom.h"

#ifndef FUN_MOTOR_CONTROLLER_H
#define FUN_MOTOR_CONTROLLER_H

class FunMotorController{
	
	RedBotMotors frontMotors;
	private: 

		void moveForwardOneSquare();
		void turnLeft();
		void turnRight();
		void turnAround();
		/*
		 * Given a current direction and a direction in which to
		 * turn, phsyically turn the robot 
		 *
		 * @param: current - The current direction of the robot
		 * @param: toFace - The direction which the robot should turn to face
		 */
		void turn(Cardinal current,Cardinal toFace);
		void stopAll();
		bool allLineSensorsOnBlack();
		int rightLineRead();
		int leftLineRead();
		int centerLineRead();
		const int MAX_SPEED = 140;
		const int MAX_TURN_SPEED = MAX_SPEED - 50;
	public:
		FunMotorController();
		~FunMotorController();

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
