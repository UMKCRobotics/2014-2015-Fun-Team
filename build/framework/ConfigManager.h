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
		static Configuration* createConfiguration();
		static Configuration* constructBlankConfig();
};
