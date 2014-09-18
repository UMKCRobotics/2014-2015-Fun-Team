#include "Cardinal.h"
#include "ConfigManager.h"
#include "RobotState.h"
#include "GPIOManager.h"
#include "GPIOConst.h"

int main(void){
	Configuration* config = ConfigurationFactory::constructBlankConfig();
	RobotState* robot = new RobotState(config);
	GPIO::GPIOManager* gp = GPIO::GPIOManager::getInstance();
	gp->clean();
	return 0;
}
