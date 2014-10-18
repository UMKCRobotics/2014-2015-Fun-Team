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
  	int pin = GPIO::GPIOConst::getInstance()->getGpioByKey("AIN0");
	std::cout << gp->getValue(pin);

	gp->clean();

	delete gp;


	std::cout << "Congraturations, I compile!" << std::endl;
	return 0;
}
