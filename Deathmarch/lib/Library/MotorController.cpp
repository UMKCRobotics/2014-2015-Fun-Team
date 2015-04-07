#include "MotorController.h"
#include "Pins.h"
#include "Arduino.h"
#include "RedBot.h"

FunMotorController::FunMotorController(){
}
FunMotorController::~FunMotorController(){
}

RobotState FunMotorController::move(RobotState state, Cardinal c){
	RobotState s = state;
	if(state.currentDirection != c){
	       	turn(state.currentDirection,c);	
		s.currentDirection = c;
	}
	switch(c){
		case NORTH: 
			s.currentNode -= 7;
			break;
		case SOUTH: 
			s.currentNode += 7;
			break;
		case EAST:
			s.currentNode += 1;
			break;
		case WEST:
			s.currentNode -= 1;
			break;
	}
	moveForwardOneSquare();
	return s;
}
void FunMotorController::turn(Cardinal current, Cardinal toFace){
	switch(current){
		case NORTH:
			switch(toFace){
				case NORTH: break;
				case SOUTH:
					turnAround();
					break;
				case EAST:
					turnRight();
					break;
				case WEST:
					turnLeft();
					break;
			} break;
		case SOUTH:
			switch(toFace){
				case SOUTH: break;
				case NORTH:
					turnAround();
					break;
				case EAST:
					turnLeft();
					break;
				case WEST:
					turnRight();
					break;
			} break;
		case EAST:
			switch(toFace){
				case EAST: break;
				case WEST:
					turnAround();
					break;
				case NORTH:
					turnLeft();
					break;
				case SOUTH:
					turnRight();
					break;
			} break;
		case WEST:
			switch(toFace){
				case WEST: break;
				case EAST:
					turnAround();
					break;
				case NORTH:
					turnRight();
					break;
				case SOUTH:
					turnLeft();
					break;
			} break;
	}
}


void FunMotorController::stopAll(){
	frontMotors.brake();
	SerialCom::stopBothMotors();
}

void FunMotorController::turnAround(){
	turnRight();
	turnRight();
}
void FunMotorController::turnLeft(){
	frontMotors.leftDrive(-MAX_TURN_SPEED);
	frontMotors.rightDrive(MAX_TURN_SPEED);
	SerialCom::motorsLeftTurn();
	delay(800);
	while(!allLineSensorsOnBlack()){} //this is why i miss frp
	stopAll();
	
}
void FunMotorController::turnRight(){
	frontMotors.leftDrive(MAX_TURN_SPEED);
	frontMotors.rightDrive(-MAX_TURN_SPEED);
	SerialCom::motorsRightTurn();
	delay(800); 
	while(!allLineSensorsOnBlack()){} //this is why i miss frp
	stopAll();
}
void FunMotorController::moveForwardOneSquare(){
	SerialCom::motorsFullForward();
	frontMotors.drive(MAX_SPEED-50);
	delay(800);
	while(!allLineSensorsOnBlack() && analogRead(FRONT_IR) < 650){
		int potentialNextRightValue = MAX_SPEED - rightLineRead();
		int potentialNextLeftValue = MAX_SPEED - leftLineRead();
		int nextRightValue = (potentialNextRightValue >0)? potentialNextRightValue : 20;
		int nextLeftValue = (potentialNextLeftValue > 0) ? potentialNextLeftValue : 20;
		frontMotors.leftDrive(nextLeftValue);
		frontMotors.rightDrive(nextRightValue);
	}
	stopAll();
}
bool FunMotorController::allLineSensorsOnBlack(){
	int blackMin = 800;
	return rightLineRead() > blackMin &&  leftLineRead() > blackMin && centerLineRead() > blackMin;
}
int FunMotorController::rightLineRead(){
	return analogRead(RIGHT_LINE);
}
int FunMotorController::leftLineRead(){
	return analogRead(LEFT_LINE);
}
int FunMotorController::centerLineRead(){
	return analogRead(CENTER_LINE);
}
