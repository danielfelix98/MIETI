NAME MAIN

		;EXTRN 	CODE 	(ENVIAR_RS232, RECEBER_RS232, CONFIG_RS232)

		;CSEG 	AT	0H
		;JMP		MAIN

		;CSEG 	AT 	30H
MAIN:
		;CALL	CONFIG_RS232	; configura a porta de serie(flags, bourate, etc)
		MOV 	A,#35
		MOV		R0,A
		INC		R0
		MOV		R1,#35h
		INC		R1
		MOV		A,R0
		MOV		B,R1
		;MOV	R0,A
		MOV 	A,@R0
		MOV 	B,@R1
		;MOV	R1,A
		JMP		MAIN

END