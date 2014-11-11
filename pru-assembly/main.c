#include <stdio.h>
#include <sys/mman.h>
#include <stdint.h>

#include <prussdrv.h>
#include <pruss_intc_mapping.h>

#define PRU_NUM 0

uint16_t *getAddr();

void main (void) {
    /* Initialize structure used by prussdrv_pruintc_intc   */
    /* PRUSS_INTC_INITDATA is found in pruss_intc_mapping.h */
    tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

    /* Allocate and initialize memory */
    prussdrv_init ();
    prussdrv_open(PRU_EVTOUT_0);
    /* Map PRU's INTC */
    prussdrv_pruintc_init(&pruss_intc_initdata);

    // Get address and flush part of memory
    uint16_t *pruData = getAddr();
    pruData[0] = 10;
    pruData[1] = 7;

    /* Load and execute binary on PRU */
    prussdrv_exec_program(PRU_NUM, "./prucode.bin");

    /* Wait for event completion from PRU */
    prussdrv_pru_wait_event(PRU_EVTOUT_0);

    printf("Original: \t%u, %u\n", pruData[0], pruData[1]);
    printf("Result: \t%u, %u\n", pruData[2], pruData[3]);

    /* Disable PRU and close memory mappings */
    prussdrv_pru_disable(PRU_NUM);
    prussdrv_exit ();
}

uint16_t *getAddr() {
    void *addr;
    prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, &addr);
    return (uint16_t *)addr;
}
