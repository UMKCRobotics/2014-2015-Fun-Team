#include "Navigation.h"
#include "ConfigManager.h"
#include <iostream>
#include "RobotState.h"
#include "Cardinal.h"
#include "Notification.h"
#include "MotorController.h"
#include "FunMazeSolver.h"

#include <ctime>
using std::cout;
using std::endl;

void phase_1(Configuration*);
void phase_2(Configuration*);
bool isPastTime(Configuration*, clock_t);

int main(void){
	Logger::standardInit();
	Configuration* config = ConfigManager::createConfiguration();
	if(config->phase == 1){
		phase_1(config);
	}
	else{
		phase_2(config);
	}
}
void phase_1(Configuration* config){
	Navigation nav(config);
	RobotState state(config);
	Cardinal nextCard;
	FunMotorController motorController(config);
	FunWorldSensor worldSensor();
	FunMazeSolver mazeSolver();
	Vision vision;
	std::clock_t begin = std::clock();
	bool visitedFinalNode = false;
	while(!isPastTime(config,begin)){
		nextCard = mazeSolver.doRighthand(state,worldSensor.computeOpenings())
		if(!visitedFinalNode){
			nav.updateMap(state,nextCard);.
		}
		state = motorController.move(staet,nextCard);
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
	Logger::logMessage("Time over!")
}
void phase_2(Configuration* config){
	Navigation nav(config);

	nav.loadPath();
	RobotState state(config);
	Cardinal nextCard;
	FunMotorController motorController(config);
	while(!nav.inFinalNode(state)){
		nextCard = nav.getCardinalToNextNode(state);
		state = motorController.move(state,nextCard);
	}
	Notifier::mazeComplete();
}
bool isPastTime(Configuration* config, clock_t start){
	return double(std::clock() - begin) / CLOCKS_PER_SEC * 60 >= config->matchTime)
}

