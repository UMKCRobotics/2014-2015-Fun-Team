.origin 0
.entrypoint INIT

#include "prucode.hp"

// UART serial protocol:
// - 1 start bit (low)
// - 8 data bits
// - 1 stop bit (high)
// Falling edge of stop bit = beginning of start bit.
// At 115200 baud, 1 bit = 8681 nanoseconds = 1736 clock cycles at 200 mhz.

// Wait for end of stop/beginning of start bit (high -> low edge)
// Delay 1.5x bit rate
// Loop 8x:
//      Read data pin
//      Shift into register
// Store newly read byte -- to second pru or directly to ram?

// Note: RAM writes (SBBO) should be 2-8 cycles depending on saturation,
// Read (LBBO) is around 33 cycles... I think.

INIT:
    // Enable OCP socket for communication with host/DDRAM
    LBCO r0, C4, 4, 4
    CLR  r0, r0, 4
    SBCO r0, C4, 4, 4

    // Store data ram address (0) for communication with host.
    MOV RAM_ADDR_REG, 0

MAIN_LOOP:
    MOV MAIN_COUNT, 4

READ:
    readByte
    LSL DATA_REG, DATA_REG, 8  // Shift data.
    MOV DATA_REG.b0, TEMP_REG.b0  // Store new.

    SUB MAIN_COUNT, MAIN_COUNT, 1
    QBNE READ, MAIN_COUNT, 0

WRITE:
    SBBO DATA_REG, RAM_ADDR_REG, 0, 4  // Write byte to ram.
    MOV r31.b0, PRU1_ARM_INTERRUPT+16  // Notify CPU.
    QBA MAIN_LOOP
