#include "Cardinal.h"
#include "ConfigManager.h"
#include "RobotState.h"
#include <iostream>

int main(void){
	Configuration* config = ConfigurationFactory::constructBlankConfig();
	RobotState* robot = new RobotState(config);

	std::cout << "Congraturations, I compile!" << std::endl;
	return 0;
}
