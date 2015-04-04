#include "MotorController.h"

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

void FunMotorController::setBackRight(int amount){
}
void FunMotorController::setBackLeft(int amount){
}
void FunMotorController::setFrontRight(int amount){
}
void FunMotorController::setFrontLeft(int amount){
}
void FunMotorController::setRight(int amount){
	setBackRight(amount);
	setFrontRight(amount);
}
void FunMotorController::setLeft(int amount){
	setFrontLeft(amount);
	setBackLeft(amount);
}
void FunMotorController::setAll(int amount){
	setFrontLeft(amount);
	setFrontRight(amount);
	setBackLeft(amount);
	setBackRight(amount);
}

void FunMotorController::stopAll(){
	setAll(0);
}

void FunMotorController::turnAround(){
}
void FunMotorController::turnLeft(){
}
void FunMotorController::turnRight(){
}
void FunMotorController::moveForwardOneSquare(){


}

