#include "MotorController.h"

FunMotorController::FunMotorController(){
	fd1 = DMCCstart(0);
	fd2 = DMCCstart(1);
}
FunMotorController::~FunMotorController(){
	DMCCend(fd1);
	DMCCend(fd2);
}

RobotState FunMotorController::move(RobotState state, Cardinal c){
	RobotState s = state;
	if(state.currentDirection != c){
	       	turn(state,c);	
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
RobotState FunMotorController::turn(RobotState state, Cardinal c){
	RobotState s = state;
	switch(state.currentDirection){
		case NORTH:
			switch(c){
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
			switch(c){
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
			switch(c){
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
			switch(c){
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
	s.currentDirection = c;
	return s;
}

void FunMotorController::turnAround(){
}
void FunMotorController::turnLeft(){
}
void FunMotorController::turnRight(){
}
void FunMotorController::moveForwardOneSquare(){}
