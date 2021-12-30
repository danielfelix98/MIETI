		CSEG 	AT 	0H
		JMP 	MAIN
		CSEG  	AT 	30H
MAIN:
		MOV 	DPTR,#DADOS			; Move para DPTR o endereço do primeiro número em DADOS
TESTE:	
		CJNE	R0,#12H,PERCORRER	; Se já chegou ao fim da sequência, parar de percorrer
		MOV		A,R2				; Mover para A o menor número encontrado, que se encontra em R2
		JMP 	$					
PERCORRER:
		MOV		A,R0
		MOVC 	A,@A+DPTR			; Move para A o número atual
		JNB		ACC.0,PAR			; Verifica se o número é par. Último bit do acumulador tem de ser 0
		INC		R0					; Se não for par, passa para o próximo número
		JMP		TESTE				; Verifica o próximo número
PAR:
		MOV		R1,A				
		CJNE	R1,#0,LOOP			; 0 não é par, por isso, não pode ser mínimo
		JMP		TESTE
LOOP:								
		DEC		A
		CJNE	A,#0,LOOP2			
		JMP		PAR2				; Se o número atual da sequência chegar primeiro a 0, é o novo mínimo
LOOP2:
		DEC		R3					; Se o mínimo atual chegar primeiro a 0, continua a ser o menor até ao momento
		CJNE	R3,#0,LOOP			; Se já chegou a 0, podemos verificar o próximo número
		MOV		A,R2				
		MOV		R3,A				; Transfere novamente para R3 o mínimo que está em R2
		INC		R0					; Verifica o próximo número da sequência
		JMP		TESTE				
PAR2:
		MOV		A,R1				
		MOV		R2,A				; Transferir o novo mínimo para R2 e R3. R2 é uma cópia de segurança, visto que R3 vai ser alterado
		MOV		R3,A
		INC		R0					; Verifica o próximo número da sequência
		JMP		TESTE
		CSEG 	AT	440H			; Inicia o código que se segue no endereço 440H
DADOS:
		DB 10,9,8,2,4,6,7,8,9,1,14,19,20,22,14,15,28,19,0
END