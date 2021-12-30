# O maior de dois números
# Este programa selecciona o maior de dois números
# e coloca-o no registo $s7

	.data		# Data declaration section

	.text

main:					# Start of code section
		li $s0, 20			# primeiro número
		li $s1, 14			# segundo número
		bgt $s0, $s1, benfica   # salta para "benfica" se $s0>$s1
		move $s7, $s1 		# o maior é o $s1
		j FIM 			# Salta para o fim
benfica:	move $s7, $s0 		# o maior é o $s0
FIM: 

# END OF PROGRAM
