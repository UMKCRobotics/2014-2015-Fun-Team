#include <Arduino.h>
#include "MotorController.h"
#include "FunMazeSolver.h"
#include "WorldSensor.h"
#include "Cardinal.h"
#include "ConfigManager.h"
#include "Navigation.h"
#include "Pins.h"
void setup();
void phase1();
void phase2();
void loop();
#line 1 "src/sketch.ino"
//#include "MotorController.h"
//#include "FunMazeSolver.h"
//#include "WorldSensor.h"
//#include "Cardinal.h"
//#include "ConfigManager.h"
//#include "Navigation.h"
//#include "Pins.h"

FunMotorController mc;
RobotState state;
Configuration* conf = ConfigurationFactory::createConfiguration();
Navigation nav(conf);

void setup()
{
	mc.stopAll();
	SerialCom::init();
	delay(500);
}
void phase1(){
  int leftTurns = 0;
  nav.updateMap(state,NORTH);
  state = mc.move(state,NORTH);
  while(!nav.inFinalNode(state)){
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
      mc.turnLeft();
      leftTurns++;
      switch(state.currentDirection){
	  case NORTH:
	    state.currentDirection = WEST;
	    break;
          case SOUTH:
	    state.currentDirection = EAST;
	    break;
          case EAST:
	    state.currentDirection = NORTH;
	    break;
          case WEST:
	    state.currentDirection = SOUTH;
	    break;
      }
     
       IRSensorReadings readings = FunWorldSensor::medianThreeSensors();
      if (readings.frontIR < 200){
	mc.move(state,state.currentDirection);
	//CHANGE STATE HERE
      }
      

      if(leftTurns == 2){	
	nav.updateMap(state,state.currentDirection);
	state = mc.move(state,state.currentDirection);
	leftTurns = 0;
      }
    }	
    else{
      SerialCom::redLedOff();
      SerialCom::greenLedOn();
    	
      nav.updateMap(state,nextCard);
      mc.move(state,nextCard);
      state.currentDirection = nextCard;
      delay(200);
    }
  }
  
}
void phase2(){
  while(!nav.inFinalNode(state)){
    Cardinal nextCard = nav.getCardinalToNextNode(state);
    state = mc.move(state,nextCard);
  }

}
void loop()
{
  //while(!SerialCom::testSerial){}
  while(digitalRead(BUTTON)==LOW){}
 
  for(int i = 0; i < 10; ++i){
    analogRead(FRONT_IR);
    analogRead(FORWARD_RIGHT_IR);
    analogRead(BACKWARD_RIGHT_IR);
    delay(35);
  }
  delay(200);
  state.init(conf);
  phase1();
  //Reset the configuration between rounds
  while(digitalRead(BUTTON)==LOW){}
  state.init(conf);
  phase2();
}
