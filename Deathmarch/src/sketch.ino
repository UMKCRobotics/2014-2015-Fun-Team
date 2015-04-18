#include "MotorController.h"
#include "FunMazeSolver.h"
#include "WorldSensor.h"
#include "Cardinal.h"
#include "ConfigManager.h"
#include "Navigation.h"
#include "Pins.h"

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
  Cardinal prevCard = NONE;
  int moves = 0;
  while(!nav.inFinalNode(state)){
    Openings openings = FunWorldSensor::computeOpenings(state);
    if(openings.NoneOpen){
      SerialCom::yellowLedOn();
    }
    else{
      SerialCom::yellowLedOff();
    }
    Cardinal nextCard = FunMazeSolver::doRightHand(state,openings,*conf);
    if (nextCard == EAST && (moves == 1 || moves == 0)){
      //DON'T FUCKING DO THIS YOU PIECE OF SHIT ROB
      prevCard = NORTH;
      nav.updateMap(state,state.currentDirection);
      state = mc.move(state,state.currentDirection);

    }
    else if(nextCard==NONE){
      SerialCom::greenLedOff();
      SerialCom::redLedOn();
      mc.turnLeft();
      switch(state.currentDirection){
	  case NORTH:
	    state.currentDirection = WEST;
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
      prevCard = state.currentDirection;
    }
    else if(nextCard == prevCard){
      //ROB PLEASE STOP DON'TING SHIT 
      SerialCom::yellowLedOn();
      SerialCom::greenLedOn();
      nav.updateMap(state,state.currentDirection);
      state = mc.move(state,state.currentDirection);
      prevCard == NORTH;
      delay(500);
    }
    else{
      SerialCom::redLedOff();
      SerialCom::greenLedOn();
      nav.updateMap(state,nextCard);
      state = mc.move(state,nextCard);
      prevCard = state.currentDirection;
      delay(50);
    }
    SerialCom::redLedOff();
    SerialCom::yellowLedOff();
    SerialCom::greenLedOff();
    moves++;
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
  SerialCom::greenLedOn();
  //while(!SerialCom::testSerial){}
  while(digitalRead(BUTTON)==LOW){}
 
 
  for(int i = 0; i < 10; ++i){
    analogRead(FRONT_IR);
    analogRead(FORWARD_RIGHT_IR);
    analogRead(BACKWARD_RIGHT_IR);
    delay(35);
  }
  conf = ConfigurationFactory::createConfiguration();
  state.init(conf);
  phase1();
  SerialCom::redLedOn();
  delay(1000);
  SerialCom::greenLedOn();
  while(digitalRead(BUTTON)==LOW){}

  conf = ConfigurationFactory::createConfiguration();
  state.init(conf);
  phase2();
}
