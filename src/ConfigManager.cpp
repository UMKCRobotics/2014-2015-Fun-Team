#include "ConfigManager.h"
#include "GPIOManager.h"
#include "GPIOConst.h"



Configuration* ConfigurationFactory::constructBlankConfig(){
	return new Configuration;
};

Configuration* ConfigurationFactory::createConfiguration()
{
	Configuration config;
	
	if(getValue(9) == HIGH) {
		config.round = 1;
		config.scanForCharacters = false;
		config.boardXDimension = 5;
		config.boardYDimension = 5;
		config.matchTime 180;
		config.startNode = 48;
		config.endNode = 9;
		
	}
	else {
		if(getValue(8) == LOW)  {
			config.round = 2;
			config.boardXDimension = 6;
			config.boardYDimension = 6;
			config.matchTime 240;
			config.startNode = 48;
			config.endNode = 1;
		}
		else {
			config.round = 3;
			config.boardXDimension = 7;
			config.boardYDimension = 7;
			config.matchTime = 300;
			config.startNode = 49;
			config.endNode = 1;
		}
	
	}
	
	
	if(getValue(81) == LOW) {
		config.phase = 1;
		if(config.round != 1)
			config.scanForCharacters = true;
	}
	else {
		config.phase = 2;
		config.scanForCharacters = false;
	}	
	
	return new Configuration = &config;
}
