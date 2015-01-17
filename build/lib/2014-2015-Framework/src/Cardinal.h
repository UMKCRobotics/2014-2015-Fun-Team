#ifndef CARDINAL_H
#define CARDINAL_H

#include <string>
#include "Logger.h"
using std::string;

enum Cardinal { NORTH,
		SOUTH,
		EAST,
		WEST};
string cardinalToString(Cardinal);
Cardinal stringToCardinal(string);
#endif

