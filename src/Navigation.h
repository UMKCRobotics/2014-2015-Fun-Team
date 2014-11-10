#ifndef NAVIGATION_h
#define NAVIGATION_h
#include "RobotState.h"
#include "Cardinal.h"
#include "ConfigManager.h"
#include <string>

using std::string;



class Navigation
{
	public:
		
	Navigation(Configuration* config);
	void updateMap(RobotState current_state, Cardinal dir);
	void loadPath();
	Cardinal getCardinalToNextNode(RobotState current_state);
	void storePath();
	bool inFinalNode(RobotState* state);
	string toString();
	
	private:
	Cardinal map[50];
	const string fileLocation = "/tmp/robot/navigation.txt";
	Configuration* config;

	void logNavigationMessage(string);
	void logNavigationError(string);

	template<typename Func>
	void applyToFileStream(Func f);
	
};

#endif
