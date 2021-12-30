NAME	H2A
	
	PUBLIC	INICIOH2A
	
	H2ACODE	SEGMENT	CODE			; Declara segmento
	RSEG 	H2ACODE					; Seleciona o segmento
		
	; Rotina que converte dígito hexadecimal armazenado
	; no endereço de memória apontado por R0 para ASCII
INICIOH2A:
		; BA1: Bloco de atribuição 1
		;MOV		A, @R0
		CLR C				
		SUBB 	A,#10 		
		
		; BD1: Bloco de decisão 1					
		JC BA3_NAO			
		; Carry é 0, logo é letra porque A>=0
		; BA2_SIM: Bloco de atribuiçao 2					
		ADD A,#'A'			
		MOV B,A				
		JMP FIMH2A 			
		
		; BA3_NAO: Bloco de atribuição 3					
BA3_NAO:
		ADD A,#10			
		ADD A,#'0'			
		MOV B,A				
FIMH2A:
		RET					
		
END
	
; Universidade do Minho
; MIECOM
; Microcontroladores
; David Faria a48238

; Qual o objectivo de desenvolver este programa em dois módulos?
; Diminui o tempo de execução. O programa fica mais leve em 
; comparação se fosse feito em apenas um módulo.

; As directivas para ligação do programa utilizam-se quando o programa 
; a desenvolver se encontra distribuído por vários módulos.
; Como os módulos necessitam de partilhar informação torna-se necessário 
; identificar a origem da informação (quando externa) 
; ou qual a informação que vai ser partilhada.

; -> PUBLIC: Lista os símbolos que podem ser usados por outros módulos; 
; 			exporta um símbolo, neste caso módulo H2A.

; -> EXTRN: Lista os símbolos referidos no módulo corrente e definidos 
; 			noutro módulo; usa um símbolo, neste caso módulo MAIN.

; -> SEGMENT: Define um segmento.

; -> RSEG: Selecção de um segmento.

; -> NAME: Especifica o nome do módulo objecto gerado pelo programa.

; Qual o endereço na memória de código das etiquetas:
; BA3_NAO: C:0x000F
; FIM_H2A: C:0x0015

; Os ficheiros '.lst' contem os codigos maquina e assembly e os respectivos endereços no código.

; O objectivo de incluir a linha: #include<89C51Rx2.inc> é: incluir uma biblioteca, neste caso, a do nosso microcontrolador.

; O ficheiro com extensão '.M51' contem os endereços das etiquetas, endereços de outras instruções.