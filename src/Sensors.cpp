#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
// prussdrv.h and pruss_intc_mapping.h should be installed by
// am335x-pru-package (on Debian) or similar.

#include <prussdrv.h>
#include <pruss_intc_mapping.h>

#include <fstream>
#include "Sensors.h"
#include "Logger.h"

template<typename Func>
void Sensors::applyToSensorInstance(Func f){
	Sensors * instance = &Sensors::getInstance();
	f(instance);
}

Sensors::Sensors() {
    // Enable PRU device cape overlay thing.
    // FIXME: actual system calls instead of this nonsense.
    system("echo bspm_pru > /sys/devices/bone_capemgr.9/slots");
    system("echo bspm_pru > /sys/devices/bone_capemgr.8/slots");
    system("echo bspm_pru > /sys/devices/bone_capemgr.7/slots");
    system("echo bspm_pru > /sys/devices/bone_capemgr.6/slots");
    system("echo bspm_pru > /sys/devices/bone_capemgr.5/slots");
    system("echo bspm_pru > /sys/devices/bone_capemgr.4/slots");
    system("echo bspm_pru > /sys/devices/bone_capemgr.3/slots");
    system("echo bspm_pru > /sys/devices/bone_capemgr.2/slots");
    system("echo bspm_pru > /sys/devices/bone_capemgr.1/slots");
    system("echo bspm_pru > /sys/devices/bone_capemgr.0/slots");
    // Wait for system calls to terminate/cape to load.
    usleep(1000 * 1000);

    /* Initialize structure used by prussdrv_pruintc_intc   */
    /* PRUSS_INTC_INITDATA is found in pruss_intc_mapping.h */
    tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

    /* Allocate and initialize memory */
    prussdrv_init();
    prussdrv_open(PRU_EVTOUT_1);
    /* Map PRU's INTC */
    prussdrv_pruintc_init(&pruss_intc_initdata);

    // Get address and flush part of memory
    void *temp;
    prussdrv_map_prumem(PRUSS0_PRU1_DATARAM, &temp);
    addr = (uint16_t *)temp;
    for (int i = 0; i < 8; i++) {
        addr[i] = 0;
    }

    std::ifstream binfile("./prucode.bin", std::ios::binary);
    if(!binfile){ Logger::logError("prucode.bin does not exist");}
    binfile.close();

    /* Load and execute binary on PRU */
    prussdrv_exec_program(PRU_NUM, "./prucode.bin");
}

Sensors::~Sensors() {
    /* Disable PRU and close memory mappings */
    prussdrv_pru_disable(PRU_NUM);
    prussdrv_exit();
}

SensorValues Sensors::read() {
	SensorValues values;
	values.irFront = getInstance().addr[7];
    	values.irFrontLeft = getInstance().addr[6];
    	values.irFrontRight = getInstance().addr[5];
    	values.irBackLeft = getInstance().addr[4];
    	values.irBackRight = getInstance().addr[3];
    	values.lineLeft = getInstance().addr[2];
    	values.lineCenter = getInstance().addr[1];
    	values.lineRight = getInstance().addr[0];
	return values;
}
