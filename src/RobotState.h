/**
 * This is used to carry the current state of the robot
 * This makes it easier to test functions, I promise
 */

#include "Cardinal.h"

struct RobotState{
	Cardinal currentDirection;
	int currentNode;
	RobotState(Configuration* config){
		currentNode = config->startNode;
		currentDirection = NORTH;

	}
};