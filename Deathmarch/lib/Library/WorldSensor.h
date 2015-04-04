#include "RobotState.h"
#include "Arduino.h"
#include "Pins.h"


#ifndef FunWorldSensor
#define FunWorldSensor

struct Openings{
	bool NorthOpen;
	bool SouthOpen;
	bool EastOpen;
	bool WestOpen;
	bool NoneOpen;
	Openings(){
		bool NorthOpen = false;
		bool SouthOpen = false;
		bool EastOpen = false;
		bool WestOpen = false;
		bool NoneOpen = false;
	}

	void open(Cardinal card){
		switch(card){
			case NORTH:
				NorthOpen = true;
				break;
			case SOUTH:
				SouthOpen = true;
				break;
			case EAST:
				EastOpen = true;
				break;
			case WEST:
				WestOpen = true;
				break;
		}
	}
};

namespace FunWorldSensor{
	/**
	 * Uses the IR sensors to compute what walls around the
	 * robot are open
	 */
	const int minValue = 250; //Sensor values get higher as you get closer
	Openings computeOpenings(RobotState state){
		int frontIR = analogRead(FRONT_IR);
		int backRightIR =analogRead(BACKWARD_RIGHT_IR);
		int frontRightIR = analogRead(FORWARD_RIGHT_IR);
		
		bool noFrontWall = frontIR >= minValue;
		bool noRightWall = ((backRightIR + frontRightIR) / 2) >= minValue;

		Openings openings;

		if(noFrontWall && noRightWall){
			openings.NoneOpen = true;
			return openings;
		}

		switch(state.currentDirection){
			case NORTH:
				if(noFrontWall){
					openings.open(NORTH);
				}
				if(noRightWall){
					openings.open(EAST);
				}
				/*
				if(noLeftWall){
					openings.open(WEST);
				}
				*/
				//openings.open(SOUTH);
				break;
			case SOUTH:
				if(noFrontWall){
					openings.open(SOUTH);
				}
				if(noRightWall){
					openings.open(WEST);
				}
				/*
				if(noLeftWall){
					openings.open(EAST);
				}
				*/
				//openings.open(NORTH);
				break;
			case EAST:
				if(noFrontWall){
					openings.open(EAST);
				}
				if(noRightWall){
					openings.open(SOUTH);
				}
				/*
				if(noLeftWall){
					openings.open(NORTH);
				}
				*/
				//openings.open(WEST);
				break;
			case WEST:
				if(noFrontWall){
					openings.open(WEST);
				}
				if(noRightWall){
					openings.open(NORTH);
				}
				/*
				if(noLeftWall){
					openings.open(SOUTH);
				}
				*/
				//openings.open(EAST);
				break;
			}
		
		return openings;
	}
}
#endif
