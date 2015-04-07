#include "RedBot.h"

#ifndef SerialCom_h
#define SerialCom_h

#define SERIAL_SPEED 38400
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
class SerialCom{

    public:
	static void stopBothMotors(){getInstance().serial.write(1);}
	static void redLedOn(){getInstance().serial.write(2);}
	static void yellowLedOn(){getInstance().serial.write(3);}
	static void greenLedOn(){getInstance().serial.write(4);}
	static void redLedOff(){getInstance().serial.write(5);}
	static void yellowLedOff(){getInstance().serial.write(6);}
	static void greenLedOff(){getInstance().serial.write(7);}
	static void motorsFullForward(){getInstance().serial.write(8);}
	static void motorsRightTurn(){getInstance().serial.write(9);}
	static void motorsLeftTurn(){getInstance().serial.write(10);}
        
    private:
	static SerialCom& getInstance()
        {
            static SerialCom  instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }

	RedBotSoftwareSerial serial;
        SerialCom() {
		serial.begin(SERIAL_SPEED);
	};                   
};

#endif
