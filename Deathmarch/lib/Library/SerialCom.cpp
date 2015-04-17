#include "SerialCom.h"

void SerialCom::stopBothMotors(){
  SerialCom::rawWriteValue(1);
}
void SerialCom::redLedOn(){
  SerialCom::rawWriteValue(2);
}
void SerialCom::yellowLedOn(){
  SerialCom::rawWriteValue(3);
}
void SerialCom::greenLedOn(){
  SerialCom::rawWriteValue(4);
}
void SerialCom::redLedOff(){
  SerialCom::rawWriteValue(5);
}
void SerialCom::yellowLedOff(){
  SerialCom::rawWriteValue(6);
}
void SerialCom::greenLedOff(){
  SerialCom::rawWriteValue(7);
}
void SerialCom::motorsFullForward(){
  SerialCom::rawWriteValue(8);
}
void SerialCom::motorsRightTurn(){
  SerialCom::rawWriteValue(9);
}
void SerialCom::motorsLeftTurn(){
  SerialCom::rawWriteValue(10);
}

bool SerialCom::testSerial(){
  SerialCom::rawWriteValue(70);
  return serial.read() == 0xF;
}
void SerialCom::blockUntilGoodWrite(){

	while(true){
		if(serial.available() != 0){
			return;
		}
	}

}

void SerialCom::initializeIfNeeded(){
 if (! SerialCom::isInitialized) SerialCom::init(); 
}
void SerialCom::rawWriteValue(char value){
  SerialCom::initializeIfNeeded();
  serial.write(value);
  delay(SerialCom::DELAY_AFTER_WRITE);

}


void SerialCom::initializeScreenSerialIfNeeded(){
  if(!SerialCom::screenIsInitialized){Serial.begin(9600);}
  SerialCom::screenIsInitialized = true;
}
