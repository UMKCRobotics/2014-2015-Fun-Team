#ifndef CARDINAL_H
#define CARDINAL_H

#include "Arduino.h"
#include <string.h>

enum Cardinal { NORTH,
		SOUTH,
		EAST,
		WEST,
		NONE
};
String cardinalToString(Cardinal);
Cardinal stringToCardinal(String);
#endif
