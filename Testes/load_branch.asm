.data
valor1:		.byte 0xFF
valor2:		.byte 0x01
valor3:		.half 0xFFFF
valor4:		.half 0x0001
msg1:          	.asciz "0xFF e maior que 0x01 (unsigned) "
msg1e:          .asciz "0xFF e menor que 0x01 (unsigned) "
msg2:          	.asciz "0xFFFF e maior que 0x0001 (unsigned)"
msg2e:          .asciz "0xFFFF e menor que 0x0001 (unsigned)"

.text
	la t0,valor1
	lb a1,0(t0)
	la t0,valor2
	lbu a2,0(t0)
	la t0,valor3
	lh a3,0(t0)
	la t0,valor4
	lhu a4,0(t0)
	
comp1:	bltu a2,a1,cer1
	li a7, 4      # imprime errada
	la a0, msg1e 
	ecall
	b comp2
cer1:	li a7, 4      # imprime certa
	la a0, msg1 
	ecall
comp2:	bgeu a3,a4,cer2
	li a7, 4      # imprime errada
	la a0, msg2e 
	ecall
	b set
cer2:	li a7, 4      # imprime certa
	la a0, msg2 
	ecall
set:	slt s0, a1,a2
	sltu s1,a1,a2
exit:	li a7,10
	ecall
	
	