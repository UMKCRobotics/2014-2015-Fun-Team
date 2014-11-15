#include "FunMazeSolver.h" 
#include "Logger.h"
#include <sstream>

void logMazeSolverError(string s){
	Logger::logError("Maze Solver: " + s);
}
void logMazeSolverMessage(string s){
	Logger::logMessage("Maze Solver: " + s);
}
bool openingsContains(set<Cardinal> openings, Cardinal value){
	return openings.find(value) != openings.end();
}
Cardinal FunMazeSolver::computeOpenings(RobotState r,set<Cardinal> openings){
	if(openings.empty()) logMazeSolverError("Passed an empty set!");
	Cardinal direction;
	switch(r.currentDirection){
		case NORTH:
			if(openingsContains(openings,EAST)) {
				direction = EAST;
				break;
			}
			if(openingsContains(openings,NORTH)) {
				direction = NORTH;
				break;
			}
			if(openingsContains(openings,WEST)) {
				direction = WEST;
				break;
			}
			if(openingsContains(openings,SOUTH)) {
				direction = SOUTH;
				break;
			}
		case EAST:
			if(openingsContains(openings,SOUTH)) {
				direction = SOUTH;
				break;
			}
			if(openingsContains(openings,EAST)) {
				direction = EAST;	
				break;
			}
			if(openingsContains(openings,NORTH)) {
				direction = NORTH;
				break;
			}
			if(openingsContains(openings,WEST)){
			       	direction = WEST;
				break;
			}
		case SOUTH:
			if(openingsContains(openings,WEST)) {
				direction = WEST;
				break;
			}
			if(openingsContains(openings,SOUTH)) {
				direction = SOUTH;
				break;
			}
			if(openingsContains(openings,EAST)){
				direction = EAST;
				break;
			}
			if(openingsContains(openings,NORTH)){
				direction = NORTH;
				break;
			}
		case WEST:
			if(openingsContains(openings,NORTH)){
				direction = NORTH;
				break;
			}
			if(openingsContains(openings,WEST)){
				direction = WEST;
				break;
			}
			if(openingsContains(openings,SOUTH)){
				direction = SOUTH;
				break;
			}
			if(openingsContains(openings,EAST)){
				direction = EAST;
				break;
			}
		}
		stringstream ss;
		ss << "Robot is currently facing " << cardinalToString(r.currentDirection) << " therefore it should be turned to " << cardinalToString(direction);
		logMazeSolverMessage(ss.str());
		return direction;
}



