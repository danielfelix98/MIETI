; Filipe Rodrigues nº 68455
; Eduardo Silva nº 70216

;	INICIO DE PROGRAMA
		
#include <89C51IC2.inc>		
		NAME MAIN
		EXTRN 	CODE 	(ENVIAR_RS232, RECEBER_RS232, CONFIG_RS232)
		
		CSEG 	AT	0H
		JMP		MAIN
		CSEG 	AT 	30H
		
		C1		EQU		140		; variável "C1" toma o valor de ajuste para o ciclo de atraso de menor peso
		C2		EQU		138		; variável "C2" toma o valor de ajuste para o ciclo de atraso de peso intermédio
		C3		EQU		12		; variável "C3" toma o valor de ajuste para o ciclo de atraso de maior peso

; ROTINA PARA CONFIGURAR A PORTA DE SERIE, E, INICIALIZAR AS VARIÁVEIS  (posição da função pode ser alterada)		
MAIN:
		CALL	CONFIG_RS232	; configura a porta de serie(flags, bourate, etc)
		MOV 	DPTR,#MENSAGEM	; DPTR toma o valor do apontador de MENSAGEM, ou seja o valor da primeira posição da string
		MOV		R0,#0h			; variável de controlo dos limites superior e inferiores da sequencia
		MOV		R1,#0h  		; contador que envia o valor que aparece no display para o terminal
		
		MOV		R5,#C1			; ajuste de "ATRASO_2"
		MOV		R6,#C2			; ajuste de "ATRASO_1"
		MOV		R7,#C3			; ajuste de "ATRASO_0"
		JMP		ESCREVER		; saltar para ESCREVER(envia para o display e escreve no terminal
		
; ROTINA PARA ESCREVER NO DISPLAY O VALOR APONTADO POR "R0" EM DPTR, E ENVIAR PARA O TERMINAL O VALOR DE "R1"(=R0) (posição da função pode ser alterada)		
ESCREVER:
		MOV		A,R0			; A = R0
		MOVC	A,@A+DPTR		; A = @A(posição onde se quer ir buscar o numero) + DPTR(1ª posição do array onde se encontram os valores a ser enviados para o micro
		MOV		P1,A			; enviar para o display, o valor pretendido do array
		
		MOV		A,R1			; A = R1 , valor a aparecer no terminal
		CALL	ENVIAR_RS232	; enviar para o terminal valor de R1 
		;CALL	ATRASO_0

PRESSIONAR:
		JNB		P3.5,PRESSIONAR1		; salta para PRESSIONAR1
		JNB		P3.3,PRESSIONAR2		; salta para PRESSIONAR2
		JMP		PRESSIONAR
		
; CICLO DE 2 ROTINAS, PRESSIONAR1(se pressionar o botão de somar) E PRESSIONAR2	(se pressioanr o botão de subtrair)
PRESSIONAR1:
		JNB		P3.5,$			
		JB		P3.5,INCREMENTAR		
		;JMP		PRESSIONAR2		; se NÃO pressionou saltar para PRESIONAR2
		
PRESSIONAR2:;(a sua possição tem que ser logo a seguir a PRESSIONAR1)
		JNB		P3.3,$			
		JB		P3.5,DECREMENTAR		; se NÃO pressionou saltar para PRESIONAR1
		
; SUB-ROTINA PARA SOMAR 1 A "R0" E "R1" (posição da função pode ser alterada)
INCREMENTAR:
		INC		R0							; somar "1" a R0
		INC		R1							; somar "1" a R1
			; verifica se passou o nº 9 (ciclo "if-else")
		MOV		A,R0			
		CJNE	A,#0Ah,ESCREVER				; salta para "ESCREVER", se A(=R0) for diferente de "Ah"(=10)
			; proximo nº toma valor de "0"
		MOV		R0,#0h						; R0 = "0h"
		MOV		R1,#0h						; R1 = "0h"
		JMP		ESCREVER					; senão salta para "ESCREVER"

; SUB-ROTINA PARA SUBTRAIR 1 A "R0" E "R1" (posição da função pode ser alterada)
DECREMENTAR:
		DEC		R0							; subtraí "1" a R0
		DEC		R1							; subtraí "1" a R0
			; verifica se passou(-) o nº 0 (ciclo "if-else")
		MOV		A,R0
		CJNE	A,#0FFh,ESCREVER			; salta para "ESCREVER", se A(=R0) for diferente de "FFh"(="-1"="16(decimal)")
			; proximo nº toma valor de "9"
		MOV		R0,#9h						; R0 = "9h"
		MOV		R1,#9h						; R1 = "9h"
		JMP		ESCREVER					; senão salta para "ESCREVER"

; ROTINA PARA OBTER UM ATRASO DE 0.7s (posição da função pode ser alterada)
ATRASO_0:
ATRASO_1:
ATRASO_2:
		NOP	          			; queima 1 ciclo por cada ciclo
		DJNZ	R5,ATRASO_2		; decrementa "1" a R5 e salta para "ATRASO_2" enquanto for diferente de "0". A partir do 2º ciclo R5 = 0-1 = 255, ou o ciclo ocorrer 255 vezes
		MOV		R5,#C1			; ajuste de "ATRASO_2"

		NOP
		DJNZ	R6,ATRASO_1		; decrementa "1" a R5 e salta para "ATRASO_1" enquanto for diferente de "0". A partir do 2º ciclo R5 = 0-1 = 255, ou o ciclo ocorrer 255 vezes
		MOV		R6,#C2			; ajuste de "ATRASO_1"

		NOP
		DJNZ	R7,ATRASO_0		; decrementa "1" a R5 e salta para "ATRASO_0" enquanto for diferente de "0". A partir do 2º ciclo R5 = 0-1 = 255, ou o ciclo ocorrer 255 vezes
		MOV		R7,#C3			; ajuste de "ATRASO_0"
		
		RET						;O PROGRAMA CONTINUA ONDE FOI CHAMADA A FUNÇÃO "ATRASO_0"

; LOCAL ONDE "DPTR" É INICIALIZADO (posição da função pode ser alterada)
MENSAGEM:
		DB	0Ch,0CFh,54h,46h,87h,26h,24h,4Fh,04h,07h		; numeros de "0" a "9" em codigo reconhecivel para o display
		
END		;FIM DE PROGRAMA