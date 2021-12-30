# UNTITLED PROGRAM

	.data		# Data declaration section

	.text

main:			# Start of code section
	
		li $s1, 1
		li $s2, 1
		li $s3, 10	

PRINT:	li  $v0, 1            # system call code for print_int
      	move $a0, $s1         # move g to argument 0
      	syscall               # print it
	
		beq $s1,$s3,FIM
		add $s1, $s1, $s2
		j PRINT
FIM:

# END OF PROGRAM
