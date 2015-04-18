#include "MotorController.h"
#include "Pins.h"
#include "Arduino.h"
#include "RedBot.h"
#include "WorldSensor.h"

FunMotorController::FunMotorController(){
  justTurnedLeft=false;
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
  turnLeft();
  turnLeft();
}
void FunMotorController::turnLeft(){
  alignToIRs();
  justTurnedLeft = true;
  frontMotors.leftDrive(MAX_REVERSE_TURN_SPEED);
  frontMotors.rightDrive(MAX_TURN_SPEED);
  SerialCom::motorsLeftTurn();
  delay(TURN_DELAY_L/2+20);
  //while(!allLineSensorsOnBlack()){} //this is why i miss frp
  stopAll();
  delay(75);

  frontMotors.leftDrive(MAX_REVERSE_TURN_SPEED);
  frontMotors.rightDrive(MAX_TURN_SPEED);
  SerialCom::motorsLeftTurn();
  delay(TURN_DELAY_L/2+20);
  //while(!allLineSensorsOnBlack()){} //this is why i miss frp
  stopAll();

  delay(10);
  alignToIRs();
	
}
void FunMotorController::turnRight(){
  
  if(justTurnedLeft == true){
    SerialCom::redLedOn();
    SerialCom::greenLedOn();
    return;
  }
  alignToIRs();
  justTurnedLeft = false;
  frontMotors.leftDrive(MAX_TURN_SPEED);
  frontMotors.rightDrive(MAX_REVERSE_TURN_SPEED);
  SerialCom::motorsRightTurn();
  delay(TURN_DELAY_R/2 + 20); 
  stopAll();

  delay(75);

  frontMotors.leftDrive(MAX_TURN_SPEED);
  frontMotors.rightDrive(MAX_REVERSE_TURN_SPEED);
  SerialCom::motorsRightTurn();
  delay(TURN_DELAY_R/2 + 20); 

  // while(!allLineSensorsOnBlack()){} //this is why i miss frp:wa
  stopAll();
  delay(10);

  SerialCom::motorsFullForward();
  frontMotors.rightDrive(MAX_SPEED_R-50);
  frontMotors.leftDrive(MAX_SPEED_L-50);
  delay(10);

  stopAll();
  alignToIRs();

}
void FunMotorController::moveForwardOneSquare(){
  
  if(analogRead(FRONT_IR) > 200){
    SerialCom::yellowLedOn();
    SerialCom::greenLedOn();
    turnLeft();
    return;
  }
  
  justTurnedLeft = false;
	SerialCom::motorsFullForward();

	frontMotors.rightDrive(MAX_SPEED_R-50);
	frontMotors.leftDrive(MAX_SPEED_L-50);

	delay(400);
	while(!allLineSensorsOnBlack()){
		int potentialNextRightValue = MAX_SPEED_R - rightLineRead();
		int potentialNextLeftValue = MAX_SPEED_L - leftLineRead();
		int nextRightValue = (potentialNextRightValue > MIN_SPEED)? potentialNextRightValue : MIN_SPEED;
		int nextLeftValue = (potentialNextLeftValue > MIN_SPEED) ? potentialNextLeftValue : MIN_SPEED;
		frontMotors.leftDrive(nextLeftValue);
		frontMotors.rightDrive(nextRightValue);
	}
	//frontMotors.drive(-100);
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
/*
void FunMotorController::alignToLine(){
  bool goRight;
  while(!analogRead())
}
*/
void FunMotorController::alignToIRs(){
  IRSensorReadings readings = FunWorldSensor::medianThreeSensors();
  if (readings.frontRightIR > 200 && readings.backRightIR > 200 && (abs(readings.frontRightIR - readings.backRightIR) > 40)) {

    if(readings.frontRightIR < readings.backRightIR){
      //adjust left 
      frontMotors.leftDrive(MAX_TURN_SPEED);
      frontMotors.rightDrive(MAX_REVERSE_TURN_SPEED);
      SerialCom::yellowLedOn();
      SerialCom::motorsRightTurn();
      delay(100); 
      stopAll();
      SerialCom::yellowLedOff();
    }
    else{
      //adjust right
      frontMotors.leftDrive(MAX_REVERSE_TURN_SPEED);
      frontMotors.rightDrive(MAX_TURN_SPEED);
      SerialCom::motorsLeftTurn();
      SerialCom::yellowLedOn();
      delay(100); 
      stopAll();
      SerialCom::yellowLedOff();

    }
  }
  
}
