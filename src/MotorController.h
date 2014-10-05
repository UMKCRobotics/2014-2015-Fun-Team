#include "DMCC.h"
#include "Cardinal.h"

class MotorController{
	private: 
		int fd1;
		int fd2;
		void moveForwardOneSquare();
		void turnLeft();
		void turnRight();
		viod turnAround();
	public:
		MotorController();
		~MotorController();
		RobotState turn(RobotState,Cardinal);
		RobotState move(RobotState,Cardinal);
}

