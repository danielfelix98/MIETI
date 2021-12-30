	NAME MAIN
#include <89C51rx2.inc>
	
	N_LOOPS		EQU		6
		
	CSEG		AT 	0H			
	LJMP		MAIN			
	
MAIN:

	
	MOV		R3, #0A0H 			;Serve para guardar os nºos inferiores a 128 (decimal)
	MOV		R4, #40H 			;Serve para guardar os nºos iguais e superiores a 128 (decimal)
	MOV		R5, #N_LOOPS

START:
	
	MOV		DPTR, #0A000H
	
	

CICLO:
	
	MOVX	A, @DPTR
	CLR 	C
	SUBB	A, #128
	ADD		A, #128
	JNC		MAIOR_OU_IGUAL
	MOV		B, R3
	MOV		R0, B
	MOV		@R0, A
	INC		R3
	JMP		INCREMENTAR_DPTR
	
MAIOR_OU_IGUAL:
	
	MOV		B, R4
	MOV		R0, B
	MOV		@R0, A
	INC		R4

INCREMENTAR_DPTR:

	INC		DPTR

LOOP_FIM:

	DJNZ	R5,CICLO
	
	END


;INC DPL DATA POINT PARA O LOW
;INC DPH DATA POINT PARA O HIGH

;Qual o objectivo de desenvolver este programa em dois módulos?
;Diminui o tempo de execução; o programa fica mais leve em comparação se fosse feito apenas num módulo.

;As directivas para ligação do programa utilizam-se quando o programa a desenvolver se encontra distribuído por vários módulos.
;Como os módulos necessitam de partilhar informação torna-se necessário identificar a origem da informação (quando externa) 
;ou qual a informação que vai ser partilhada.

;PUBLIC:Lista os símbolos que podem ser usados por outros módulos; exporta um símbolo, neste caso módulo H2A
;EXTRN:Lista os símbolos referidos no módulo corrente e definidos noutro módulo; usa um símbolo, neste caso módulo MAIN
;SEGMENT:Define um segmento.
;RSEG:Selecção de um segmento.
;NAME:Especifica o nomedo módulo objecto gerado pelo programa.

;Qual o endereço na memória de código das etiquetas:
;BA3_NAO: C:0x080C
;FIM_H2A: C:0x0812

;Os ficheiros '.lst' contem os codigos maquina e assembly e os respectivos endereços no código.

;O objectivo de incluir a linha: #include<89C51Rx2.inc> é:

;O ficheiro com extensão '.M51' contem os endereços das etiquetas.