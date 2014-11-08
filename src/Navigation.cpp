#include "Navigation.h"
#include "Logger.h"
#include <fstream>

Navigation::Navigation(Configuration* config) : config(config)
{
	//TODO: Check if filelocation is readable?
}

void Navigation::updateMap(RobotState current_state, Cardinal dir)
{
	map[current_state.currentNode] = dir;
}

Cardinal Navigation::getCardinalToNextNode(RobotState current_state)
{
	return map[current_state.currentNode];
}

void Navigation::storePath()
{
}

void Navigation::loadPath(){
	applyToFileStream([&](fstream file){
				for(int i = 0; i < 50; ++i){
					Cardinal tmp;
					file >> tmp;
					map[i] = tmp;
				}
			}
}




void applyToFileStream(void f(fstream file)){
	fstream file(fileLocation);
	if(!file){
		Logger::logError("Navigation couldn't open file!");
	}
	f(file);

bool Navigation::inFinalNode(RobotState* state)
{
	return state->currentNode == config->endNode;
}



