#include "MotorController.h"

MotorController::MotorController(){
	fd1 = DMCCStart(0);
	fd2 = DMCCStart(1);
}
MotorController::~MotorController(){
	DMCCEnd(fd1);
	DMCCEnd(fd2);
}

RobotState RobotState::move(RobotState state, Cardinal c){
	RobotState s = state;
	if(state->currentDirection != c){
	       	turn(state,c);	
		s->currentDirection = c;
	}
	switch(c){
		case NORTH: 
			s->currentNode -= 7;
			break;
		case SOUTH: 
			s->currentNode += 7;
			break;
		case EAST:
			s->currentNode += 1;
			break;
		case WEST:
			s->currentNode -= 1;
			break;
	}
	moveForwardOneSquare();
	return s;
}
RobotState RobotState::turn(RobotState state, Cardinal c){
	RobotState s = state;
	switch(state->currentDirection){
		case NORTH:
			switch(c){
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
	s->currentDirection = c;
	return s;
}
