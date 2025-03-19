    .data
m:                  .word 5          
t:                  .word 1000       
interrupt_count:    .word 0          

    .text
    .globl main

main:
    
    la   a0, handle_interrupt     
    csrw a0, utvec

    
    csrr a0, uie
    ori  a0, a0, 0x10            
    csrw a0, uie

    csrr a0, ustatus
    ori  a0, a0, 0x1             
    csrw a0 , ustatus


    li   a0, 0xFFFF0018          
    lw   a1, 0(a0)              
    la   a2, t                   
    lw   a2, 0(a2)               
    add  a1, a1, a2              
    li   a3, 0xFFFF0020          
    sw   a1, 0(a3)               

    
main_loop:
    j main_loop


handle_interrupt:
    
    la   t0, interrupt_count
    lw   t1, 0(t0)              
    addi t1, t1, 1
    sw   t1, 0(t0)

    
    la   t2, m
    lw   t2, 0(t2)              
    bge  t1, t2, exit_program   

    
    li   t3, 0xFFFF0018         
    lw   t3, 0(t3)              
    la   t4, t
    lw   t4, 0(t4)              
    add  t3, t3, t4             
    li   t5, 0xFFFF0020         
    sw   t3, 0(t5)              

    
    uret


exit_program:
    li   a7, 10   
    ecall
