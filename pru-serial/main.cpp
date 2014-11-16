#include <stdio.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>

#include <prussdrv.h>
#include <pruss_intc_mapping.h>

#define PRU_NUM 1

uint32_t *getAddr();

int main () {
    /* Initialize structure used by prussdrv_pruintc_intc   */
    /* PRUSS_INTC_INITDATA is found in pruss_intc_mapping.h */
    tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

    /* Allocate and initialize memory */
    prussdrv_init ();
    prussdrv_open(PRU_EVTOUT_1);
    /* Map PRU's INTC */
    prussdrv_pruintc_init(&pruss_intc_initdata);

    // Get address and write part of memory
    uint32_t *pruData = getAddr();

    /* Load and execute binary on PRU */
    prussdrv_exec_program(PRU_NUM, "./prucode.bin");

    while (true) {
        printf("%u\n", pruData[0]);
        usleep(250000);
    }

    /* Disable PRU and close memory mappings */
    prussdrv_pru_disable(PRU_NUM);
    prussdrv_exit ();

    return 0;
}

uint32_t *getAddr() {
    void *addr;
    prussdrv_map_prumem(PRUSS0_PRU1_DATARAM, &addr);
    return (uint32_t *)addr;
}
