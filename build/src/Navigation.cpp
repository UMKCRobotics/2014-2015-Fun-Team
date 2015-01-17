#include "Navigation.h"
#include "Logger.h"
#include <sstream>
#include <fstream>

Navigation::Navigation(Configuration* config) : config(config)
{
	for(int i = 0; i < 50; ++i){
		map[i] = (Cardinal)-1; //This is because somtimes they will intialize to valid values and we don't want that for pretty printing
	}
	map[config->startNode] = Cardinal::NORTH;

	
	fstream f(fileLocation);	
	(f.good())? logNavigationMessage("File at " + fileLocation + " is readable") : logNavigationError("File at " + fileLocation + " is not readable");
}

void Navigation::updateMap(RobotState current_state, Cardinal dir)
{
	stringstream ss;
	ss << "Updated " << current_state.currentNode << " to " << cardinalToString(dir);
	logNavigationMessage(ss.str());
	map[current_state.currentNode] = dir;
}

Cardinal Navigation::getCardinalToNextNode(RobotState current_state)
{
	stringstream ss;
	ss << "Cardinal to next node " << map[current_state.currentNode];
	logNavigationMessage(ss.str());
	return map[current_state.currentNode];
}

void Navigation::storePath(){
	applyToFileStream([&](fstream& file){
				for(int i=0; i<50; ++i){
					file << cardinalToString(map[i]);
				}
			});
}

void Navigation::loadPath(){
	applyToFileStream([&](fstream& file){
				for(int i = 0; i < 50; ++i){
					string tmp;
					file >> tmp;
					map[i] = stringToCardinal(tmp);
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

bool Navigation::inFinalNode(RobotState state)
{
	return state.currentNode == config->endNode;
}
string Navigation::toString(){
	stringstream ss;
	string tmp;
	for(int i = 0; i < 169; ++i){
		ss << "-";
	}
	ss << "\n|\t";
	for(int i = 1; i < 50; ++i){
		tmp = cardinalToString(map[i]);
		ss << i << ": ";
		if(tmp.compare("") != 0){ //cardinal did not return empty string
			ss << cardinalToString(map[i]) << "\t|\t";
		}
		else{
			ss << "EMPTY" << "\t|\t"; 
		}
		
		if(i % 7 == 0){ //We are at a leftmost square
			ss << "\n";
			for(int i = 0; i < 169; ++i){ //Put 90 dashes because that's a pretty even number
				ss << "-";
			}
			if (i != 49) ss << "\n|\t"; //Print | on newline for begining unless it's the last one
		}
				
	}
	return ss.str();
}
void Navigation::logNavigationError(string s){
	Logger::logError("Navigation: " + s);
}
void Navigation::logNavigationMessage(string s){
	Logger::logMessage("Navigation: " + s);
}
