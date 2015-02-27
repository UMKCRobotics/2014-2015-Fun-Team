#include "Navigation.h"
#include "ConfigManager.h"
#include <iostream>
#include "RobotState.h"
#include "Cardinal.h"
#include "Notification.h"
#include "MotorController.h"
#include "FunMazeSolver.h"
#include "WorldSensor.h"
#include "Vision.h"

#include <ctime>
using std::cout;
using std::endl;

void phase_1(Configuration*);
void phase_2(Configuration*);
bool isPastTime(Configuration*, clock_t);
/*
//Screw KCKAAOS FOR NOT BELIEVING ME
int main(void){
	Logger::standardInit();
	Configuration* config = ConfigurationFactory::createConfiguration();
	FunMotorController mc;
	RobotState r(config);
	r.currentDirection = NORTH;
	mc.move(r,NORTH);
	/*
	if(config->phase == 1){
		phase_1(config);
	}
	else{
		phase_2(config);
	}
	*/
//	return 0;
//}

//Testing LED and switches
int main(void) {
	Logger::standardInit();
	Configuration* config = ConfigurationFactory::createConfiguration();
	Notifier note;

	while(bool a = true) {
		if(config->round == 1) {
			note.onGreen();
			if(config->phase == 2)
				note.onYellow();
		}
		
		if(config->round == 2) {
			note.onRed();
			if(config->phase == 2)
				note.onYellow();
		}
		
		if(config->round == 3) {
			note.onYellow();
			if(config->phase == 2) {
				note.offYellow();
				note.onRed();
				note.onGreen();
			}
		}
	}
		
	
	
}

/*
void phase_1(Configuration* config){
	Navigation nav(config);
	RobotState state(config);
	Cardinal nextCard;
	FunMotorController motorController;
	Vision vision;
	std::clock_t begin = std::clock();
	bool visitedFinalNode = false;
	while(!isPastTime(config,begin)){
		nextCard = FunMazeSolver::doRightHand(state,FunWorldSensor::computeOpenings());
		if(!visitedFinalNode){
			nav.updateMap(state,nextCard);
		}
		state = motorController.move(state,nextCard);
		if(config->round != 1){
			vision.scanForCharacters(state);
		}
		if(nav.inFinalNode(state) && !visitedFinalNode){
			visitedFinalNode = true;
			nav.storePath();
			Notifier::mazeComplete();
			Logger::logMessage("Reached finish node!");
		}
	}
	Logger::logMessage("Time over!");
}
void phase_2(Configuration* config){
	Navigation nav(config);

	nav.loadPath();
	RobotState state(config);
	Cardinal nextCard;
	FunMotorController motorController;
	while(!nav.inFinalNode(state)){
		nextCard = nav.getCardinalToNextNode(state);
		state = motorController.move(state,nextCard);
	}
	Notifier::mazeComplete();
}
bool isPastTime(Configuration* config, clock_t start){
	return (double(std::clock() - start) / CLOCKS_PER_SEC * 60) >= config->matchTime;
}

*/
