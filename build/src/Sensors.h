#ifndef SENSORS_H
#define SENSORS_H
#include <stdint.h>

// Determines whether PRU 0 or 1 is used.
#define PRU_NUM 1

struct SensorValues {
    uint16_t irFront;
    uint16_t irFrontLeft;
    uint16_t irFrontRight;
    uint16_t irBackLeft;
    uint16_t irBackRight;

    uint16_t lineLeft;
    uint16_t lineCenter;
    uint16_t lineRight;
};

class Sensors {
    public:
        static SensorValues read();
    private:
        uint16_t *addr;
	template<typename Func>
	static void applyToSensorInstance(Func f);
	Sensors();
        ~Sensors();
	static Sensors& getInstance(){
		static Sensors instance;
		return instance;
	}
};

#endif
