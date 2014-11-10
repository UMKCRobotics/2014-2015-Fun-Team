#include "Navigation.h"
#include "Logger.h"
#include <sstream>
#include <fstream>

Navigation::Navigation(Configuration* config) : config(config)
{
	map[config->startNode] = Cardinal::NORTH;

	//TODO: Check if filelocation is readable?
}

void Navigation::updateMap(RobotState current_state, Cardinal dir)
{
	stringstream ss;
	ss << "Navigation: updated " << current_state.currentNode << " to " << dir;
	Logger::logMessage(ss.str());
	map[current_state.currentNode] = dir;
}

Cardinal Navigation::getCardinalToNextNode(RobotState current_state)
{
	stringstream ss;
	ss << "Navigation: Cardinal to next node " << map[current_state.currentNode];
	return map[current_state.currentNode];
}

void Navigation::storePath(){
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
	Logger::logError("Navigation charToCardinal fed incorrect char");
}

string Navigation::toString(){
	stringstream ss;
	for(int i = 0; i < 50; ++i){
		ss << map[i] << " ";
	}
	return ss.str();
}
void Navigation::logNavigationError(string s){
	Logger::logError("Navigation: " + s);
}
void Navigation::logNavigationMessage(string s){
	Logger::logMessage("Navigation: " + s);
}
