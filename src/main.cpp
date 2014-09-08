#include "Cardinal.h"
#include "ConfigManager.h"
#include "RobotState.h"
#include "gpio.h"

int main(void){
	Configuration* config = ConfigurationFactory::constructBlankConfig();
	RobotState* robot = new RobotState(config);
	init();
	return 0;
}
