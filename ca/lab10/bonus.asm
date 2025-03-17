.eqv CUR 0xFFFF0018
.eqv NEW 0xFFFF0020

.macro timer(%timeout)
    lw   t0, CUR
    addi t0, t0, %timeout
    sw   t0, NEW, t1
.end_macro

.data
current_thread: .word 0
thread1_done: .word 0          
thread2_done: .word 0          
N: .word 5                   


thread1_regs: .word 0, 0, 0, 0, thread1_loop
thread2_regs: .word 0, 0, 0, 0, thread2_loop

msg1: .asciz "Thread1: "    
msg2: .asciz "Thread2: "
newline: .asciz "\n"

.text
j main

handler:
    addi sp, sp, -32
    sw t0, 0(sp)
    sw t1, 4(sp)
    sw t2, 8(sp)
    sw t3, 12(sp)
    sw t4, 16(sp)
    sw a0, 20(sp)
    sw a7, 24(sp)
    sw ra, 28(sp)

    la t0, current_thread
    lw t1, 0(t0)

    beqz t1, check_thread1_active
    la t2, thread2_done
    lw t3, 0(t2)
    bnez t3, switch
    j save_thread
check_thread1_active:
    la t2, thread1_done
    lw t3, 0(t2)
    bnez t3, switch

save_thread:
    beqz t1, save_thread1
    la t2, thread2_regs
    sw s0, 0(t2)
    sw s1, 4(t2)
    sw s2, 8(t2)
    sw s3, 12(t2)
    csrr t3, uepc
    sw t3, 16(t2)
    j switch

save_thread1:
    la t2, thread1_regs
    sw s0, 0(t2)
    sw s1, 4(t2)
    sw s2, 8(t2)
    sw s3, 12(t2)
    csrr t3, uepc
    sw t3, 16(t2)

switch:
    xori t1, t1, 1
    beqz t1, check_thread1
    la t2, thread2_done
    lw t3, 0(t2)
    beqz t3, switch_done
    j switch
check_thread1:
    la t2, thread1_done
    lw t3, 0(t2)
    beqz t3, switch_done
    j switch

switch_done:
    sw t1, 0(t0)
    beqz t1, load_thread1

    la t2, thread2_regs
    lw s0, 0(t2)
    lw s1, 4(t2)
    lw s2, 8(t2)
    lw s3, 12(t2)
    lw t3, 16(t2)
    csrw t3, uepc
    j handler_end

load_thread1:
    la t2, thread1_regs
    lw s0, 0(t2)
    lw s1, 4(t2)
    lw s2, 8(t2)
    lw s3, 12(t2)
    lw t3, 16(t2)
    csrw t3, uepc

handler_end:
    lw t0, 0(sp)
    lw t1, 4(sp)
    lw t2, 8(sp)
    lw t3, 12(sp)
    lw t4, 16(sp)
    lw a0, 20(sp)
    lw a7, 24(sp)
    lw ra, 28(sp)
    addi sp, sp, 32

    timer 2000
    uret

main:
    la t0, thread1_regs
    sw zero, 0(t0)
    lw t1, N
    sw t1, 4(t0)
    la t1, msg1
    sw t1, 8(t0)
    li t1, 4
    sw t1, 12(t0)

    la t0, thread2_regs
    sw zero, 0(t0)
    lw t1, N
    sw t1, 4(t0)
    la t1, msg2
    sw t1, 8(t0)
    li t1, 4
    sw t1, 12(t0)

    la t0, handler
    csrw t0, utvec
    csrsi ustatus, 1
    csrsi uie, 0x10
    timer 2000

    la t0, thread1_regs
    lw s0, 0(t0)
    lw s1, 4(t0)
    lw s2, 8(t0)
    lw s3, 12(t0)
    j thread1_loop

thread1_loop:
    bgt s0, s1, mark_thread1_done

    mv a0, s2
    li a7, 4
    ecall

    mv a0, s0
    li a7, 1
    ecall

    la a0, newline
    li a7, 4
    ecall

    addi s0, s0, 1
    wfi
    j thread1_loop

mark_thread1_done:
    la t0, thread1_done
    li t1, 1
    sw t1, 0(t0)
    j check_exit

thread2_loop:
    bgt s0, s1, mark_thread2_done

    mv a0, s2
    li a7, 4
    ecall

    mv a0, s0
    li a7, 1
    ecall

    la a0, newline
    li a7, 4
    ecall

    addi s0, s0, 1
    wfi
    j thread2_loop

mark_thread2_done:
    la t0, thread2_done
    li t1, 1
    sw t1, 0(t0)

check_exit:
    la t0, thread1_done
    lw t1, 0(t0)
    la t0, thread2_done
    lw t2, 0(t0)
    and t3, t1, t2
    beqz t3, handler_end
    li a7, 10
    ecall
