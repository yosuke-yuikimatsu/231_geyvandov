    .text
    .globl main

main:
    li a7, 5         
    ecall      

   
    bltz a0, convert
    j process
convert:
    neg a0, a0       

process:
    
    mv t0, a0        
    li t1, 0
    
    li a0, 10
    li a7, 11        
    ecall    

digit_loop:
    beq t0, zero, print_result   

    li t2, 10
    rem t3, t0, t2   
    add t1, t1, t3   

    div t0, t0, t2   
    j digit_loop

print_result:
    
    mv a0, t1        
    li a7, 1         
    ecall

    
    li a0, 10
    li a7, 11        
    ecall

    
    li a7, 10
    ecall
