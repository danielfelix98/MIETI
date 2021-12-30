# UNTITLED PROGRAM

	.data	
vector:	.word 	70, 602, 102, 18, 15, -4, 89, 8078, -475, 289
nl:		.asciiz "\n"

	.text

main:			# Start of code section
	
	la $t0, vector	# carregar o endereço de memória do início do vector
	lw $s1, ($t0)	# colocar em $s1 o valor que está na posicao 0 do vector
	move $a0, $s1	# escrever na consola o valor de $s1
	li $v0, 1
	syscall
	la $a0,nl	
	li $v0,4	
	syscall
	addi $t0,$t0,4	# passar para o próximo valor do vector 
	lw $s1, ($t0)	# colocar em $s1 o valor que está na posicao 1 do vector
	move $a0, $s1	# escrever na consola o valor de $s1
	li $v0, 1
	syscall
	la $a0,nl	
	li $v0,4	
	syscall
	addi $t0,$t0,4	# passar para o próximo valor do vector 
	lw $s1, ($t0)	# colocar em $s1 o valor que está na posicao 2 do vector
	move $a0, $s1	# escrever na consola o valor de $s1
	li $v0, 1
	syscall
	la $a0,nl	
	li $v0,4	
	syscall
	addi $t0,$t0,4	# passar para o próximo valor do vector 
	lw $s1, ($t0)	# colocar em $s1 o valor que está na posicao 3 do vector
	move $a0, $s1	# escrever na consola o valor de $s1
	li $v0, 1
	syscall
	la $a0,nl	
	li $v0,4	
	syscall
	li $v0, 10 		# terminar programa
	syscall





# END OF PROGRAM
