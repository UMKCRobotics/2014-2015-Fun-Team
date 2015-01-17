#include <set>
using std::set;

#ifndef FunWorldSensor
#define FunWorldSensor

namespace FunMazeSolver{
	/**
	 * Uses the IR sensors to compute what walls around the
	 * robot are open
	 */
	set<Cardinal> computeOpenings();
}
