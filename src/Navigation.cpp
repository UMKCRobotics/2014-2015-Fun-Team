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
	applyToFileStream([&](fstream& file){
				for(int i=0; i<50; ++i){
					file << indexToChar(i);
				}
			});
}

void Navigation::loadPath(){
	applyToFileStream([&](fstream& file){
				for(int i = 0; i < 50; ++i){
					char tmp;
					file >> tmp;
					map[i] = charToCardinal(tmp);
				}
			});
}

template<typename Func>
void Navigation::applyToFileStream(Func f){
	fstream file(fileLocation);
	if(!file){
		Logger::logError("Navigation couldn't open file!");
	}
	f(file);
}

bool Navigation::inFinalNode(RobotState* state)
{
	return state->currentNode == config->endNode;
}
char Navigation::indexToChar(int i){
	switch(map[i]){
		case NORTH:
			return 'n';
		case SOUTH:
			return 's';
		case WEST:	
			return 'w';
		case EAST:
			return 'e';
	}
}
Cardinal Navigation::charToCardinal(char c){
	switch(c){
		case 'n':
			return Cardinal::NORTH;
		case 's':
			return Cardinal::SOUTH;
		case 'e':
			return Cardinal::EAST;
		case 'w':
			return Cardinal::WEST;
	}
}


