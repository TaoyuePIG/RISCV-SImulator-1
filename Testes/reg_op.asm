.data
valor1:		.byte 0x01
valor2:		.byte 0x02
valor3:		.half 0x0001
valor4:		.half 0x0002
memory:		.word 0x2000

.text
	la t0,valor1
	lb a1,0(t0)
	la t0,valor2
	lbu a2,0(t0)
	la t0,valor3
	lh a3,0(t0)
	la t0,valor4
	lhu a4,0(t0)
	la t0,memory
	lw s0,0(t0)
	
	sll t0,a1,a2
	sb t0,0(s0)
	xor t0,a1,a2
	sb t0,1(s0)
	sra t0,a1,a2
	sb t0,2(s0)
	srl t0,a1,a2
	sb t0,3(s0)
	or t0,a3,a4
	sh t0,4(s0)
	and t0,a3,a4
	sh t0,6(s0)
	
exit:	li a7,10
	ecall 