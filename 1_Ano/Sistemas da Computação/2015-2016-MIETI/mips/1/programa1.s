# PROGRAM START

	.data		# Data declaration section
A:	.word	14 
B:	.word	5 
C:	.word	0 

	.text

main:			# Start of code section
	
	lw $s3,A
	lw $s2,B
	add $s1,$s3,$s2 # comenta'rio!!!!
	sw $s1,C

# END OF PROGRAM
