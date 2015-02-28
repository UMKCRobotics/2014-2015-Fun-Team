#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>
#include "serialib.h"

#define SERIAL_PORT "/dev/ttyUSB0"
#define SERIAL_RATE 115200

struct LineValues {
    uint16_t left;
    uint16_t center;
    uint16_t right;
};

struct DistanceValues {
    uint16_t front;
    uint16_t frontLeft;
    uint16_t frontRight;
    uint16_t backLeft;
    uint16_t backRight;
};

class Sensors {
    public:
	Sensors();
        ~Sensors();
        LineValues readLines();
        DistanceValues readDistance();
    private:
	serialib serial;
};

#endif
