#include "RobotState.h"
#include "Arduino.h"
#include "Pins.h"
#include <stdlib.h>


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

struct IRSensorReadings{
  int frontIR;
  int frontRightIR;
  int backRightIR;
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
	int compareInts(const void * a, const void * b){
	  return ( *(int*)a -*(int*) b);
	}
	
	IRSensorReadings getAvg(int readTimes,int delayTime = 5){
	  int frontIRSum = 0;
	  int backRightIRSum = 0;
	  int frontRightIRSum = 0;

	  for(int i = 0; i < timesToReadSensors; ++i){
		frontIRSum += analogRead(FRONT_IR);
		backRightIRSum += analogRead(BACKWARD_RIGHT_IR);
		frontRightIRSum += analogRead(FORWARD_RIGHT_IR);
		delay(delayTime);
	  }
	  IRSensorReadings readings;
	  readings.frontIR = frontIRSum / timesToReadSensors;
	  readings.backRightIR = backRightIRSum / timesToReadSensors;
	  readings.frontRightIR = frontRightIRSum / timesToReadSensors;
	  return readings;
	}
	
	IRSensorReadings median(int timesToReadSensors, int delayTime = 5){
	  int frontReadings[timesToReadSensors];
	  int backRightReadings[timesToReadSensors];
	  int frontRightReadings[timesToReadSensors];
	  for(int i = 0; i < timesToReadSensors; ++i){
	    frontReadings[i] = analogRead(FRONT_IR);
	    backRightReadings[i] = analogRead(BACKWARD_RIGHT_IR);
	    frontRightReadings[i] = analogRead(FORWARD_RIGHT_IR);
	    delay(delayTime);
	  }
	  qsort(frontReadings,timesToReadSensors,sizeof(int),compareInts);
	  qsort(backRightReadings,timesToReadSensors,sizeof(int),compareInts);
	  qsort(frontRightReadings,timesToReadSensors,sizeof(int),compareInts);
	  IRSensorReadings readings;
	  readings.frontIR = frontReadings[timesToReadSensors/2];
	  readings.backRightIR = backRightReadings[timesToReadSensors/2];
	  readings.frontRightIR = backRightReadings[timesToReadSensors/2];
	  return readings;
	}
	IRSensorReadings medianThreeSensors(int delayTime){
	  int irFront1 = analogRead(FRONT_IR);
	  int irBackRight1 = analogRead(BACKWARD_RIGHT_IR);
	  int irFrontRight1 = analogRead(FORWARD_RIGHT_IR);
	  delay(delayTime);
	  int irFront2 = analogRead(FRONT_IR);
	  int irBackRight1 = analogRead()
	  IRSensorReadings readings; 
	}
	Openings computeOpenings(RobotState state){
	        IRSensorReadings readings = median(3);
	  	bool noFrontWall = readings.frontIR <= maxValueF;
		bool noRightWall = avg(readings.backRightIR,readings.frontRightIR) <= maxValueR;


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
