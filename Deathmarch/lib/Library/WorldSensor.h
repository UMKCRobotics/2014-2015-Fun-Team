#include <set>
#include "Sensors.h"
#include "Logger.h"
#include "RobotState.h"
#include <sstream>
#include "Arduino.h"
#include "Pins.h"
using std::set;


#ifndef FunWorldSensor
#define FunWorldSensor

namespace FunWorldSensor{
	/**
	 * Uses the IR sensors to compute what walls around the
	 * robot are open
	 */
	const int minValue = 250; //Sensor values get higher as you get closer
	set<Cardinal> computeOpenings(RobotState state){
		set<Cardinal> openings;
		int frontIR = analogRead(FRONT_IR);
		int backRightIR =analogRead(BACKWARD_RIGHT_IR);
		int frontRightIR = analogRead(FORWARD_RIGHT_IR);

		bool noFrontWall = frontIR >= minValue;
		bool noRightWall = ((backRightIR + frontRightIR) / 2) >= minValue;
		switch(state.currentDirection){
			case NORTH:
				if(noFrontWall){
					openings.insert(NORTH);
				}
				if(noRightWall){
					openings.insert(EAST);
				}
				/*
				if(noLeftWall){
					openings.insert(WEST);
				}
				*/
				//openings.insert(SOUTH);
				break;
			case SOUTH:
				if(noFrontWall){
					openings.insert(SOUTH);
				}
				if(noRightWall){
					openings.insert(WEST);
				}
				/*
				if(noLeftWall){
					openings.insert(EAST);
				}
				*/
				//openings.insert(NORTH);
				break;
			case EAST:
				if(noFrontWall){
					openings.insert(EAST);
				}
				if(noRightWall){
					openings.insert(SOUTH);
				}
				/*
				if(noLeftWall){
					openings.insert(NORTH);
				}
				*/
				//openings.insert(WEST);
				break;
			case WEST:
				if(noFrontWall){
					openings.insert(WEST);
				}
				if(noRightWall){
					openings.insert(NORTH);
				}
				/*
				if(noLeftWall){
					openings.insert(SOUTH);
				}
				*/
				//openings.insert(EAST);
				break;
			}
		
		return openings;
	}
}
#endif
