#include<89c51ic2.inc>
CSEG AT 0H

mov 	sp,#5fh
jmp 	main

cseg at 30h
	main:
		mov p0,#0ffh
		call rotina
		jz main
		swap a
		mov p1,a
		jmp main
	
	cseg at 200h
		rotina:
		mov a,p2
		ret

END