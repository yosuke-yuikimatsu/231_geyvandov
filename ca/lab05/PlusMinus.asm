    .text
    .globl main

main:
    li a7, 5          
    ecall
    mv t1, a0         

    
    li t0, 0          
    li t2, 0          
    li t3, 1          

loop:
    bge t0, t1, print_result   

    
    li a7, 5          
    ecall

    
    mul t4, t3, a0    
    add t2, t2, t4    

    
    neg t3, t3

    
    addi t0, t0, 1
    j loop

print_result:
    
    mv a0, t2
    li a7, 1         
    ecall

    
    li a0, 10
    li a7, 11        
    ecall

    
    li a7, 10
    ecall
