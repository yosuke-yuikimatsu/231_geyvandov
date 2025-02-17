    .data
even_printed: .word 0         

    .text
    .globl main
main:
    
    li a7, 5                
    ecall                   

    
    li a1, 0
    jal ra, rec

   
    la t0, even_printed
    lw t1, 0(t0)
    bnez t1, main_end       
    li a0, 10
    li a7, 11              
    ecall

main_end:
    
    li a7, 10
    ecall


rec:
    
    addi sp, sp, -12
    sw ra, 8(sp)
    sw s0, 4(sp)
    mv s0, a0             

    
    beq a1, s0, rec_base

    
    li a7, 5
    ecall                 
    sw a0, 0(sp)         

    
    addi a1, a1, 1
    mv a0, s0            
    jal ra, rec          

    
    lw t0, 0(sp)

    
    andi t1, t0, 1
    bnez t1, rec_epilogue  

   
    li t2, 1
    la t3, even_printed
    sw t2, 0(t3)

    
    mv a0, t0
    li a7, 1             
    ecall

    
    li a0, 10
    li a7, 11            
    ecall

rec_epilogue:
    
    lw ra, 8(sp)
    lw s0, 4(sp)
    addi sp, sp, 12
    jr ra

rec_base:
    lw ra, 8(sp)
    lw s0, 4(sp)
    addi sp, sp, 12
    jr ra
