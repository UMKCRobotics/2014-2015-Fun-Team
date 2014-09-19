#include "Cardinal.h"
#include "ConfigManager.h"
#include "RobotState.h"
#include "GPIOManager.h"
#include "GPIOConst.h"
#include <iostream>

int main(void){
	Configuration* config = ConfigurationFactory::constructBlankConfig();
	RobotState* robot = new RobotState(config);
	GPIO::GPIOManager* gp = GPIO::GPIOManager::getInstance();
	gp->clean();
	delete config;
	delete robot;
	delete gp;
	
	std::cout << "Congraturations, I compile!" << std::endl;
	return 0;
}
