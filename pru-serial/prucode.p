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

    MOV MAIN_COUNT, 4

START:
    // Initialize serial data registers.
    MOV DATA_REG_1, 0
    MOV DATA_REG_2, 0

    // Wait for sync/start pulse from Arduino.
    WBS r31.SYNC_PIN
    WBC r31.SYNC_PIN

    MOV MAIN_COUNT, 8  // Read 8 bits from serial.

READ:
    readByte

    // Shift data one byte over across both registers.
    LSL DATA_REG_2, DATA_REG_2, 8
    MOV DATA_REG_2.b0, DATA_REG_1.b3
    LSL DATA_REG_1, DATA_REG_1, 8
    // Store new byte.
    MOV DATA_REG_1.b0, TEMP_REG.b0

    SUB MAIN_COUNT, MAIN_COUNT, 1
    QBNE READ, MAIN_COUNT, 0

WRITE:
    SBBO DATA_REG_1, RAM_ADDR_REG, 0, 8  // Write byte to ram.
    MOV r31.b0, PRU1_ARM_INTERRUPT+16  // Notify CPU.
    QBA START
