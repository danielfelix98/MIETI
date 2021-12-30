;#include <89C51Rx2.inc>
;	INICIO DE PROGRAMA
		NAME MAIN

		EXTRN 	CODE 	(ENVIAR_RS232, RECEBER_RS232, CONFIG_RS232)

		CSEG 	AT	0H
		JMP		MAIN

		CSEG 	AT 	30H
MAIN:
		CALL	CONFIG_RS232	; configura a porta de serie(flags, bourate, etc)
		MOV		P1,#4Fh			; envia 4Fh('7') para a porta de serie(P1)
		MOV 	R4,#0			; inicializa o contador a 0
		MOV 	DPTR,#MENSAGEM	; DPTR toma o valor do apontador de MENSAGEM, ou seja o valor da primeira posição da string
MAINLOOP:
        MOV		A,R4			; 'A' toma o valor de R4
		MOVC	A,@A+DPTR		; Mover para 'A' o byte relativo á posição = A+DPTR(será sempre o valor da primeira posição da string
		CALL	ENVIAR_RS232	; Envia o byte para a porta de serie 
		INC		R4				; incrementa 1 a R4 (R4 = R4 +1
		CJNE	R4,#MSGLEN,MAINLOOP		;compara R4 e #MSGLEN(tamanho da mensagem) e salta para MAINLOOP enquanto for diferente
MAINLOOP2:
		CALL	RECEBER_RS232	; Recebe os bytes da porta de serie 
		CALL	ENVIAR_RS232	; Envia o byte para a porta de serie
		JMP		MAINLOOP2		; Salta sempre para MAINLOOPS2 (ciclo infinito)

MENSAGEM:
		DB	"07"		; A mensagem a enviar será "07"
MSGLEN  EQU $-MENSAGEM	; MSGLEN = $(posição de memoria de fim de mensagem) - MENSAGEM (posição de memoria da primeira letra da mensagem)
END		;FIM DE PROGRAMA