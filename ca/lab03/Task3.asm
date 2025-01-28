.text
main:
    addi a7, zero, 5
    ecall
    add t0, zero, a0

    addi a7, zero, 5
    ecall
    add t1, zero, a0

    addi t2, zero, -1
    slli t2, t2, 2
    and a0, t0, t2
    addi a7, zero, 1
    ecall

    addi a7, zero, 11
    addi a0, zero, '\n'
    ecall

    addi t2, zero, -1
    srli t2, t2, 30
    or t2, t0, t2
    add a0, zero, t2
    addi a7, zero, 1
    ecall

    addi a7, zero, 11
    addi a0, zero, '\n'
    ecall

    li t2, 1
    sll t2, t2, t1
    or t2, t0, t2
    add a0, zero, t2
    addi a7, zero, 1
    ecall

    addi a7, zero, 11
    addi a0, zero, '\n'
    ecall

    li t2, 1
    sll t2, t2, t1
    not t2, t2
    and t2, t0, t2
    add a0, zero, t2
    addi a7, zero, 1
    ecall

    addi a7, zero, 11
    addi a0, zero, '\n'
    ecall

    addi t2, t1, 3
    slt t3, t0, t2
    slt t4, t2, t0
    or t3, t3, t4
    add a0, zero, t3
    addi a7, zero, 1
    ecall

    addi a7, zero, 11
    addi a0, zero, '\n'
    ecall

    li t2, -5
    li t3, 5
    slt t4, t2, t0
    slt t5, t1, t3
    and t2, t4, t5
    add a0, zero, t2
    addi a7, zero, 1
    ecall

    addi a7, zero, 10
    ecall
