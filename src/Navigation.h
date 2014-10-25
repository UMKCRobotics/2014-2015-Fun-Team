#include "RobotState.h"
#include "Cardinal.h"
#include <string>


#ifndef NAVIGATION_h
#define NAVIGATION_h

class Navigation
{
	public:
		
	Navigation();
	void updateMap(RobotState current_state, Cardinal dir);
	void loadPath();
	Cardinal getCardinalToNextNode(RobotState current_state);
	void storeCriticalPath();
	bool inFinalNode();
	
	private:
	Cardinal map[50];
	
	
	
};

#endif
