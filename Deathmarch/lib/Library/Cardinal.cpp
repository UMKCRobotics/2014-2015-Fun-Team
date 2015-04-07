#include <string.h>
#include "Cardinal.h"

String cardinalToString(Cardinal c){
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
	//Logger::logError("Cardinal to string cast failed!");
	return "";
}

Cardinal stringToCardinal(String s){
	//the person who wrote string comparison is a goofball
	if(s == ("NORTH")) return NORTH;
	if(s == ("SOUTH")) return SOUTH;
	if(s == ("EAST")) return EAST;
	if(s == ("WEST")) return WEST;

//	Logger::logError("String to Cardinal cast failed, returning north to avoid errors");
	return NORTH;
}
