.global switch_to_user_mode
.type switch_to_user_mode, @function
switch_to_user_mode:
    /* Set MPP to 2 (User mode) */
    csrr t0, mstatus
    li t1, ~0x1800    /* Clear MPP bits */
    and t0, t0, t1
    csrw mstatus, t0

    /* Enable interrupts */
    csrr t0, mstatus
    li t1, 1 << 3  /* MIE bit */
    or t0, t0, t1
    csrw mstatus, t0

    /* Set mepc to the next instruction after mret */
    auipc t0, 0
    addi t0, t0, 14
    csrw mepc, t0

    /* Execute mret to switch to user mode */
    mret

    /* This code will execute in user mode */
    addi a0, a0, 136  /* Arbitrary operation in user mode */
    
    /* Try to execute a M-mode CSR access (should cause an exception) */
    csrwi mepc, 0

    ret