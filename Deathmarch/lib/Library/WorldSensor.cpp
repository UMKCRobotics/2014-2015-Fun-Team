#include "WorldSensor.h"

Openings::Openings(){
		bool NorthOpen = false;
		bool SouthOpen = false;
		bool EastOpen = false;
		bool WestOpen = false;
		bool NoneOpen = false;
}

void Openings::open(Cardinal card){
	switch(card){
		case NORTH:
			NorthOpen = true;
			break;
		case SOUTH:
			SouthOpen = true;
			break;
		case EAST:
			EastOpen = true;
			break;
		case WEST:
			WestOpen = true;
			break;
	}
}

