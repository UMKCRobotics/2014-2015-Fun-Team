#ifndef NAVIGATION_h
#define NAVIGATION_h
#include "RobotState.h"
#include "Cardinal.h"
#include "ConfigManager.h"
#include <string>

using std::string;



/**
 * The navigation object is what stores the path and calculates the critical path
 *
 * The algorithm works by saving the direction the robot needs to go to properly leave the square in the map at some index
 *
 */
class Navigation
{
	public:
		
	/**
	 * Initialize a new navigation object with the configuration
	 * that has been passed
	 */
	Navigation(Configuration* config);
	/*
	 * Update the map at the position of the robot in current_state 
	 * 
	 * @param:current_state - Represents the current state of the robot
	 * @param:dir - The direction in the direction the robot should go to leave this square
	 */
	void updateMap(RobotState current_state, Cardinal dir);
	/*
	 * Loads up a path from the filesystem
	 */
	void loadPath();
	/*
	 * Given a robot state, return what direction the robot should go next
	 *
	 * Note: This only works after the robot has built up some map
	 */
	Cardinal getCardinalToNextNode(RobotState current_state);
	/*
	 * Writes the current map out to the filesystem at filelocation
	 */
	void storePath();
	/**
	 * Returns whether the robot has reached the final node. After the robot has reached the final node the navigation should no longer be updated
	 * as it should simply follow the righthand rule until it hits the begining again.
	 *
	 * If navigation is updated the critical path algorithm may no longer work
	 */
	bool inFinalNode(RobotState state);
	/**
	 * Returns a pretty printed version of the array. Very useful for debugging
	 */
	string toString();
	
	private:
	Cardinal map[50];
	string fileLocation;

	Configuration* config;

	void logNavigationMessage(string);
	void logNavigationError(string);

	template<typename Func>
	void applyToFileStream(Func f);
	
};

#endif
