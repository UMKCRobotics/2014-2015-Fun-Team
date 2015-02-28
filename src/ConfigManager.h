#ifndef CONFIG_H
#define CONFIG_H

struct Configuration{
	int phase;
	int round;
	bool scanForCharacters;
	int startNode;
	int endNode;
	int boardXDimension;
	int boardYDimension;
	int matchTime;
};

class ConfigurationFactory{
	public:
		static Configuration* createConfiguration(){
			return ConfigurationFactory::constructBlankConfig();
		}
		static Configuration* constructBlankConfig();
};
#endif
