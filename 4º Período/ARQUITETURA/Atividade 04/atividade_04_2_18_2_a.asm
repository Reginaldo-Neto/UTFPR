#REGINALDO GREGÓRIO DE SOUZA NETO
#RA: 2252813
.data
a: .word 5
b: .word -1
.text
.globl main
#for(i=0; i<a; i++)
#a += b;
main:   lw $s0, a
	lw $s1, b
	addi $t0, $s0, 0
Loop:	slt $t1, $t0, $s0
	beq $t1, $zero, Exit
	add $s0, $s0, $s1
	addi $t0, $t0, 1
	j Loop

Exit: nop