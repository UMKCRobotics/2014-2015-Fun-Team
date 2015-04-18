#include "Cardinal.h"
#include "RobotState.h"
#include "SerialCom.h"

#ifndef FUN_MOTOR_CONTROLLER_H
#define FUN_MOTOR_CONTROLLER_H

class FunMotorController{
	
	private: 
                bool justTurnedLeft;
		RedBotMotors frontMotors;
		void moveForwardOneSquare();
		void turnAround();
		/*
		 * Given a current direction and a direction in which to
		 * turn, phsyically turn the robot 
		 *
		 * @param: current - The current direction of the robot
		 * @param: toFace - The direction which the robot should turn to face
		 */
		void turn(Cardinal current,Cardinal toFace);
		bool allLineSensorsOnBlack();
		int rightLineRead();
		int leftLineRead();
		int centerLineRead();
		const int MAX_SPEED_L = 100;
		const int MAX_SPEED_R = 120;
		const int MAX_TURN_SPEED =80;
		const int MAX_REVERSE_TURN_SPEED = -100;
		const int MIN_SPEED = 0;
		const int TURN_DELAY_R = 800;
		const int TURN_DELAY_L = 790;
		void alignToIRs();
 public:		
		void turnRight();
		void turnLeft();
		FunMotorController();
		~FunMotorController();

		void stopAll();
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
