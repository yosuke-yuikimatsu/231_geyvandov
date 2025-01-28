.text
main: 
	addi a7, zero, 5
	ecall
	add t0, zero, a0
	
	addi a7, zero, 5
	ecall
	add t1, zero, a0
	
	# Task 1 (x + 5) - (y - 7)
	add t2, t0, zero
	addi t2, t2, 5
	addi t3, t1, -7
	sub t2, t2, t3
	add a0, zero, t2
	addi a7, zero, 1
	ecall
	
	addi a7, zero, 11
	addi a0, zero, '\n'
	ecall
	
	# Task 2 2 * x * x - 3 * y + 4
	mul t2, t0, t0
	slli t2, t2, 1
	slli t3, t1, 1
	add t3, t3, t1
	sub t2, t2, t3
	addi t2, t2, 4
	add a0, zero, t2
	addi a7, zero, 1
	ecall
	
	addi a7, zero, 11
	addi a0, zero, '\n'
	ecall
	
	# Task 3 (x + 5) / y + 10 / (y - 1)
	addi t2, t0, 5
	div t2, t2, t1
	addi t3, t1, -1
	addi t4, zero, 10
	div t4, t4, t3
	add t2, t2, t4
	add a0, zero, t2
	addi a7, zero, 1
	ecall
	
	addi a7, zero, 11
	addi a0, zero, '\n'
	ecall
	
	# Task 4 (x / y) * y + x % y = x
	div t2, t0, t1
	mul t2, t2, t1
	rem t3, t0, t1
	add t2, t2, t3
	add a0, zero, t2
	addi a7, zero, 1
	ecall
	
	addi a7, zero, 11
	addi a0, zero, '\n'
	ecall
	
	# Task 5 x > y ? 1 : 0
	sub t2, t0, t1
	srai t3, t2, 31
	xori t3, t3, -1
	sub t4, zero, t2
	or t4, t2, t4
	srai t4, t4, 31
	andi t4, t4, 1
	and a0, t3, t4
	addi a7, zero, 1
	ecall
	
	addi a7, zero, 11
	addi a0, zero, '\n'
	ecall
