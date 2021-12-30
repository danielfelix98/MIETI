; Filipe Rodrigues nº 68455
; Eduardo Silva nº 70216

;	INICIO DE PROGRAMA		
#include <89C51IC2.inc>		
		NAME MAIN
		EXTRN 	CODE 	(ENVIAR_RS232, RECEBER_RS232, CONFIG_RS232)
		
		CSEG 	AT	0H
		JMP		MAIN
		CSEG 	AT 	30H
	
MAIN:	
		CALL	CONFIG_RS232	; configura a porta de serie(flags, bourate, etc)
		CALL	RECEBER_RS232
		SUBB	A,#30h
		MOV		R0,A
		
RECOMECAR:
				
		MOV		A,R0
		MOV		R3,A
		MOV 	R4,#0			; inicializa o contador a 0
		MOV 	R2,#0			; inicializa o contador a 0
		INC		R3
		MOV 	DPTR,#MENSAGEM	; DPTR toma o valor do apontador de MENSAGEM, ou seja o valor da primeira posição da string
		
CONTADOR:
		MOV		R5,#138
		MOV		R6,#139
		MOV		R7,#4
		CALL	ESCREVER
		CALL	ATRASO_0
		DEC		R3
		MOV		A,R3
		CJNE	A,#0,CONTADOR
		JMP		RECOMECAR
		
ATRASO_0:
ATRASO_1:
ATRASO_2:
		NOP
		DJNZ	R5,ATRASO_2		
		NOP
		DJNZ	R6,ATRASO_1		
		NOP
		DJNZ	R7,ATRASO_0
		RET

ESCREVER:
        MOV		A,R4
		MOVC	A,@A+DPTR
		MOV		P1,A
		MOV		A,R2
		CALL	ENVIAR_RS232
		INC		R4
		INC		R2
		RET
MENSAGEM:
		DB	0Ch,0CFh,54h,46h,87h,26h,24h,4Fh,04h,07h
		RET
		
END		;FIM DE PROGRAMA