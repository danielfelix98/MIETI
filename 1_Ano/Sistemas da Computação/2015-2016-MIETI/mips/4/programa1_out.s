# PROGRAM START

	.data	# Data declaration section
A:	.word	14 #0x10010000
B:	.word	5 #0x10010004
C:	.word	0 #0x10010008


	.text	# Start of code section
main:
	
	lw $s3,A 
	lw $s2,B 
	
	add $s1,$s3,$s2 
	sw $s1,C 

	li $v0, 1 			# identificador da chamada ao sistema para print_int
	move $a0, $s1 		# move $s1 para $a0 (argumento necessário para a função print_int)
	syscall 			# chamada ao sistema

# END OF PROGRAM
