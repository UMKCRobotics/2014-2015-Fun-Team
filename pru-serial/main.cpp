#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "Sensors.h"

/*
 * Ugly example/quick test code.
 */
int main() {
    Sensors s;
    while (1) {
        SensorValues values = s.read();
        std::cout << std::setw(8) << values.irFront << std::setw(8) <<
            values.irFrontLeft << std::setw(8) << values.irFrontRight <<
            std::setw(8) << values.irBackLeft << std::setw(8) <<
            values.irBackRight;
        std::cout << std::setw(8) << values.lineLeft << std::setw(8) <<
            values.lineCenter << std::setw(8) << values.lineRight << '\n';
        usleep(10000);
    }
}
