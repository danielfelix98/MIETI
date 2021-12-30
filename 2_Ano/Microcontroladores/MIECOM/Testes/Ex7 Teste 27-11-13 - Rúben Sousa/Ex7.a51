	CSEG 	AT 	0H
	
	SJMP	MAIN
	CSEG	AT  30H
	
MAIN:
	MOV		R4,#N		; Move para R4 a quantidade de números a serem trocados
	MOV		R5,#40h     ; Endereço destino do 1º número, 0x40
	MOV		R7,#10h     ; R7 contém os 8bits mais significativos do endereço de 16bits onde se encontram os números
	MOV		R6,#00h		; R6 contém os 8bits menos significativos do endereço de 16bits onde se encontram os números	
	CALL    ROTINA	
	JMP		$

ROTINA:
	MOV		A,R5
	MOV		R0,A		; R0 apontará para a primeira posição onde será colocado o número
	INC		R5
	MOV		A,R5
	MOV		R1,A		; R1 apontará para a posição seguinte
	MOV		DPL,R6		; Move os 8bits menos significativos para DPL
	MOV		DPH,R7		; Move os 8bits mais significativos para DPH
	MOV		A,B			
	MOVC	A,@A+DPTR	; Guarda em A o número que está em NUMS
	DEC		R4			; Decrementa a quantidade de números que falta ler
	MOV		@R1,A		; Faz a troca do número
	INC		B			; Lê o número seguinte
	MOV		A,B
	MOVC	A,@A+DPTR	; Guarda em A o número seguinte
	MOV		@R0,A		; Faz novamente a troca
	SUBB 	R4,#2
	INC		B			
	INC		R5			
	CJNE	R4,#0,ROTINA	
	RET

	CSEG	AT 1000H
	
NUMS:
	DB 		80h,05h,6h,10h,20h,30h,5Fh,30h
	N		EQU $-NUMS
	
END