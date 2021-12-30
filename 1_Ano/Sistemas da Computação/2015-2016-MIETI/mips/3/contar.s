# Ficha 3

	.data	
I:		.word 	1
LIMIT:	.word	10

	.text

main:
	lw $s1, I		# i= 1
	li $s2, 1
	lw $s3, LIMIT	

CYCLE: 
	beq $s1,$s3,FIM	     	# se i==LIMIT entao ir para FIM
	add $s1, $s1, $s2 		# i=i+1
	j CYCLE
FIM:

# END OF PROGRAM
