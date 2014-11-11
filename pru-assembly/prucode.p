.origin 0
.entrypoint INIT

#define PRU0_ARM_INTERRUPT  (1<<5) + 3

INIT:
    // Enable OCP master port for memory communication
    LBCO r0, C4, 4, 4
    CLR  r0, r0, 4
    SBCO r0, C4, 4, 4

    // Load the data ram address (0)
    MOV r0, 0
    // Load first 4 bytes from addr at r0 into r2
    LBBO r2, r0, 0, 4  // dest, src address, offs, size

    // Add values loaded from ram (r2) into r3.
    ADD r3, r2.w0, r2.w2
    // Write result to ram.
    SBBO r3, r0, 4, 2  // value, dest addr, offs, size

    // Subtract values and write result to ram.
    SUB r3.w2, r2.w0, r2.w2
    SBBO r3.w2, r0, 6, 2

    // Notify main cpu and stop.
    MOV R31.b0, PRU0_ARM_INTERRUPT
    HALT
