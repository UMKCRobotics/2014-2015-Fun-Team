#include "FunMazeSolver.h"


Cardinal FunMazeSolver::doRightHand(RobotState r,Openings openings){
	if(openings.NoneOpen) return NONE;
	Cardinal direction;
	switch(r.currentDirection){
		case NORTH:
			if(openings.EastOpen) {
				direction = EAST;
				break;
			}
			if(openings.NorthOpen) {
				direction = NORTH;
				break;
			}
			if(openings.WestOpen) {
				direction = WEST;
				break;
			}
			if(openings.SouthOpen) {
				direction = SOUTH;
				break;
			}
		case EAST:
			if(openings.SouthOpen) {
				direction = SOUTH;
				break;
			}
			if(openings.EastOpen) {
				direction = EAST;	
				break;
			}
			if(openings.NorthOpen) {
				direction = NORTH;
				break;
			}
			if(openings.WestOpen){
			       	direction = WEST;
				break;
			}
		case SOUTH:
			if(openings.WestOpen) {
				direction = WEST;
				break;
			}
			if(openings.SouthOpen) {
				direction = SOUTH;
				break;
			}
			if(openings.EastOpen){
				direction = EAST;
				break;
			}
			if(openings.NorthOpen){
				direction = NORTH;
				break;
			}
		case WEST:
			if(openings.NorthOpen){
				direction = NORTH;
				break;
			}
			if(openings.WestOpen){
				direction = WEST;
				break;
			}
			if(openings.SouthOpen){
				direction = SOUTH;
				break;
			}
			if(openings.EastOpen){
				direction = EAST;
				break;
			}
		}
		/*
		stringstream ss;
		ss << "Robot is currently facing " << cardinalToString(r.currentDirection) << " therefore it should be turned to " << cardinalToString(direction);
		logMazeSolverMessage(ss.str());
		*/
		return direction;
}
