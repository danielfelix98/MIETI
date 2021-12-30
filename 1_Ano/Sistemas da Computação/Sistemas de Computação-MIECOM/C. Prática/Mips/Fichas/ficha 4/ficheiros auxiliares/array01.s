# UNTITLED PROGRAM

	.data		# Data declaration section

array: .space 40

	.text

main:			# Start of code section
	
# ler os 10 número e preencher o array com esses números
	
	li $t1, 0 		# $t1 - registo usado para contar númerso
	li $t2, 10		# $t2 - registo usado para identificar o fim de ciclo
	la $t0, array 	# $t0 - registo que funcionará como índice do aray,
				# e começa por apontar para o primeiro elemento
flag1:
	li $v0, 5		# leitura da consola
	syscall		
	sw $v0, ($t0)	# coloca o valor lido no array (em memória)
	add $t1, $t1, 1	# assinala que leu um elemento 
	add $t0, $t0, 4	# coloca o índice do array na posição seguinte
	bne $t1, $t2, flag1 #testa se já leu ou não os 10 elementos


	

# END OF PROGRAM
