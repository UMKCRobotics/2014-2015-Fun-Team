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

START:
    // Initialize serial data registers.
    MOV DATA_REG_1, 0
    MOV DATA_REG_2, 0

    // Wait for sync/start pulse from Arduino.
    WBS r31.SYNC_PIN
    WBC r31.SYNC_PIN

    // Store new.
    readByte
    MOV DATA_REG_3.b3, TEMP_REG.b0
    readByte
    MOV DATA_REG_3.b2, TEMP_REG.b0
    readByte
    MOV DATA_REG_3.b1, TEMP_REG.b0
    readByte
    MOV DATA_REG_3.b0, TEMP_REG.b0

    readByte
    MOV DATA_REG_2.b3, TEMP_REG.b0
    readByte
    MOV DATA_REG_2.b2, TEMP_REG.b0
    readByte
    MOV DATA_REG_2.b1, TEMP_REG.b0
    readByte
    MOV DATA_REG_2.b0, TEMP_REG.b0

    readByte
    MOV DATA_REG_1.b3, TEMP_REG.b0
    readByte
    MOV DATA_REG_1.b2, TEMP_REG.b0
    readByte
    MOV DATA_REG_1.b1, TEMP_REG.b0
    readByte
    MOV DATA_REG_1.b0, TEMP_REG.b0

    readByte
    MOV DATA_REG_0.b3, TEMP_REG.b0
    readByte
    MOV DATA_REG_0.b2, TEMP_REG.b0
    readByte
    MOV DATA_REG_0.b1, TEMP_REG.b0
    readByte
    MOV DATA_REG_0.b0, TEMP_REG.b0

WRITE:
    SBBO DATA_REG_0, RAM_ADDR_REG, 0, 16  // Write to ram.

    MOV r31.b0, PRU1_ARM_INTERRUPT+16  // Notify CPU.
    QBA START
