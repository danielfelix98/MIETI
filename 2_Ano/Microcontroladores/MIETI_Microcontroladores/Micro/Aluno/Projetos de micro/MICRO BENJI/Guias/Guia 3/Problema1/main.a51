	NAME MAIN
#include <89C51rx2.inc>
#define N_LOOPS 20	

	CSEG		AT 	0H			
	LJMP		START			
	
START:

	MOV		R0, #30H
	MOV		R1, #0H
	MOV		R2, #80H ;<-- PARES
	MOV		R3, #90H ;<-- IMPARES
	MOV		R4, #N_LOOPS
	
CICLO:
	
	MOV		A,@R0
	INC     R0
	JB		Acc.0, IMPAR
	Mov     B, R2
	Mov     R1, B
	MOV		@R1,A
	INC		R2
	
	jmp 	loopfim
	
IMPAR:
	
	MOV		B,R3
	MOV		R1,B
	MOV		@R1,A
	INC		R3

loopfim:

	DJNZ	R4,CICLO	
					
END

;Universidade do Minho
;MIECOM
;Microcontroladores
;Jorge Bastos a68456

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