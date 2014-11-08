#include "Cardinal.h"
#include "ConfigManager.h"
#include "RobotState.h"
#include <iostream>
#include  "BlackADC.h"
#include "Timing.h"
#include <unistd.h>

void analogTest();

int main(void){
	Configuration* config = ConfigurationFactory::constructBlankConfig();
	RobotState* robot = new RobotState(config);

	analogTest();

	std::cout << "Congraturations, I compile!" << std::endl;
	return 0;
}

void analogTest() {
    Timing adcTiming;

    adcTiming.startMeasure("1. Constructor");
    BlackLib::BlackADC analog(BlackLib::AIN0);
    adcTiming.endMeasure("1. Constructor");

    while (true) {
        adcTiming.startMeasure("2. BlackADC::getValue()");
        std::cout << analog.getValue() << '\n';
        adcTiming.endMeasure("2. BlackADC::getValue()");
        sleep(1);
    }
}
