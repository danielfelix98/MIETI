# UNTITLED PROGRAM

	.data		# Data declaration section


nl:		.asciiz "\n"
porto:	.word 0,0,0,0,0,0,0,0,0,0



	.text

main:			# Start of code section

# carregar o array
	li $s4,1	
	li $s5,1
	li $s6,10
	la $t0, porto
scp:

	li $v0, 5
	syscall
	sw $v0, ($t0)
	add $s4, $s4, $s5
	bgt $s4, $s6, mostrar
	add $t0, $t0, 4	
	j scp


	
# ler o array para a consola
mostrar:
	li $s4,1	
	la $t0, porto
slb:
	lw $s1, ($t0)
	move $a0, $s1
	li $v0, 1
	syscall
	la $a0,nl	
	li $v0,4	
	syscall
	add $s4, $s4, $s5
	bgt $s4, $s6, fim
	add $t0, $t0, 4	
	j slb
fim:




# END OF PROGRAM
