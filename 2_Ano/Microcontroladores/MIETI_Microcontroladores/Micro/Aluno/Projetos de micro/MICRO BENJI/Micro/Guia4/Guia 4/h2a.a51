	NAME	H2A
	
	PUBLIC	INICIOH2A
	
	H2ACODE	SEGMENT	CODE	 ;Declara segmento
	RSEG 	H2ACODE			 ;Seleciona o segmento
	; Rotina que converte dígito hexadecimal armazenado
	;no endereço de memória apontado por R0 para ASCII
		
	
INICIOH2A:
	;BA1: Bloco de atribuição 1
	MOV A,@R0
	CLR C				
	SUBB A,#10
		
	;BD1: Bloco de decisão 1					
	JC BA3_NAO			
	;Carry é 0, logo é letra porque A>=0
	;BA2_SIM: Bloco de atribuiçao 2					
	ADD A,#'A'			
	MOV B,A				
	JMP FIMH2A 			
		
	;BA3_NAO: Bloco de atribuição 3					
BA3_NAO:
	ADD A,#10			
	ADD A,#'0'			
	MOV B,A	
	
FIMH2A:

	RET					
		
END