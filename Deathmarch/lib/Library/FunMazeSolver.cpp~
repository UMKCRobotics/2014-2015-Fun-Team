#include "FunMazeSolver.h"


Cardinal FunMazeSolver::doRightHand(RobotState r,Openings openings){
	if(openings.NoneOpen) return NONE;
	switch(r.currentDirection){
		case NORTH:
			if(openings.EastOpen) {
				return EAST;
				break;
			}
			if(openings.NorthOpen) {
				return NORTH;
			}
			if(openings.WestOpen) {
				return WEST;
			}
			if(openings.SouthOpen) {
				return SOUTH;
			}
		case EAST:
			if(openings.SouthOpen) {
				return SOUTH;
			}
			if(openings.EastOpen) {
				return EAST;	
			}
			if(openings.NorthOpen) {
				return NORTH;
			}
			if(openings.WestOpen){
			       	return WEST;
			}
		case SOUTH:
			if(openings.WestOpen) {
				return WEST;
			}
			if(openings.SouthOpen) {
				return SOUTH;
			}
			if(openings.EastOpen){
				return EAST;
			}
			if(openings.NorthOpen){
				return NORTH;
			}
		case WEST:
			if(openings.NorthOpen){
				return NORTH;
			}
			if(openings.WestOpen){
				return WEST;
			}
			if(openings.SouthOpen){
				return SOUTH;
			}
			if(openings.EastOpen){
				return EAST;
			}
		}
		/*
		stringstream ss;
		ss << "Robot is currently facing " << cardinalToString(r.currentDirection) << " therefore it should be turned to " << cardinalToString(direction);
		logMazeSolverMessage(ss.str());
		*/
}
