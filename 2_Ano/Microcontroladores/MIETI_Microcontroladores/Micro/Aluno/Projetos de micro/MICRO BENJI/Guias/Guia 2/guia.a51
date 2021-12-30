CSEG 	AT 0H
	LJMP MAIN

CSEG 	AT 0BH
	LJMP 	LIGA_LARANJA

CSEG 	AT 33H

MAIN:
	MOV 	R6,#65

CONFTIMER0:
	MOV 	TMOD,#1
	MOV 	TH0,#HIGH(-10000)     ;10 ms de contagem
	MOV 	TL0,#LOW(-10000)		
	SETB 	TR0
	SETB 	EA
	SETB 	ET0

LOOP:
	JMP 	$  		;fica à espera da interrupção (10 ms)

LIGA_LARANJA:
	DJNZ 	R6,OUT	 	;decrementa R6 (65 vezes) 65x10ms = 650 ms
	CPL 	P1.0
	MOV 	R6,#65		;volta a carregar R6 com 65
	
OUT:
	MOV 	TH0,#HIGH(-10000)     ;10 ms de contagem
	MOV 	TL0,#LOW(-10000)
	CLR 	TF0
	RETI
	
END