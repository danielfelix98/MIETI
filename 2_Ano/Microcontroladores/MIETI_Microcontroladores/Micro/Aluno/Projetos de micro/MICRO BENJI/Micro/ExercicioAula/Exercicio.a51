CSEG AT 0H

	
	MOV 	B,#0BBH              	;DIVISOR
	MOV 	DPTR,#0AD6BH			;DIVIDENDO

	MOV 	R2,DPH	
	MOV 	R1,DPL

	MOV 	A,R1
	MOV 	DPTR,#0H
	
SUB:
	SUBB 	A,B
	INC 	DPTR                    ;CONTAGEM DE SUBTRAÇÕES, FUNCIONA COMO QUOCIENTE NO FINAL DO PROGRAMA
	JB 		cy,DECREMENTA
	JMP 	SUB
	
DECREMENTA:
	DEC 	R2
	CLR 	C
	CJNE 	R2,#0H,SUB
	JMP 	FIM

FIM:
	MOV 	B,A   					;B FICA COM O RESTO DA DIVISÃO.
	JMP $
	
END
	
;Testei e funcionou corretamente com o meu exemplo.
;Cumprimentos, Hélder Rafael Costa Veloso, aluno nº 70017, de MIETI.


