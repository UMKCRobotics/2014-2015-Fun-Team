#include "Cardinal.h"
#include "RobotState.h"
#include "RedBot.h"

#ifndef FUN_MOTOR_CONTROLLER_H
#define FUN_MOTOR_CONTROLLER_H

class FunMotorController{
	
	SoftwareSerial backSerialCom;
	/*
	 * Serial works as in a 2 byte fashion. If the first byte is 0 a special command is desired
	 * if the first byte is not 0 then a motor speed is desired, first byte is right second byte is left
	 * 244 is max forward, 1 is max backward with 127 being 'stop' (the special stop command should be used instead
	 *
	 * if the first byte is 0 then the next byte is the selector byte
	 * 1 - stop both motors
	 * 2 - red LED ON
	 * 3 - yellow LED ON
	 * 4 - green LED ON
	 * 5 - red LED OFF
	 * 6 - yellow LED OFF
	 * 7 - green LED OFF
	 */


	RedBotMotor frontMotors;
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
		void setAll(int);
		void stopAll();
		void setLeft(int);
		void setRight(int);
		void setFrontLeft(int);
		void setFrontRight(int);
		void setBackLeft(int);
		void setBackRight(int);
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
