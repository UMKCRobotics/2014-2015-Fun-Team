#include "Cardinal.h"
#include "ConfigManager.h"
#include "RobotState.h"
#include "GPIOManager.h"
#include "GPIOConst.h"
#include <highgui.h>
#include <iostream>

int main(void){
	Configuration* config = ConfigurationFactory::constructBlankConfig();
	RobotState* robot = new RobotState(config);
	GPIO::GPIOManager* gp = GPIO::GPIOManager::getInstance();
	gp->clean();
	delete config;
	delete robot;
	delete gp;


	cv::VideoCapture capture(0);
	if (!capture.isOpened()) {
		std::cerr << "Unable to open the camera" << std::endl;
		return(10);
	}
	std::cout << "Congraturations, I compile!" << std::endl;
	return 0;
}
