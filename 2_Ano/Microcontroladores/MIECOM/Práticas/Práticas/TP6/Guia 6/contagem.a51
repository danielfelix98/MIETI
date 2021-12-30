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
		MOV 	T2MOD,#00H		; temporizador2 de 8-bit com auto-reload
		MOV 	T2CON,#00H	
		SETB	ET2
		SETB	EA
		MOV 	DPTR,#MENSAGEM	; DPTR toma o valor do apontador de MENSAGEM, ou seja o valor da primeira posição da string
		MOV		R0,#00H
		MOV		R1,#00H
		MOV		R2,#00H	
		
		MOV     R3,#00H
		MOV		R4,#00H
		MOV		R5,#00H
		MOV		R6,#250
		MOV		R7,#10
		
		MOV		A,R6
		MOV		B,#100
		DIV		AB
		MOV		R3,A
		MOV		R4,B
		
		MOV		B,#10
		MUL		AB
		MOV		R3,A
		
		MOV		B,#10
		MOV		A,R4
		DIV		AB
		MOV		R4,A
		
		ADD		A,R3
		MOV		R5,A

		MOV		A,#0FFH
		SUBB	A,R5
		MOV		R7,A
	
TIMER: 
		CALL	TIMER_OFF
		CALL	TIMER_ON
		JMP 	TIMER;

TIMER_OFF:
		
		MOV 	TL2,#57H
		MOV 	TH2,#9EH
		MOV		RCAP2L,TL2
		MOV		RCAP2H,TL2
		SETB 	TR2			; início da contagem TIMER
		JNB 	TF2,$		; esperar pelo fim da contagem
		CLR 	TF2			; limpar flag
		RET

TIMER_ON:
		MOV 	TL2,#0A8H
		MOV 	TH2,#61H
		MOV		RCAP2L,TL2
		MOV		RCAP2H,TL2
		SETB 	TR2			; início da contagem TIMER
		JNB 	TF2,$		; esperar pelo fim da contagem
		CLR 	TF2			; limpar flag
		RET

RETORNAR:
		RETI
ISR:	
		CLR		RI
		CPL 	P3.7
		INC		R1
		CJNE	R1,#250,RETORNAR
		
CONTAGEM:
		MOV		A,R0			; A = R4
		MOVC	A,@A+DPTR  		; A = ao conteudo da 1ª posição da mensagem/String
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
MENSAGEM:
		DB	0Ch,0CFh,54h,46h,87h,26h,24h,4Fh,04h,07h,05H,04H,3CH,0CH,34H,35H		

END