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
	const int maxValueF = 200;
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
	IRSensorReadings medianThreeSensors(int delayTime = 10){
	  int irFront1 = analogRead(FRONT_IR);
	  int irBackRight1 = analogRead(BACKWARD_RIGHT_IR);
	  int irFrontRight1 = analogRead(FORWARD_RIGHT_IR);
	  delay(delayTime);
	  int irFront2 = analogRead(FRONT_IR);
	  int irBackRight2 = analogRead(BACKWARD_RIGHT_IR);
	  int irFrontRight2 = analogRead(FORWARD_RIGHT_IR);
	  delay(delayTime);
	  int irFront3 = analogRead(FRONT_IR);
	  int irBackRight3 = analogRead(BACKWARD_RIGHT_IR);
	  int irFrontRight3 = analogRead(FORWARD_RIGHT_IR);
	  IRSensorReadings readings; 
	  if (irFront1 > irFront2 && irFront1 > irFront3){
	    readings.frontIR = irFront1;
	  }
	  else if (irFront2 > irFront1 && irFront2 > irFront3){
	    readings.frontIR = irFront2;
	  }
	  else{
	    readings.frontIR = irFront3;
	  }
	  if (irBackRight1 > irBackRight2 && irBackRight1 > irBackRight3){
	    readings.backRightIR = irBackRight1;
	  }
	  else if (irBackRight2 > irBackRight1 && irBackRight2 > irBackRight3){
	    readings.backRightIR = irBackRight2;
	  }
	  else{
	    readings.backRightIR = irBackRight3;
	  }
	  if(irFrontRight1 > irFrontRight2 && irFrontRight1 > irFrontRight3){
	    readings.frontRightIR = irFrontRight1;
	  }
	  else if( irFrontRight2 > irFrontRight1 && irFrontRight2 > irFrontRight3){
	    readings.frontRightIR = irFrontRight2;
	  }
	  else{
	    readings.frontRightIR = irFrontRight3;
	  }
	  return readings;
	}
	Openings computeOpenings(RobotState state){
	        IRSensorReadings readings = medianThreeSensors();
		IRSensorReadings readings1 = medianThreeSensors(10);
		int backRightIR = readings.backRightIR;
		int frontRightIR = readings.frontRightIR;

	  	bool noFrontWall = (readings.frontIR <= maxValueF) && ();
		bool noRightWall = frontRightIR <= maxValueR;

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
