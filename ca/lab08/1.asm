.macro exit
    li      a7, 10
    ecall
.end_macro


.macro print_dec(%x)
    mv      a0, %x
    li      a7, 1       
    ecall
.end_macro

.macro newline
    li      a0, '\n'
    li      a7, 11
    ecall
.end_macro

    .text
main:
    lui     s0, 0xffff0   
    mv      s1, zero      
    mv      s2, zero      
    li      s3, 20        
    li      s4, 1         

loop:
    li      t0, 1         
    sb      t0, 0x12(s0)   
    lbu     t1, 0x14(s0)   
    bnez    t1, pressed   

    li      t0, 2         
    sb      t0, 0x12(s0)
    lbu     t1, 0x14(s0)
    bnez    t1, pressed

    li      t0, 4         
    sb      t0, 0x12(s0)
    lbu     t1, 0x14(s0)
    bnez    t1, pressed

    li      t0, 8         
    sb      t0, 0x12(s0)
    lbu     t1, 0x14(s0)
    bnez    t1, pressed

    mv      s2, zero      
    j       loop          

pressed:
    beq     t1, s2, loop  
    mv      s2, t1        

    
    andi    t2, t1, 0xF       
    andi    t3, t1, 0xF0      
    srli    t3, t3, 4         

    
    mv      t4, t2            
    li      t5, 0             
row_index_loop:
    beq     t4, s4, row_index_done  
    srai    t4, t4, 1         
    addi    t5, t5, 1         
    j       row_index_loop
row_index_done:

    
    mv      t4, t3            
    li      t6, 0             
col_index_loop:
    beq     t4, s4, col_index_done  
    srai    t4, t4, 1         
    addi    t6, t6, 1         
    j       col_index_loop
col_index_done:

    
    slli    t5, t5, 2         
    add     t5, t5, t6        

    print_dec(t5)             
    newline

    addi    s1, s1, 1         
    ble     s1, s3, loop      

end:
    exit
