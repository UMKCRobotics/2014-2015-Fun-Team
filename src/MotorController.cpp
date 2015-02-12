#include "MotorController.h"
#include <sstream>

FunMotorController::FunMotorController(){
	backMotorController = DMCCstart(0); //Back
	frontMotorController = DMCCstart(1); //Front
}
FunMotorController::~FunMotorController(){
	DMCCend(backMotorController);
	DMCCend(frontMotorController);
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
	setMotorPower(backMotorController,1,-amount);
}
void FunMotorController::setBackLeft(int amount){
	setMotorPower(backMotorController,2,amount);
}
void FunMotorController::setFrontRight(int amount){
	setMotorPower(frontMotorController,1,-amount);
}
void FunMotorController::setFrontLeft(int amount){
	setMotorPower(frontMotorController,2,amount);
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
	Logger::logMessage("Stopping all motors");
	setAll(0);
}

void FunMotorController::turnAround(){
}
void FunMotorController::turnLeft(){
}
void FunMotorController::turnRight(){
}
void FunMotorController::moveForwardOneSquare(){

	Logger::logMessage("Moving Forward one square.");
	
	stopAll();
	int blackLevel = 130;
	int blackMax = 190;
	int motorMax = 10000;
	applyFuncUntilPredicateAndStop(
	[&](SensorValues v){
		return (v.lineLeft >= blackLevel && v.lineCenter >= blackLevel && v.lineRight >=blackLevel);
	},
	[&](SensorValues v){
		stringstream s;
	        s << "Left: " << v.lineLeft << " Right: " << v.lineRight << " Center: " << v.lineCenter;
		Logger::logMessage(s.str());
		//setLeft(motorMax *((blackMax - v.lineLeft) / 190));
		//setRight(motorMax * ((blackMax - v.lineRight))/190);
	});
*/



}
/**
 * This is a weird function.
 *
 * Basically it captures the behavior that you want to do something with sensor values until you get some reading from the sensor values. Then you want to stop becuase you've achieved the goal you want.
 * An example usage would be
 *
 * applyfuncuntilpredicateandstop(allAreEqual,goForward);
 *
 * p and f should both be functions with the paramater of one sensorvalue
 * p should return a bool
 * f should be void
 * this function applies f until p is true
 *
 * also stops at end
 */
template<typename Predicate, typename Func>
void FunMotorController::applyFuncUntilPredicateAndStop(Predicate p, Func f){
	while(true) {
		SensorValues s = Sensors::read();
		if(p(s)){ break; }
		f(s);
	}
	stopAll();
}
