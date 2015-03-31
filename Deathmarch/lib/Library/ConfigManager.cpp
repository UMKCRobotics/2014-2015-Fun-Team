#include "ConfigManager.h"


Configuration* ConfigurationFactory::constructBlankConfig(){
	return new Configuration;
};

Configuration* ConfigurationFactory::createConfiguration()
{
	Configuration config;
	
	int roundPin = ;
	int phasePin = ;
	
	pinMode(roundPin, INPUT);
	pinMode(phasePin, INPUT);
	
	
	if(digitalRead(roundPin) == HIGH) {
		config.round = 1;
		config.boardXDimension = 5;
		config.boardYDimension = 5;
		config.matchTime = 180;
		config.startNode = 48;
		config.endNode = 9;
		
	}
	else {
		config.round = 2;
		config.boardXDimension = 6;
		config.boardYDimension = 6;
		config.matchTime = 240;
		config.startNode = 48;
		config.endNode = 1;
		
	}
	
	
	if(digitalRead(phasePin) == HIGH) {
		config.phase = 1;
	}
	else {
		config.phase = 2;
	}	
	
	return &config;
}
