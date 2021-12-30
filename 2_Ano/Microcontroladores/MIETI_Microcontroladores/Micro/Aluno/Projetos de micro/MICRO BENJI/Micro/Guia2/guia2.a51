CSEG 	AT 	0H
	
	
repete: 
	MOV A,P1
	MOV R4,A
	CJNE R4,#3BH,repete
	
JMP $
	
END