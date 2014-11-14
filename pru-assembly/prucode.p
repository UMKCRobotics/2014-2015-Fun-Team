.origin 0
.entrypoint INIT

#include "prucode.hp"

// *** LINE SENSOR ALGORITHM ***
// CHARGE: set all high, wait, set all low
// Set outputs to high
// Loop: wait 10 micros
// Set outputs low
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

    gpio_dir_out P8_38, GPIO2_ADDR

    MOV GPIO_ADDR_REG, GPIO2_ADDR | GPIO_DATAOUT_OFFSET
    MOV LOOP_REG, 100000000

LOOP_TOGGLE_OUT:
    // Set high
    set_gpio (1 << P8_38)

    // Set low
    set_gpio 0

    // Loop
    SUB LOOP_REG, LOOP_REG, 1
    QBNE LOOP_TOGGLE_OUT, LOOP_REG, 0

INIT_READ:
    MOV R31.b0, PRU1_ARM_INTERRUPT+16

    // Set pin to input.
    MOV GPIO_ADDR_REG, GPIO2_ADDR | GPIO_OE_OFFSET
    LBBO OE_REG, GPIO_ADDR_REG, 0, 4
    SET OE_REG, P8_38
    SBBO OE_REG, GPIO_ADDR_REG, 0, 4

    MOV GPIO_ADDR_REG, GPIO2_ADDR | GPIO_DATAIN_OFFSET  // Store GPIO input address.
    MOV RAM_ADDR_REG, 0  // Store data ram address (0) for communication with host.

    MOV LOOP_REG, 50000000  // Reset loop counter

LOOP_READ_IN:
    LBBO GPIO_DATA_REG, GPIO_ADDR_REG, 0, 4  // Read inputs into local register.
    SBBO GPIO_DATA_REG, RAM_ADDR_REG, 0, 4  // Send to RAM for main CPU to read.

    // Loop counter/jump
    SUB LOOP_REG, LOOP_REG, 1
    QBNE LOOP_READ_IN, LOOP_REG, 0

    // Send event interrupt to main CPU and stop.
    MOV R31.b0, PRU1_ARM_INTERRUPT+16
    HALT


