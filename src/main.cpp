#include "Navigation.h"
#include "ConfigManager.h"
#include <iostream>
#include "RobotState.h"
#include "Cardinal.h"
using std::cout;


int main(void){

	Configuration* config = ConfigurationFactory::constructBlankConfig();
	config->startNode = 45;
	RobotState r(*config);
	r.currentDirection = Cardinal::EAST;
	Navigation nav(config);
	nav.updateMap(r,Cardinal::EAST);
	r.currentNode = 46;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 39;
	nav.updateMap(r,Cardinal::EAST);
	r.currentNode = 40;
	nav.updateMap(r,Cardinal::SOUTH);
	r.currentNode = 47;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 40;
	nav.updateMap(r,Cardinal::EAST);
	r.currentNode = 48;
	nav.updateMap(r,Cardinal::SOUTH);
	
	cout << nav.toString();
	

}
