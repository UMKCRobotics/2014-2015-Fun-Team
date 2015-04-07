#include "RobotState.h"
#include "WorldSensor.h"
#ifndef FUN_MAZE_SOLVER_H
#define FUN_MAZE_SOLVER_H

namespace FunMazeSolver{
	/*
	 * Given the current state of the robot and a set of openings
	 * return what direction the robot should turn to face.
	 * Should always turn to the right.
	 */
	Cardinal doRightHand(RobotState r,Openings openings);
}

#endif
