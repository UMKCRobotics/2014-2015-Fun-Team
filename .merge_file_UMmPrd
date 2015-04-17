#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include <fstream>
#include "Sensors.h"
#include "Logger.h"

Sensors::Sensors() {
	int status;
	status = serial.Open(SERIAL_PORT, SERIAL_RATE);
	if (status != 1) {
		Logger::logError("Error opening serial.");
	}
}

LineValues Sensors::readLines() {
	serial.WriteString("l");
	uint16_t buf[3];
	serial.Read((uint8_t *)buf, 6);

	LineValues values;
	values.left = buf[0];
	values.center = buf[1];
	values.right = buf[2];
	return values;
}

DistanceValues Sensors::readDistance() {
	serial.WriteString("d");
	uint16_t buf[5];
	serial.Read((uint8_t *)buf, 10);

	DistanceValues values;
	values.front = buf[0];
	values.frontLeft = buf[1];
	values.frontRight = buf[2];
	values.backLeft = buf[3];
	values.backRight = buf[4];
	return values;
}

Sensors::~Sensors() {
	serial.Close();
}
