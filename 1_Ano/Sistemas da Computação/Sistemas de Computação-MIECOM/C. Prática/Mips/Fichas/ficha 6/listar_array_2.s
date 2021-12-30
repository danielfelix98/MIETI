# listar_array_2.s

	.data		# Data declaration section

array:	.word 70,602,102,18,15,-4,89,8078,-475,289
size:   .word 10
nl:		.asciiz "\n"

	.text

main:			# Start of code section

    li $v0, 5
    syscall # read_int from console
    move $t0, $v0 # move to t0 int read


    # Adicione o código necessário aqui



end:
    move $a0, $s1
    li $v0, 1
    syscall # print_int do valor em s1

    la $a0,nl
    li $v0,4
    syscall # print_string "\n"


# END OF PROGRAM
