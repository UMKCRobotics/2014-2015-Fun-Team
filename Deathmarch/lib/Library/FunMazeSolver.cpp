#include "FunMazeSolver.h"
 
bool legitNode(int node, Configuration c)
{
	if(c.round == 1)
	{
		if(node == 1 || node == 2 || node == 3 || node == 4 || node == 5 || node == 6 || node == 7 || node == 8 || node == 15 || node == 22 || node == 29  || node == 36 || node == 43  || node == 44
		|| node == 45  || node == 46  || node == 47  || node == 14  || node == 21  || node == 28  || node ==35  || node == 42  || node == 49)
		{
			return false;
		}
		return true;
	}
	if(c.round == 2)
	{
		if(node == 7  || node == 14  || node == 21  || node == 28  || node == 35  || node == 42  || node == 49  || node == 43  || node == 44  || node == 45  || node == 46  || node == 47)
		{
			return false;
		}
		return true;
	}	
	
	
	
}


Cardinal FunMazeSolver::doRightHand(RobotState r,Openings openings, Configuration c){
	if(openings.NoneOpen) return NONE;
	switch(r.currentDirection){
		case NORTH:
			if(openings.EastOpen) {
				if(legitNode(currentNode + 1,c))
				return EAST;
			}
			if(openings.NorthOpen) {
				if(legitNode(currentNode - 7,c))
				return NORTH;
			}
			if(openings.WestOpen) {
				if(legitNode(currentNode - 1,c))
				return WEST;
			}
			if(openings.SouthOpen) {
				if(legitNode(currentNode + 7,c))
				return SOUTH;
			}
		case EAST:
			if(openings.SouthOpen) {
				if(legitNode(currentNode + 7,c)) 
				return SOUTH;
			}
			if(openings.EastOpen) {
				if(legitNode(currentNode + 1,c))
				return EAST;	
			}
			if(openings.NorthOpen) {
				if(legitNode(currentNode - 7,c))
				return NORTH;
			}
			if(openings.WestOpen){
				if(legitNode(currentNode - 1,c))
			    return WEST;
			}
		case SOUTH:
			if(openings.WestOpen) {
				if(legitNode(currentNode - 1,c))
				return WEST;
			}
			if(openings.SouthOpen) {
				if(legitNode(currentNode + 7,c)) 
				return SOUTH;
			}
			if(openings.EastOpen){
				if(legitNode(currentNode + 1,c))
				return EAST;
			}
			if(openings.NorthOpen){
				if(legitNode(currentNode - 7,c))
				return NORTH;
			}
		case WEST:
			if(openings.NorthOpen){
				if(legitNode(currentNode - 7,c))
				return NORTH;
			}
			if(openings.WestOpen){
				if(legitNode(currentNode - 1,c))
				return WEST;
			}
			if(openings.SouthOpen){
				if(legitNode(currentNode + 7,c)) 
				return SOUTH;
			}
			if(openings.EastOpen){
				if(legitNode(currentNode + 1,c))
				return EAST;
			}
		}
		/*
		stringstream ss;
		ss << "Robot is currently facing " << cardinalToString(r.currentDirection) << " therefore it should be turned to " << cardinalToString(direction);
		logMazeSolverMessage(ss.str());
		*/
}
