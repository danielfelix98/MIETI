

	NAME	MAIN
#include <89c51ic2.inc>

		EXTRN		CODE	(INICIOH2A)
		NO_LOOPS	EQU		11
		CSEG AT 00H
		LJMP START
	
			
		CSEG	AT	1000H					;inicializar a memória na posição 1000h
TABLE:
			DB 10,07,12,03,15,10,15,14,08,07,00 		; guardar os valores na posição de memória
				
START:	
		MOV 	DPTR,#1000H					;mover a posição 1000h para o DPTR
		MOV		R2,#NO_LOOPS				; passar a constante de fim de ciclo para R2
		MOV 	R1,#8H						; inicializar o valor do array dos valores guardados
			
LOOP:
		CLR		A  ;Limpar o A
		MOVC	A,@A+DPTR ; mover a posição da memoria de codigo do valor a analisar 
		MOV		R0,A
		PUSH	ACC
		LCALL	INICIOH2A  ; chamar a função INICIOH2A
		MOV		A,B  
		MOVX 	@R1,A 		; guarda no valor apontado por R1 o valor modificado pela função
		POP 	ACC
		INC 	DPTR		; incrementa 1 byte, ou seja passa para o valor seguinte guardado na memória de código
		INC		R1			; incrementa 1 byte no array dos valores modificados
		DJNZ	R2,LOOP		; verifica se o loop chegou ao fim, senão decrementa R2
		SJMP	$
END