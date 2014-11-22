#include "Navigation.h"
#include "ConfigManager.h"
#include <iostream>
#include "RobotState.h"
#include "Cardinal.h"
using std::cout;
using std::endl;


int main(void){
	Logger::standardInit();

	Configuration* config = ConfigurationFactory::constructBlankConfig();
	config->startNode = 48;
	RobotState r(*config);
	r.currentDirection = Cardinal::NORTH;
	Navigation nav(config);
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 41;
	nav.updateMap(r,Cardinal::WEST);
	r.currentNode = 40;
	nav.updateMap(r,Cardinal::WEST);
	r.currentNode = 39;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 32;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 25;
	nav.updateMap(r,Cardinal::EAST);
	r.currentNode = 26;
	nav.updateMap(r,Cardinal::EAST);
	r.currentNode = 27;
	nav.updateMap(r,Cardinal::SOUTH);
	r.currentNode = 34;
	nav.updateMap(r,Cardinal::WEST);
	r.currentNode = 33;
	nav.updateMap(r,Cardinal::EAST);
	r.currentNode = 34;
	nav.updateMap(r,Cardinal::EAST);
	r.currentNode = 35;
	nav.updateMap(r,Cardinal::SOUTH);
	r.currentNode = 42;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 35;
	nav.updateMap(r, Cardinal::WEST);
	r.currentNode = 34;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 27;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 20;
	nav.updateMap(r,Cardinal::EAST);
	r.currentNode = 21;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 14;
	nav.updateMap(r,Cardinal::WEST);
	r.currentNode = 13;
	nav.updateMap(r,Cardinal::WEST);
	r.currentNode = 12;
	nav.updateMap(r,Cardinal::SOUTH);
	r.currentNode = 19;
	nav.updateMap(r,Cardinal::WEST);
	r.currentNode = 18;
	nav.updateMap(r,Cardinal::EAST);
	r.currentNode = 19;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 12;
	nav.updateMap(r,Cardinal::EAST);
	r.currentNode = 13;
	nav.updateMap(r,Cardinal::EAST);
	r.currentNode = 14;
	nav.updateMap(r,Cardinal::SOUTH);
	r.currentNode = 21;
	nav.updateMap(r,Cardinal::WEST);
	r.currentNode = 20;
	nav.updateMap(r,Cardinal::SOUTH);
	r.currentNode = 27;
	nav.updateMap(r,Cardinal::WEST);
	r.currentNode = 26;
	nav.updateMap(r,Cardinal::WEST);
	r.currentNode = 25;
	nav.updateMap(r,Cardinal::SOUTH);
	r.currentNode = 32;
	nav.updateMap(r,Cardinal::WEST);
	r.currentNode = 31;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 24;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 17;
	nav.updateMap(r,Cardinal::SOUTH);
	r.currentNode = 24;
	nav.updateMap(r,Cardinal::WEST);
	r.currentNode = 23;
	nav.updateMap(r,Cardinal::WEST);
	r.currentNode = 22;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 15;
	nav.updateMap(r,Cardinal::EAST);
	r.currentNode = 16;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 9;
	nav.updateMap(r,Cardinal::SOUTH);
	r.currentNode = 16;
	nav.updateMap(r,Cardinal::WEST);
	r.currentNode = 15;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 8;
	nav.updateMap(r,Cardinal::NORTH);
	r.currentNode = 1;
	
	
	cout << nav.toString() << endl;
	

}
