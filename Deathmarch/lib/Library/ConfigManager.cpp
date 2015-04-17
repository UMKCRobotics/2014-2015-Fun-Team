#include "ConfigManager.h"
#include "Pins.h"
#include "Arduino.h"


Configuration* ConfigurationFactory::constructBlankConfig(){
	return new Configuration;
};

Configuration* ConfigurationFactory::createConfiguration()
{
	Configuration config;

	pinMode(LEFT_SWITCH, INPUT);
	pinMode(RIGHT_SWITCH, INPUT);
	
	
	if(digitalRead(LEFT_SWITCH) == HIGH) {
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
	
	
	if(digitalRead(RIGHT_SWITCH) == HIGH) {
		config.phase = 1;
	}
	else {
		config.phase = 2;
	}	
	
	return &config;
}
