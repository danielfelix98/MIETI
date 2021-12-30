# listar_array_1.s

	.data		# Data declaration section

array:	.word 70,602,102,18,15,-4,89,8078,-475,289 # array of words
size:   .word 10 # size of array
nl:     .asciiz "\n"

	.text

main:			# Start of code section
    
        la $t0, array
        li $t1, 0
        lw $t2, size


iter:	lw $s1, ($t0) # load current element into s1

        li $v0, 1
        move $a0, $s1
        syscall # print_int do valor em s1

        li $v0,4
        la $a0, nl
        syscall # print_string "\n"

        add $t0, $t0, 4 # incrementa o endereço corrente para o endereço do próximo elemento do array
        add $t1, $t1, 1 # incrementa o numero de elementos percorridos
        bne $t1, $t2, iter
end:


# END OF PROGRAM
