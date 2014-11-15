.origin 0
.entrypoint INIT

#include "prucode.hp"

// *** LINE SENSOR ALGORITHM ***
// CHARGE: set all high, wait, set all low
// Set outputs to high
// Loop: wait 10 micros
// DON'T set low
//
// READ: (reset counts/loop), read pins, incr. each counter if high, loop until all low
// Read inputs
// if input i(n) is high, increment counter c(n), set doLoop to 1
// repeat read if doLoop == 1 (QBGT doLoop 0)
//
// SEND: write all read counters to ram

INIT:
    // Enable OCP socket for communication with host/DDRAM
    LBCO r0, C4, 4, 4
    CLR  r0, r0, 4
    SBCO r0, C4, 4, 4


    // MOV GPIO_ADDR_REG, GPIO2_ADDR | GPIO_DATAOUT_OFFSET
    MOV RAM_ADDR_REG, 0  // Store data ram address (0) for communication with host.

    // MOV LOOP_REG, 1337
    // SBBO LOOP_REG, RAM_ADDR_REG, 0, 4

    // gpio_dir_out P8_36, GPIO2_ADDR

    // set_gpio (1 << P8_36)

// CHARGE:
    // set_gpio (1 << P8_36)  // Set high
    // delay_micros 15  // Wait for capacitor to charge
    // gpio_dir_in P8_36, GPIO2_ADDR  // Set to input

gpio_dir_in P8_36, GPIO2_ADDR
MOV GPIO_ADDR_REG, GPIO2_ADDR | GPIO_DATAIN_OFFSET  // Store GPIO input address.

INIT_READ:
    MOV LOOP_REG, 0  // For input time counting

WAIT_HIGH:  // Temporary use for testing
    LBBO GPIO_DATA_REG, GPIO_ADDR_REG, 0, 4
    QBBC WAIT_HIGH,  GPIO_DATA_REG, P8_36

LOOP_READ_IN:
    ADD LOOP_REG, LOOP_REG, 1
    LBBO GPIO_DATA_REG, GPIO_ADDR_REG, 0, 4  // Read inputs into local register.
    QBBS LOOP_READ_IN, GPIO_DATA_REG, P8_36

    SBBO LOOP_REG, RAM_ADDR_REG, 0, 4
    QBA INIT_READ


// Send event interrupt to main CPU and stop.
// MOV R31.b0, PRU1_ARM_INTERRUPT+16
// HALT
