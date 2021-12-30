;$NOMOD51
#include <89C51IC2.inc>

	CSEG AT 0H

        Main:  MOV DPTR,#0A000H
               MOV R0,#40H;MAIOR/igual
	           MOV R1,#0A0H;MENOR
	           MOV R3,#0;CONTADOR
	  
	  Inicio:  MOVX A,@DPTR
               INC DPTR
               INC R3
               CJNE A,#128,MaiorMenor
               MOV @R0,A
               INC R1
               JMP CONTADOR
      
	  Contador:CJNE R3,#40,Inicio
               JMP Fim
	
	MaiorMenor:
               JC MENOR
               JMP MAIOR  
        
		MAIOR: INC R0
		       MOV @R0,A
			   CLR C
               JMP Contador
	    
		MENOR: INC R1 
		       MOV @R1,A
			   CLR C
               JMP Contador
	  FIM:
	  JMP $
END