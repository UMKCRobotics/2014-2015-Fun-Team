#include "Navigation.h"

Navigation::Navigation()
{
	;
}

void Navigation::updateMap(RobotState current_state, Cardinal dir)
{
	map[current_state.currentNode] = dir;
}

Cardinal Navigation::getCardinalToNextNode(RobotState current_state)
{
	return map[current_state.currentNode];
}

void storeCriticalPath()
{
	
}

bool inFinalNode()
{
	
}




