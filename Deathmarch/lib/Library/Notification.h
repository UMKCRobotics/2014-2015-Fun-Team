#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <sstream>


class Notifier
{
	private:
	
	int RED_PIN;
	int YELLOW_PIN;
	int GREEN_PIN;

	public:
	
	Notifier() {
		
		RED_PIN = 86;
		GREEN_PIN = 10;
		YELLOW_PIN = 87;
		pinMode(RED_PIN, OUTPUT);
		pinMode(GREEN_PIN, OUTPUT);
		pinMode(YELLOW_PIN, OUTPUT);
	}

	
	~Notifier() {
	
	}

	void onRed() {
		digitalWrite(RED_PIN, HIGH);
	}
	
	void offRed() {
		digitalWrite(RED_PIN, LOW);
	}
	
	void onGreen() {
		digitalWrite(GREEN_PIN, HIGH);
	}
	
	void offGreen() {
		digitalWrite(GREEN_PIN, LOW);
	}
	
	void onYellow()	{
		digitalWrite(YELLOW_PIN, HIGH);
	}
	
	void offYellow() {
		digitalWrite(YELLOW_PIN, LOW);
	}
	
	void mazeStart() {
		Notifier::offYellow();
		Notifier::onGreen();
	}

	void  mazeComplete() {
		Notifier::offGreen();
		Notifier::onRed();
		sleep(5);
		Notifier::offRed();
		Notifier::onYellow();
	}
};











#endif
