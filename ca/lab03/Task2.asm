.text
main:
    addi a7, zero, 5
    ecall
    add t0, zero, a0

    addi a7, zero, 5
    ecall
    add t1, zero, a0

    srl t2, t0, 2
    addi t3, t1, -1
    slli t3, t3, 3
    add t2, t2, t3
    add a0, zero, t2
    addi a7, zero, 1
    ecall

    addi a7, zero, 11
    addi a0, zero, '\n'
    ecall

    sll t2, t0, t1
    addi t2, t2, -10
    add a0, zero, t2
    addi a7, zero, 1
    ecall

    addi a7, zero, 11
    addi a0, zero, '\n'
    ecall

    sra t2, t0, t1
    addi t2, t2, 10
    add a0, zero, t2
    addi a7, zero, 1
    ecall

    addi a7, zero, 11
    addi a0, zero, '\n'
    ecall

    slli t2, t0, 2
    sub t2, t2, t1
    addi t2, t2, 5
    srai t2, t2, 1
    add a0, zero, t2
    addi a7, zero, 1
    ecall

    addi a7, zero, 11
    addi a0, zero, '\n'
    ecall

    slli t2, t0, 2
    slli t3, t0, 1
    add t2, t2, t3
    slli t3, t1, 1
    add t3, t3, t1
    sub t2, t2, t3
    add a0, zero, t2
    addi a7, zero, 1
    ecall

    addi a7, zero, 11
    addi a0, zero, '\n'
    ecall

    addi a7, zero, 10
    ecall
