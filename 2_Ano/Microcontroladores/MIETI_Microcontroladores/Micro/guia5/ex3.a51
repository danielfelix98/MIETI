CSEG AT 00H
	JMP PRESS
	
PRESS:
	JB P3.3,PRESS//P3.3 É PRESSIONDADO, PB1=1
	MOV P1,#54H
	JMP TIMER
	JB P3.5,PRESS// PB2=1
	JMP TIMER
	
TIMER:	
	MOV TMOD, #02H; set up timer 0 as 8-bit auto-reload interval timer
	LOOP:
	MOV TH0, #83H; put reload value into timer 0 high byte
	SETB TR0; start timer 0
	JNB TF0, $; repeat this line while timer 0 overflow flag is not set
	CLR TF0; timer 0 overflow flag is set by hardware on transition from FFH - the flag must be reset by software
	CLR TR0
	JMP VERIFICA

VERIFICA:
