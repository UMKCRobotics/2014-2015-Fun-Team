#include <string>
#include "Cardinal.h"

std::string cardinalToString(Cardinal c){
	switch(c){
		case NORTH:
			return "NORTH";
		case SOUTH:
			return "SOUTH";
		case WEST:
			return "WEST";
		case EAST:
			return "EAST";
	}
	Logger::logError("Cardinal to string cast failed!");
	return "";
}

Cardinal stringToCardinal(std::string s){
	//the person who wrote string comparison is a goofball
	if(s.compare("NORTH") == 0) return NORTH;
	if(s.compare("SOUTH") == 0) return SOUTH;
	if(s.compare("EAST") == 0) return EAST;
	if(s.compare("WEST") == 0) return WEST;

	Logger::logError("String to Cardinal cast failed, returning north to avoid errors");
	return NORTH;
}
