/*
 * This is used to carry the current state of the robot
 * This makes it easier to test functions, I promise
*/

#include "Cardinal.h"
#include "ConfigManager.h"

#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

struct RobotState{
	/*
	 * The current direction the robot is facing
	 */
	Cardinal currentDirection;
	/**
	 * The node the robot is currently in
	 */
	int currentNode;
	RobotState(){
		currentNode = 0;
		currentDirection = NORTH;
	}
	/**
	 * Construct a new robot state from a given configuration
	 */
	RobotState(Configuration* config){
		currentNode = config->startNode;
		currentDirection = NORTH;
	}
  void init(Configuration* config){
    currentNode = config->startNode;
    currentDirection = NORTH;
  }
};
#endif
