    .text
    .globl main


main:
   
    li a7, 5         
    ecall
    mv t0, a0         
    mv s1, t0     

    
    slli t0, t0, 2    
    sub sp, sp, t0    
    mv s0, sp         

    
    li t2, 0
    
    li a7, 5
    ecall
    mv t6, a0
           
input_loop:
    bge t2, s1, choose_sort   
    li a7, 5          
    ecall             
    slli t3, t2, 2    
    add t4, s0, t3   
    sw a0, 0(t4)      
    addi t2, t2, 1
    j input_loop

choose_sort:
	bnez t6, sort_call
	
	

call_sort:
    
    mv a0, s0       
    slli t0, s1, 2  
    add a1, s0, t0  
    jal ra, sort_function

    
    li t2, 0         
print_loop:
    bge t2, s1, print_done 
    slli t3, t2, 2   
    add t4, s0, t3   
    lw a0, 0(t4)     
    li a7, 1        
    ecall
    addi t2, t2, 1
    blt t2, s1, print_space  
    j print_loop_end
print_space:
    li a0, 10       
    li a7, 11       
    ecall
print_loop_end:
    j print_loop

print_done:
    
    slli t0, s1, 2   
    add sp, sp, t0
    li a7, 10       
    ecall


sort_function:
    addi sp, sp, -4
    sw s0, 0(sp)       
    mv s0, a0          

    
    sub t0, a1, s0     
    srai t0, t0, 2     
    li t1, 1
    ble t0, t1, sort_return  

    li t2, 0         
outer_loop:
    add t1, t0, zero  
    addi t1, t1, -1  	
    bge t2, t1, sort_return  

    li t3, 0         
inner_loop:
    
    add t1, t0, zero  
    sub t1, t1, t2    
    addi t1, t1, -1   
    bge t3, t1, inner_loop_end

    
    slli t4, t3, 2    
    add t4, s0, t4    
    lw t5, 0(t4)      

    
    addi t1, t3, 1    
    slli t1, t1, 2    
    add t1, s0, t1    
    lw a0, 0(t1)      

    
    ble t5, a0, no_swap

    slli t4, t3, 2    
    add t4, s0, t4    
    sw a0, 0(t4)      
    sw t5, 0(t1)      
no_swap:
    addi t3, t3, 1
    j inner_loop
inner_loop_end:
    addi t2, t2, 1
    j outer_loop

sort_return:
    lw s0, 0(sp)
    addi sp, sp, 4
    jr ra
    
    
    
    
sort_call:
    
    mv a0, s0       
    slli t0, s1, 2  
    add a1, s0, t0  
    jal ra, sort_function_1
    li t2, 0
    j print_loop

sort_function_1:
    addi sp, sp, -4
    sw s0, 0(sp)       
    mv s0, a0          

    
    sub t0, a1, s0     
    srai t0, t0, 2     
    li t1, 1
    ble t0, t1, sort_return_1  

    li t2, 0         
outer_loop_1:
    add t1, t0, zero  
    addi t1, t1, -1  	
    bge t2, t1, sort_return_1 

    li t3, 0         
inner_loop_1:
    
    add t1, t0, zero  
    sub t1, t1, t2    
    addi t1, t1, -1   
    bge t3, t1, inner_loop_end_1

    
    slli t4, t3, 2    
    add t4, s0, t4    
    lw t5, 0(t4)      

    
    addi t1, t3, 1    
    slli t1, t1, 2    
    add t1, s0, t1    
    lw a0, 0(t1)      

    li s7, 10
    rem s8, t5, s7
    li s7, 10
    rem s9, a0, s7
    bge s8, s9, no_swap_1

    slli t4, t3, 2    
    add t4, s0, t4    
    sw a0, 0(t4)      
    sw t5, 0(t1)      
no_swap_1:
    addi t3, t3, 1
    j inner_loop_1
inner_loop_end_1:
    addi t2, t2, 1
    j outer_loop_1

sort_return_1:
    lw s0, 0(sp)
    addi sp, sp, 4
    jr ra
    
