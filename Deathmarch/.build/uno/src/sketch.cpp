#include <Arduino.h>
#include "MotorController.h"
#include "FunMazeSolver.h"
#include "WorldSensor.h"
#include "Cardinal.h"
#include "Pins.h"
void setup();
void loop();
#line 1 "src/sketch.ino"
//#include "MotorController.h"
//#include "FunMazeSolver.h"
//#include "WorldSensor.h"
//#include "Cardinal.h"
//#include "Pins.h"

FunMotorController mc;
RobotState state;

void setup()
{
	mc.stopAll();
	SerialCom::init();
	while(digitalRead(BUTTON) == LOW){}
	state.currentDirection = NORTH;
	delay(500);
}

void loop()
{
  while(!SerialCom::testSerial){}
  Openings openings = FunWorldSensor::computeOpenings(state);
  if(openings.NoneOpen){
	SerialCom::yellowLedOn();
  }
  else{
	SerialCom::yellowLedOff();
  }
  Cardinal nextCard = FunMazeSolver::doRightHand(state,openings);
  if(nextCard==NONE){
	SerialCom::greenLedOff();
	SerialCom::redLedOn();

  }	
  else{
	SerialCom::redLedOff();
	SerialCom::greenLedOn();
  }	
  mc.move(state,nextCard);
  state.currentDirection = nextCard;
  delay(400);
}
