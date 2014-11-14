.origin 0
.entrypoint INIT

#define PRU0_ARM_INTERRUPT 19
#define PRU1_ARM_INTERRUPT 20

#define GPIO0_ADDR 0x44E07000
#define GPIO1_ADDR 0x4804C000
#define GPIO2_ADDR 0x481AC000
#define GPIO3_ADDR 0x481AF000
#define GPIO_OE_OFFSET 0x134
#define GPIO_DATAOUT_OFFSET 0x13C
#define GPIO_DATAIN_OFFSET 0x138

#define P8_36 16  // AKA gpio2_16
#define P8_37 14  // AKA gpio2_14
#define P8_38 15  // AKA gpio2_15

#define RAM_ADDR_REG r29
#define GPIO_ADDR_REG r28
#define OE_REG r27
#define GPIO_DATA_REG r26
#define LOOP_REG r0

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

    // Set gpio pin to output.
    MOV GPIO_ADDR_REG, GPIO2_ADDR | GPIO_OE_OFFSET
    LBBO OE_REG, GPIO_ADDR_REG, 0, 4
    CLR OE_REG, P8_38
    SBBO OE_REG, GPIO_ADDR_REG, 0, 4

    MOV GPIO_ADDR_REG, GPIO2_ADDR | GPIO_DATAOUT_OFFSET
    MOV LOOP_REG, 100000000

LOOP_TOGGLE_OUT:
    // Set high
    MOV GPIO_DATA_REG, (1 << P8_38)
    SBBO GPIO_DATA_REG, GPIO_ADDR_REG, 0, 4

    // Set low
    MOV GPIO_DATA_REG, 0
    SBBO GPIO_DATA_REG, GPIO_ADDR_REG, 0, 4

    // Loop
    SUB LOOP_REG, LOOP_REG, 1
    QBNE LOOP_TOGGLE_OUT, LOOP_REG, 0

INIT_READ:
    MOV R31.b0, PRU1_ARM_INTERRUPT+16  // Send interrupt to main CPU

    // Set pin to input.
    MOV GPIO_ADDR_REG, GPIO2_ADDR | GPIO_OE_OFFSET
    LBBO OE_REG, GPIO_ADDR_REG, 0, 4
    SET OE_REG, P8_38
    SBBO OE_REG, GPIO_ADDR_REG, 0, 4

    MOV GPIO_ADDR_REG, GPIO2_ADDR | GPIO_DATAIN_OFFSET  // Store GPIO input address.
    MOV RAM_ADDR_REG, 0  // Store data ram address (0) for communication with host.

    MOV LOOP_REG, 50000000  // Reset loop counter

LOOP_READ_IN:
    // Rate: approximately 5 mhz (200 ns).
    LBBO GPIO_DATA_REG, GPIO_ADDR_REG, 0, 4  // Read inputs into local register.
    SBBO GPIO_DATA_REG, RAM_ADDR_REG, 0, 4  // Send to RAM for main CPU to read.

    // Loop counter/jump
    SUB LOOP_REG, LOOP_REG, 1
    QBNE LOOP_READ_IN, LOOP_REG, 0

// Send event interrupt to main CPU and stop.
MOV R31.b0, PRU1_ARM_INTERRUPT+16
HALT
