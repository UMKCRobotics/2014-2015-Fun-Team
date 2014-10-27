#include "Navigation.h"

Navigation::Navigation(Configuration* config) : config(config)
{
	//TODO: Check if filelocation is readable?
}

void Navigation::updateMap(RobotState current_state, Cardinal dir)
{
	map[current_state.currentNode] = dir;
}

Cardinal Navigation::getCardinalToNextNode(RobotState current_state)
{
	return map[current_state.currentNode];
}

void Navigation::storeCriticalPath()
{
	
}

bool Navigation::inFinalNode(RobotState* state)
{
	return state->currentNode == config->endNode;
}



