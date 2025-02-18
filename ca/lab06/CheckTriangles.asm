    .text
    .globl main

main:
    
    li a7, 5        
    ecall
    mv s1, a0       
    li a7, 5
    ecall
    mv s2, a0       
    li a7, 5
    ecall
    mv s3, a0       

    
    mv a0, s1
    mv a1, s2
    mv a2, s3
    jal ra, checkTriangles
    mv s0, a0       

    
    beq s0, zero, exit_prog

loop:
   
    li a7, 5
    ecall
    mv t3, a0       
    li a7, 5
    ecall
    mv t4, a0       
    li a7, 5
    ecall
    mv t5, a0       

    
    mv a0, t3
    mv a1, t4
    mv a2, t5
    jal ra, checkTriangles
    mv t6, a0       

    
    beq t6, zero, print_last

    
    li t0, 1
    beq s0, t0, print_Y_newline
    li t0, 2
    beq s0, t0, print_N_newline
    
    j update_current

print_Y_newline:
    li a0, 89      
    li a7, 11
    ecall
    li a0, 10      
    li a7, 11
    ecall
    j update_current

print_N_newline:
    li a0, 78      
    li a7, 11
    ecall
    li a0, 10     
    li a7, 11
    ecall
    j update_current

update_current:
    
    mv s1, t3
    mv s2, t4
    mv s3, t5
    mv s0, t6
    j loop

print_last:
    
    li t0, 1
    beq s0, t0, print_Y_no_newline
    li t0, 2
    beq s0, t0, print_N_no_newline
    j exit_prog

print_Y_no_newline:
    li a0, 89    
    li a7, 11
    ecall
    j exit_prog

print_N_no_newline:
    li a0, 78     
    li a7, 11
    ecall
    j exit_prog

exit_prog:
    li a7, 10    
    ecall


checkTriangles:
    
    li t0, 0
    bne a0, t0, check_triangle
    bne a1, t0, check_triangle
    bne a2, t0, check_triangle
    li a0, 0
    jr ra

check_triangle:
   
    add t1, a1, a2
    slt t2, t1, a0   
    bne t2, zero, not_triangle

    
    add t1, a0, a2
    slt t2, t1, a1
    bne t2, zero, not_triangle

   
    add t1, a0, a1
    slt t2, t1, a2
    bne t2, zero, not_triangle

    li a0, 1       
    jr ra

not_triangle:
    li a0, 2       
    jr ra
