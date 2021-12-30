include<89c51ic2.inc>

CSEG AT 00h				
	LJMP MAIN

	CSEG AT	2BH	
JMP ISRT2		;Vector utilizado para a interrupção desejada
					;volta para o sitio de onde saiu.
	
	CSEG AT	30H

MAIN:
	MOV		R3,#0
	MOV		DPTR, #DISPLAY
	
	MOV 	T2CON,#04H		;ativar o timer 2 da forma que queremos. modo auto reload
	MOV 	TH2,#HIGH (-1000)		;estao a decrementar
	MOV 	TL2,#LOW (-1000)
	MOV 	RCAP2H,#HIGH (-1000)	;quando o tf2 fica a 1 o rcap passa outra vez os valores para o th2.
	MOV		RCAP2L,#LOW (-1000)
	SETB 	EA						;ativar as interrupcoes todas
	SETB	ET2						;ativa a interrupçao especifica do timer 2.
	
	
LOOP:
	CJNE	R3,#250,LOOP			;quando r3 chegar a 250 sai daqui. a cada microsegundo salta 
	
ESCREVER:
	MOV		R3,#0					;como nunca mais volta a main, temos que garantir que fica a zero.
	CLR		A
	MOVC	A,@A+DPTR
	MOV		P1,A
	INC		DPTR
	CJNE	A,#07h,LOOP
	MOV 	DPTR,#DISPLAY
	JMP		LOOP
	ISRT2:
    CPL	 P2.0		
	CLR 	TF2			;Timer recomeça, quando o timer faz overflow o tf2 fica ativo e enquanto ficar assim o timer nao funciona
	INC		R3						;conta as interrupçoes
	RETI				

DISPLAY:
	DB		0CH,0CFH,54H,46H,87H,26H,24H,4FH,04H,07H
	
END