.data
.align 3

neg110: .double -110.0
pos110: .double 110.0
two:    .double 2.0
zero1:   .double 0.0

nl:     .ascii  "\n\0"

.text
.globl main

main:
    li   a7, 7 
    ecall
    fmv.d fa2, fa0

    li   a7, 7       
    ecall
    fmv.d fa1, fa0
    fmv.d fa0, fa2

    la   t0, neg110
    fld  ft2, 0(t0)   

    la   t0, pos110
    fld  ft3, 0(t0)  

    li   t1, 10000

loop:
    fadd.d ft4, ft2, ft3        
    la     t0, two
    fld    ft0, 0(t0)          
    fdiv.d ft4, ft4, ft0        

    fmul.d ft5, ft4, ft4        
    fmul.d ft6, ft5, ft4        

    fsub.d ft7, ft6, fa0       

    la    t0, zero1
    fld   ft1, 0(t0)            
    flt.d t2, ft7, ft1         
    beqz t2, skipNeg
    fneg.d ft7, ft7         

skipNeg:
    fle.d t2, ft7, fa1         
    bnez t2, done

    flt.d t2, ft6, fa0        

    bnez t2, setLow             

    fmv.d ft3, ft4
    j loopDec

setLow:
    fmv.d ft2, ft4

loopDec:
    addi t1, t1, -1
    bgtz t1, loop

done:
    fmv.d fa0, ft4
    li   a7, 3       
    ecall

    li   a7, 4      
    la   a0, nl
    ecall

    li   a7, 10
    ecall