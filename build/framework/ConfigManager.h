
#ifndef CONFIGURATION_H 
#define CONFIGURATION_H
struct Configuration{
	int phase;
	int round;
	bool scanForCharacters;
	int startNode;
	int endNode;
	int boardXDimension;
	int boardYDimension;
};

class ConfigurationFactory{
	public:
		virtual Configuration* createConfiguration() = 0;
		static Configuration* constructBlankConfig();
};
#endif
