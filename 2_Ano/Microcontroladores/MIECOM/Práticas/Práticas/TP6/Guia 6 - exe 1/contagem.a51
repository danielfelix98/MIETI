; Filipe Rodrigues nº 68455
; Eduardo Silva nº 70216

;	INICIO DE PROGRAMA
		
#include <89C51IC2.inc>	
	NAME MAIN
	EXTRN 	CODE 	(ENVIAR_RS232, RECEBER_RS232, CONFIG_RS232)
		
	CSEG	AT	0000H
	JMP		MAIN
	CSEG	AT	002BH
	JMP		ISR
	
	CSEG	AT		0030H			
MAIN:
		MOV 	T2MOD,#01H	
		MOV 	T2CON,#04H	
		SETB	ET2
		;SETB 	TR2			
		SETB	EA
		MOV 	DPTR,#MENSAGEM	
		MOV		R0,#00H
		MOV		R1,#00H
		MOV		R2,#00H	
		;MOV     R3,#00H
		
TIMER:   
		MOV 	TL2,#LOW(-1000)
		MOV 	TH2,#HIGH(-1000)
		MOV		RCAP2L,#LOW(-1000)
		MOV		RCAP2H,#HIGH(-1000)
		JMP		$

ISR:	
		CLR 	TF2			; limpar flag
		CPL 	P3.7
		INC		R2
		CJNE	R2,#500,RETORNAR
		
CONTAGEM:
		MOV		R2,#00H		
		MOV		A,R0			
		MOVC	A,@A+DPTR  		
		MOV		P1,A			; o display toma o valor desse conteudo
			; verifica se passou o nº 9 (ciclo "if-else")
		MOV		A,R0			
		CJNE	A,#0Fh,INCREMENTAR				; salta para "DEVOLVER", se A(=R0) for diferente de "Ah"(=10)
			; proximo nº toma valor de "0"
		MOV		R0,#0h						; R0 = "0h"
		MOV		R1,#0h						; R1 = "0h"
		RETI
INCREMENTAR:
		INC		R0							; somar "1" a R0
		INC		R1							; somar "1" a R1
		RETI
RETORNAR:
		RETI
MENSAGEM:
		DB	0Ch,0CFh,54h,46h,87h,26h,24h,4Fh,04h,07h,05H,04H,3CH,0CH,34H,35H		

END