.text
	    lui     x8, 0x10010
	    xori    x9, x0, 12
	    sw      x9, 0(x8)
	    lui     x5, 0x30000
	    addi    x6, x0, 3
	    srli    x5, x5, 16
	    lw      x9, 0(x8)
	    sll     x6, x6, x9  
	    beq     x5, x6, L1      
	    jal     x0, L2        
	L1: auipc   x7, 0
	    addi    x7, x7, -4
	    jalr    x0, 0(x7)
	L2: ori     x17, x0, 10
	    ecall
