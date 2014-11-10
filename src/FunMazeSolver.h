#include <set>
#include "RobotState.h"
using std::set;
#ifndef FUN_MAZE_SOLVER_H
#define FUN_MAZE_SOLVER_H

namespace FunMazeSolver{
	Cardinal computeOpenings(RobotState r,set<Cardinal> openings);
}

#endif
