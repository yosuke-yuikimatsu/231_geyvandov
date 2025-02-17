    .text
    .globl main
main:
    
    li a7, 5          
    ecall             
    mv t0, a0         

    
    slli t4, t0, 2    
    sub sp, sp, t4    
    mv s0, sp         

    li t1, 0          
    li t2, 0          

input_loop:
    beq t2, t0, finish_loop  

    
    li a7, 5          
    ecall             
    mv t5, a0         

    
    li t3, 0          
    li t6, 0          
dup_check:
    beq t3, t1, not_dup   
    slli t4, t3, 2        
    add t4, s0, t4        
    lw s1, 0(t4)         
    beq s1, t5, found_dup 
    addi t3, t3, 1        
    j dup_check

found_dup:
    li t6, 1              

not_dup:
    
    beq t6, zero, add_and_print
    
    addi t2, t2, 1
    j input_loop

add_and_print:
    
    mv a0, t5
    li a7, 1              
    ecall
    
    li a0, 10
    li a7, 11             
    ecall

    
    slli t4, t1, 2        
    add t4, s0, t4       
    sw t5, 0(t4)          
    addi t1, t1, 1        
    addi t2, t2, 1        
    j input_loop

finish_loop:
    
    slli t4, t0, 2        
    add sp, sp, t4

    li a7, 10
    ecall
