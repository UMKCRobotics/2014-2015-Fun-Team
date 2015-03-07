#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "GPIOManager.h"
#include "GPIOConst.h"
#include "Logger.h"
#include <sstream>


class Notifier
{
	private:
	GPIO::GPIOManager* gp;
	
	int RED_PIN;
	int YELLOW_PIN;
	int GREEN_PIN;

	public:
	
	Notifier(){
		gp = GPIO::GPIOManager::getInstance();
		RED_PIN = 86;
		//RED_PIN = GPIO::GPIOConst::getInstance()->getGpioByKey("P8_27");
		GREEN_PIN=10;
		YELLOW_PIN=87;
		gp->setDirection(RED_PIN,GPIO::OUTPUT);
		gp->setDirection(GREEN_PIN,GPIO::OUTPUT);
		gp->setDirection(YELLOW_PIN,GPIO::OUTPUT);
		//gp->exportPin(RED_PIN);
	}

	
	~Notifier(){
		gp->~GPIOManager();
	}

	void onRed()
	{
		gp->setValue(RED_PIN, GPIO::HIGH);
		Logger::logMessage("turned on red LED");
	}
	
	void offRed()
	{
		gp->setValue(RED_PIN, GPIO::LOW);
		Logger::logMessage("turned off red LED");
	}
	
	void onGreen()
	{
		gp->setValue(GREEN_PIN, GPIO::HIGH);
		Logger::logMessage("turned on green LED");
	}
	
	void offGreen()
	{
		gp->setValue(GREEN_PIN, GPIO::LOW);
		Logger::logMessage("turned off green LED");
	}
	
	void onYellow()
	{
		gp->setValue(YELLOW_PIN, GPIO::HIGH);
		Logger::logMessage("turned on yellow LED");
	}
	
	void offYellow()
	{
		gp->setValue(YELLOW_PIN, GPIO::LOW);
		Logger::logMessage("turned off yellow LED");
	}
	void  mazeComplete(){
		Notifier::onRed();
		sleep(5);
		Notifier::offRed();
	}
};











#endif
