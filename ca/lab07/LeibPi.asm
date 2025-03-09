.data
zero1: .float 0.0
one: .double 1.0
minus_one: .double -1.0
four: .double 4.0

.text
.globl main

main:
    li   a7, 5        
    ecall
    mv   s0, a0      

    la   t0, zero1 
    fld  fa0, 0(t0)  

    la   t1, one    
    fld  fa1, 0(t1) 


    li    t0, 0        
    li    t1, 75000    

leibniz_loop:
    beq   t0, t1, leibniz_done

    slli  t2, t0, 1     
    addi  t2, t2, 1     
    fcvt.d.w fa2, t2    

    
    fdiv.d fa2, fa1, fa2

    
    fadd.d fa0, fa0, fa2

    
    fneg.d fa1, fa1

    addi  t0, t0, 1
    j     leibniz_loop

leibniz_done:
    
    la t5, four
    fld fa2, 0(t5)
    fmul.d fa0, fa0, fa2

    mv    a0, s0           
    jal   ra, fraction_truncate

    li    a7, 3           
    ecall

    li    a7, 11           
    li    a0, 10          
    ecall

    li    a7, 10           
    ecall


fraction_truncate:
    li    t1, 1
    mv    t3, a0         
pow_loop:
    beqz  t3, pow_done
    li    t4, 10
    mul   t1, t1, t4     
    addi  t3, t3, -1
    j     pow_loop

pow_done:
    fcvt.d.w fa1, t1     
    fmul.d   fa0, fa0, fa1   
    fcvt.w.d a1, fa0, rtz    
    fcvt.d.w fa0, a1         
    fdiv.d   fa0, fa0, fa1  
    jr       ra
