	NAME MAIN
#include <89C51rx2.inc>

	EXTRN		CODE	(INICIOH2A)
	N_LOOPS		EQU		5		
	
	CSEG		AT 	0H			
	LJMP		START			

	CSEG 		AT 30H				
START:
	MOV 	20H,#05H
	MOV 	21H,#08H
	MOV 	22H,#0AH
	MOV 	23H,#0EH
	MOV 	24H,#07H
	
	MOV 	R2,#N_LOOPS
	MOV 	R0,#20H
	MOV 	R1,#8H
	Mov		DPTR,#MESSAGE
	MOV		R2,#N_LOOPS
	
LOOP:
	CLR 	A
	MOVC	A,@A+DPTR
	MOV 	A,@R0
	PUSH	ACC				
	LCALL	INICIOH2A	
	MOV		A,B				
	MOVX	@R1,A			
	POP		ACC								
	INC		DPTR
	INC     R0
	INC     R1
	DJNZ	R2,LOOP			
	SJMP	$	

;declarar que estao a partir desse endereco
	CSEG AT 1000H

MESSAGE:
		DB	10,7,12,3,15,10,15,14,8,7,0

END



;Qual o objectivo de desenvolver este programa em dois módulos?
;Diminui o tempo de execução; o programa fica mais leve em comparação se fosse feito apenas num módulo.

;As directivas para ligação do programa utilizam-se quando o programa a desenvolver se encontra distribuído por vários módulos.
;Como os módulos necessitam de partilhar informação torna-se necessário identificar a origem da informação (quando externa) 
;ou qual a informação que vai ser partilhada.

;PUBLIC: Lista os símbolos que podem ser usados por outros módulos; exporta um símbolo, neste caso módulo H2A

;EXTRN: Lista os símbolos referidos no módulo corrente e definidos noutro módulo; usa um símbolo, neste caso módulo MAIN

;SEGMENT: Define um segmento.

;RSEG: Selecção de um segmento.

;NAME:Especifica o nome do módulo objecto gerado pelo programa.

;Qual o endereço na memória de código das etiquetas:
;BA3_NAO: C:0x000c
;FIM_H2A: C:0x00012

;Os ficheiros '.lst' contem os codigos maquina e assembly e os respectivos endereços no código.

;O objectivo de incluir a linha: #include<89C51Rx2.inc> é: incluir a biblioteca.

;O ficheiro com extensão '.M51' contem os endereços das etiquetas, enderecos de outras intrucoes...