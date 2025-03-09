.data
.text

.globl main

main:
    li a7, 5         
    ecall
    mv t0, a0       

    
    li a7, 5
    ecall
    mv t1, a0       

    
    li a7, 5
    ecall
    mv t2, a0       

    
    fcvt.d.w fa0, t0
    fcvt.d.w fa1, t1
    fdiv.d fa0, fa0, fa1  

    
    mv a0, t2

    
    jal ra, fraction_truncate

    

    
    li a7, 3         
    ecall

    
    li a7, 11        
    li a0, 10        
    ecall

    
    li a7, 10        
    ecall



fraction_truncate:
    li t1, 1
    mv t3, a0
pow_loop:
    beqz t3, pow_done
    li t4, 10
    mul t1, t1, t4
    addi t3, t3, -1
    j pow_loop
pow_done:

    fcvt.d.w fa1, t1

    fmul.d fa0, fa0, fa1

    fcvt.w.d a1, fa0, rtz

    fcvt.d.w fa0, a1

    fdiv.d fa0, fa0, fa1

    jr ra
