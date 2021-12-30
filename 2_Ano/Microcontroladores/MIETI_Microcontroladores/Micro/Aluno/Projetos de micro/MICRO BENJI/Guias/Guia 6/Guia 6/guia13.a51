	#include<89c51rx2.inc>
	
	CSEG		AT 	0H	
	lcall ConfTmr0
	lcall RunTMR0
	CPL p1.0
				

ConfTmr0: 
	mov TMOD, #1h   				// Iniciar o timer.
	mov TH0, #HIGH(-500)			// 
	mov TL0, #LOW(-500)   			// 
	ret 
 
RunTMR0: 
	setb TR0 
	jnb TF0, $ 
	clr TR0 
	clr TF0 
	ret 

END