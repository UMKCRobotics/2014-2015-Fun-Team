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
	Openings();
	void open(Cardinal card);
};

namespace FunWorldSensor{
	/**
	 * Uses the IR sensors to compute what walls around the
	 * robot are open
	 */
	const int maxValueR = 200; //Sensor values get higher as you get closer
	const int maxValueF = 400;
	const int timesToReadSensors = 25;
	
	inline int avg(int x, int y){
		return ((x+y)/2);
	}

	Openings computeOpenings(RobotState state){
		unsigned int frontIRSum = 0;
		unsigned int backRightIRSum = 0;
		unsigned int frontRightIRSum = 0;

		for(int i = 0; i < timesToReadSensors; ++i){
			frontIRSum += analogRead(FRONT_IR);
			backRightIRSum += analogRead(BACKWARD_RIGHT_IR);
			frontRightIRSum += analogRead(FORWARD_RIGHT_IR);
			delay(5);
		}

		int frontIR = frontIRSum / timesToReadSensors;
		int backRightIR = backRightIRSum / timesToReadSensors;
		int frontRightIR = frontRightIRSum / timesToReadSensors;
		
		Serial* s = SerialCom::getScreenSerial();
		SerialCom::getScreenSerial()->print("test");
		SerialCom::getScreenSerial()->print("\n Front: ");
		SerialCom::getScreenSerial()->print(frontIR);
		SerialCom::getScreenSerial()->print("\n BackR: ");
		SerialCom::getScreenSerial()->print(backRightIR);
		SerialCom::getScreenSerial()->print("\n FrontR: ");
		SerialCom::getScreenSerial()->print(frontRightIR);
	
		bool noFrontWall = frontIR <= maxValueF;
		bool noRightWall = avg(backRightIR,frontRightIR) <= maxValueR;


		Openings openings;

		if(!noFrontWall && !noRightWall){
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
				break;
			case SOUTH:
				if(noFrontWall){
					openings.open(SOUTH);
				}
				if(noRightWall){
					openings.open(WEST);
				}
				break;
			case EAST:
				if(noFrontWall){
					openings.open(EAST);
				}
				if(noRightWall){
					openings.open(SOUTH);
				}
				break;
			case WEST:
				if(noFrontWall){
					openings.open(WEST);
				}
				if(noRightWall){
					openings.open(NORTH);
				}
				break;
		}
		
		openings.NoneOpen = false;
		return openings;
	
	}	

}
#endif
