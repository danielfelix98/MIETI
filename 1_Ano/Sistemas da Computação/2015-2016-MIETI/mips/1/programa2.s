# PROGRAM START

	.data		# Data declaration section
A:	.word	14 
B:	.word	5 
C:	.word	0 

	.text

main:			# Start of code section
	
	lw $s3,0x10010000
	lw $s2,0x10010004
	add $s1,$s3,$s2 # comenta'rio!!!!
	sw $s1,C

# END OF PROGRAM
