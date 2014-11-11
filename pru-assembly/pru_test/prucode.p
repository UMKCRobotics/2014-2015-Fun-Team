// prucode.p

.origin 0
.entrypoint START

#include "prucode.hp"

// 200mhz clock = 200k cycles in a ms
// Assuming a decrement delay loop has 2 instructions.
#DEFINE DELAY_1MS 200000 / 2

START:

    // Enable OCP master port
    LBCO      r0, CONST_PRUCFG, 4, 4
    CLR     r0, r0, 4         // Clear SYSCFG[STANDBY_INIT] to enable OCP master port
    SBCO      r0, CONST_PRUCFG, 4, 4

    // Configure the programmable pointer register for PRU0 by setting c28_pointer[15:0]
    // field to 0x0120.  This will make C28 point to 0x00012000 (PRU shared RAM).
    MOV     r0, 0x00000120
    MOV       r1, CTPPR_0
    ST32      r0, r1

    // Configure the programmable pointer register for PRU0 by setting c31_pointer[15:0]
    // field to 0x0010.  This will make C31 point to 0x80001000 (DDR memory).
    MOV     r0, 0x00100000
    MOV       r1, CTPPR_1
    ST32      r0, r1

    //Load values from external DDR Memory into Registers R0/R1/R2
    // Load 12 bytes into r0 from (CONST_DDR + 0)
    LBCO      r0, CONST_DDR, 0, 12

    //Store values from read from the DDR memory into PRU shared RAM
    // Store 12 bytes into r0 from (CONST_PRUSHAREDRAM + 0)
    SBCO      r0, CONST_PRUSHAREDRAM, 0, 12

    // LOOP1 counter
    MOV r1, 10000000
LOOP1:
    // Turn pin on
    SET r30.t14

    // Output voltage = 3.3 * on count / (on + off count)
    // Delay ON counter
    MOV r0, 10
DEL_ON:
    // delay: decrement r0 while r0 != 0
    SUB r0, r0, 1
    QBNE DEL_ON, r0, 0

    // Turn pin off
    CLR r30.t14

    // Delay OFF counter
    MOV r0, 90
DEL_OFF:
    SUB r0, r0, 1
    QBNE DEL_OFF, r0, 0

    SUB r1, r1, 1  // decrement r1 (loop counter)
    QBNE LOOP1, r1, 0  // goto loop1 if r1 != 0

    // Send notification to Host for program completion
    MOV       r31.b0, PRU0_ARM_INTERRUPT+16

    // Halt the processor
    HALT
