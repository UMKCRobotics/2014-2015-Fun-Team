.origin 0
.entrypoint INIT

#include "prucode.hp"

// Assembly algorithm:
// Wait for end of stop/beginning of start bit (high -> low edge)
// Delay until at middle of first data bit
// Store each received bit of sensor values to registers.
// Write received data from registers to RAM.
// Notify ARM CPU.
// Repeat.

// Note: RAM writes (SBBO) should take 2-8 cycles depending on bus saturation,
// read (LBBO) take around 33 cycles... I think. This may be incorrect.

INIT:
    // Enable OCP socket for communication with host/DDRAM -- see TI wiki.
    LBCO r0, C4, 4, 4
    CLR  r0, r0, 4
    SBCO r0, C4, 4, 4

    // Store data ram address (0) where data is written to for ARM CPU.
    MOV RAM_ADDR_REG, 0

READ:
    // TODO: verify this isn't needed.
    // Initialize serial data registers.
    // MOV DATA_REG_1, 0
    // MOV DATA_REG_2, 0

    // Wait for sync/start pulse from Arduino.
    WBS r31.SYNC_PIN
    WBC r31.SYNC_PIN

    // Store received serial data to DATA_REG_*'s.
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
    QBA READ  // Loop.
