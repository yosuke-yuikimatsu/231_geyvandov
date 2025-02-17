	.text
main:
	addi a7, zero, 5
	ecall
	add t0, zero, a0
	addi a7, zero, 5
	ecall
	add t1, zero, a0
	addi a7, zero, 5
	ecall
	add t2, zero, a0
	addi a7, zero, 5
	ecall
	add t3, zero, a0
	add a0, t0, t2
	addi a7, zero, 1
	ecall
	addi a7, zero, 11
	addi a0 , zero, '\n'
	ecall
	add a0, t1, t3
	addi a7, zero, 1
	ecall
	addi a7, zero, 11
	addi a0 , zero, '\n'
	ecall