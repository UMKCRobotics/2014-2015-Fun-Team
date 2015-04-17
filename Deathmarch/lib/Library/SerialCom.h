#include "RedBot.h"
#include "Arduino.h"

#ifndef SerialCom_h
#define SerialCom_h

/*
	 * 1 - stop both motors
	 * 2 - red LED ON
	 * 3 - yellow LED ON
	 * 4 - green LED ON
	 * 5 - red LED OFF
	 * 6 - yellow LED OFF
	 * 7 - green LED OFF
	 * 8 - Both Motors full forward
	 * 9 - both Motors right Turn
	 * 10 - both motors left turn
	 */
namespace SerialCom{
	void stopBothMotors();
	void redLedOn();
	void yellowLedOn();
	void greenLedOn();
	void redLedOff();
	void yellowLedOff();
	void greenLedOff();
	void motorsFullForward();
	void motorsRightTurn();
	void motorsLeftTurn();
	bool testSerial();

	Serial* getScreenSerial();

	const int SERIAL_SPEED = 9600;
	static RedBotSoftwareSerial serial;
	static bool isInitialized = false;
	static bool screenIsInitialized = false;
	const int DELAY_AFTER_WRITE = 10;

	static void init(){
		SerialCom::serial.begin(SerialCom::SERIAL_SPEED);
	 	//blockUntilConnected();
		SerialCom::isInitialized = true;
	}
	
	void initializeIfNeeded();
	void initializeScreenSerialIfNeeded();
	
	void rawWriteValue(char value);

	void blockUntilGoodWrite();

};

#endif
