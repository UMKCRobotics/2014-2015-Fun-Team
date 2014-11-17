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
    MOV LOOP_REG, 0  // Initialize data loop counter.
    MOV DATA_REG, 0  // Reset byte storage.

START_BIT:
    QBBS START_BIT, r31.RX_PIN  // Wait for beginning of start bit (high -> low).
    delay DELAY_AFTER_START  // Delay until middle of first data bit.

DATA_BIT:
    // Only set DATA_REG bit if DATA_PIN is high.
    QBBC DATA_BIT_2, r31.RX_PIN
    SET DATA_REG, LOOP_REG

DATA_BIT_2:
    // Delay and loop while more data bits remain.
    // Reminder: delay still happens after final data bit (before stop bit).
    delay DELAY_PER_BIT
    ADD LOOP_REG, LOOP_REG, 1
    QBNE DATA_BIT, LOOP_REG, 8

WRITE:
    SBBO DATA_REG, RAM_ADDR_REG, 0, 4  // Write byte to ram.
    QBA MAIN_LOOP
