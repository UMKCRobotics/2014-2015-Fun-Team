#include "RobotState.h"
#include "Cardinal.h"
#include "ConfigManager.h"
#include <string>

using std::string;

#ifndef NAVIGATION_h
#define NAVIGATION_h

class Navigation
{
	public:
		
	Navigation(Configuration* config);
	void updateMap(RobotState current_state, Cardinal dir);
	void loadPath();
	Cardinal getCardinalToNextNode(RobotState current_state);
	void storePath();
	bool inFinalNode(RobotState* state);
	
	private:
	Cardinal map[50];
	const string fileLocation = "/tmp/robot/navigation.txt";
	Configuration* config;
	char indexToChar(int i);
	Cardinal charToCardinal(char c);

	template<typename Func>
	void applyToFileStream(Func f);
	
};

#endif
