#include <89C51Rx2.inc>

TXPTR EQU 040h 

	CSEG AT 00H
		JMP INICIO

	CSEG AT 070H

INICIO:
		
		MOV R0,#00H ; R0 CONTEM O TERMINO DOS BITS A ENVIAR (POSIÇÃO)    
		MOV R1,#TXPTR	  ; MOVE 40H PARA R1
		
		MOV	P1,#0FFH	 		 
		MOV P0,#0FFH

;---------------------------------------------------------------------------------
;CONFIGURAÇÃO DA PORTA SERIE

CONFIG:
	MOV TH2, #0FFh 
	MOV TL2, #0D9h 
	MOV RCAP2L, #0D9h
	MOV RCAP2H, #0FFh 
	MOV T2CON, #034h ;ja activa o timer2
	MOV SCON, #50h ;8-bit, 1 stop bit, REN enable

;---------------------------------------------------------------------------------
;LER TECLA PREMIDA

LER_TECLA:	
			MOV A,P0           
			MOV B,A		       
			XRL A,#11111111b   ; VERIFICAR SE FOI PREMIDA UMA TECLA			
			JZ LER_TECLA	   ; SE NAO FOI VOLTAMOS A LER
			JMP DESC_TECLA	   ; SE FOR ZERO PROCEDEMOS Á SUA DESCODIFICAÇÃO

;--------------------------------------------------------------------------------			
;DESCODIFICAÇÃO DAS TECLAS PREMIDAS

DESC_TECLA:	
							 
			MOV A,B
			XRL A,#0F5H   	 ; VERIFICAR SE É A TECLA ZERO (11110101)	
			MOV R5,#0
			JZ AINDA_TECLA
			
			MOV A,B
			XRL A,#0BBH	
			MOV R5,#1
			JZ AINDA_TECLA
			    
			MOV A,B
			XRL A,#0BDH	
			MOV R5,#2
			JZ AINDA_TECLA

			MOV A,B
			XRL A,#0BEH	
			MOV R5,#3
			JZ AINDA_TECLA 

			MOV A,B
			XRL A,#0DBH	
			MOV R5,#4
			JZ AINDA_TECLA

			MOV A,B
			XRL A,#0DDH	
			MOV R5,#5
			JZ AINDA_TECLA

			MOV A,B
			XRL A,#0DEH	
			MOV R5,#6
			JZ AINDA_TECLA 

			MOV A,B
			XRL A,#0EBH	
			MOV R5,#7
			JZ AINDA_TECLA 

			MOV A,B
			XRL A,#0EDH	
			MOV R5,#8
			JZ AINDA_TECLA 

			MOV A,B
			XRL A,#0EEH	 
			MOV R5,#9
			JZ AINDA_TECLA  

			MOV A,B
			XRL A,#0F3H	 
			JZ ASTERISTICO	

			MOV A,B
			XRL A,#0F6H	 
			JZ CARDINAL	 
;--------------------------------------------------------------------------
ASTERISTICO:
		JMP LIMPAR

CARDINAL:
		JMP CONFIRMAR

;-------------------------------------------------------------------------------
 ;VERIFICA SE A TECLA AINDA ESTÁ A SER PREMIDA

AINDA_TECLA:			
				     
		LOOP:	MOV A,#0FFh	 	
				XRL A,P0			; VERIFICAR SE AINDA ESTAMOS A PREMIR A TECLA
				JNZ LIGA_DISPLAY  	; SE NAO FOR 0, SIGNIFICA QUE AINDA ESTAMOS A PREMIR ENTAO LIGAMOS DISPLAY
				MOV P1,#0FFh		; SE FOR 0 , JA NAO ESTAMOS A PREMIR
				JZ MOVER_MEM		; COLOCAR EM MEMORIA A TECLA
;--------------------------------------------------------------------------------
;TECLAS ESPECIAIS (COMFIRMAR E LIMPAR)

; TECLA LIMPAR (*) -> LIMPAR TODAS AS TECLAS INTRODUZIDAS E GUARDADAS NA MEMORIA
LIMPAR:
		MOV A, 00H
		MOV @R1, A
		INC R1
		DJNZ R0, LIMPAR
		JMP INICIO


; TECLA CONFIRMAR (#) -> ENVIO DE TODAS AS TECLAS INTRODUZIDAS ANTERIORMENTE
CONFIRMAR: 
		MOV R1,#TXPTR	  
		JMP ENVIAR_SERIE
		
		
;-------------------------------------------------------------------------------
;LIGA O NUMERO CORRESPONDENTE NO DISPLAY
LIGA_DISPLAY:
		MOV P1, #0FFH
		MOV DPTR, #NUM
		MOV A, R5
		MOVC A, @A+DPTR
		MOV P1,A
		JMP LOOP	 
		
;---------------------------------------------------------------------------------
;COLOCA EM MEMORIA AS TECLA PREMIDAS

MOVER_MEM:					   
		    MOV A,R5	   		
			MOV @R1,A		
			INC R1
			INC R0
			JMP NOVA_TECLA
;------------------------------------------------------------------------------------
;ENVIAR POR PORTA SERIE OS DIGITOS INSERIDOS 

ENVIAR_SERIE: 		
				MOV A,@R1	  			
				INC R1					
				MOV SBUF,A	  		    
				JNB TI,$
				CLR TI						
				DJNZ R0, ENVIAR_SERIE	
				JMP FIM     
				
;-------------------------------------------------------------------------------------------
;LE TECLA SEGUINTE
NOVA_TECLA:
			
			MOV P1,#0FFH
			MOV P0,#0FFH		 
			JMP LER_TECLA		 

;-------------------------------------------------------------------------------------------
ORG 100H
NUM: DB  0CH, 0CFH, 54H, 46H, 87H, 26H, 24H, 4FH, 04H, 06H



FIM:
	END