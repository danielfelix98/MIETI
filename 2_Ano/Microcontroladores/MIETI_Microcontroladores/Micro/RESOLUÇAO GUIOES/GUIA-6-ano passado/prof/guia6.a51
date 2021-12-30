#include <89c51rd2.inc>
CSEG AT 00H
	LJMP MAIN
CSEG AT 30H


CHAVE: DS 4
KEY: DB 1,2,3,4

MAIN:
	 SETB P3.3 //BOTÃO ESQUERDO
	 SETB P3.5 //SELECT/BOTAO DIREITO
	 CALL READCHAR
	 CJNE R1,#0,MODO2//se o utilizador desejar definir uma nova pass, 
	 CALL CHECKCODE
	 CALL DISPLAY
	  //esta vai ser feita dentro da funçao readpass recorrendo apenas a um readchar
	 
MODO2: CALL READCHAR
	   MOV R6,A
	   CALL READCHAR
	   MOV R5,A
	   CALL READCHAR
	   MOV R4,A
	   CALL READCHAR 
	   CALL CHECKCODE
	   CALL DISPLAY
 

DETECTKEYS SEGMENT CODE
	RSEG DETECTKEYS
		
DETECT:
		JNB P3.3,INSERE//É acionado salta para carregou esquerdo e verifica se carregou direito tambem

SELECT: 
		MOV R1,#1 //se passar em cima , carregou apenas no direito então retorna 1
		JMP FIM
				  
INSERE: 
		CALL WAIT 
		JNB P3.5,SIMULTANEO 		//Se activar então vindo do esquerdo premido , premiu os dois 
        MOV R1,#2
	    JMP FIM 
		
SIMULTANEO: 
			MOV R1,#0
FIM: RET
		

WAIT SEGMENT CODE	//TIMER 1 , 1 SEGUNDO	
	RSEG WAIT
	
MOV TMOD, #01H //configura temporizador  


DELAY1: MOV R7,#15 ;faz o loop 2x.... /0,5*2 = 1s

LOOP: 
      MOV TH0,#00H ; timer 0 to overflow em 50ms
      MOV TL0,#00H
	  SETB TR0
      JNB TF0, $ //ESPERA PELO TRANSBORDO. PELO SINAL DA FLAG
	  CLR TR0
      CLR TF0
	  DJNZ R7,LOOP
        RET
     
READCHAR SEGMENT CODE
	RSEG READCHAR
		
 
INICIO:
		MOV A,#0H
INICIO1:
		CALL DETECTKEYS
		CJNE R1,#1H,VERIFICA
		MOV R6,A//PARA POR O DISPLAY LIMPO 
		MOV A,#10H//ANTES DE CARREGAR O ALGARISMO INTRODUZIDO PELO USER
		CALL DISPLAY
		CALL WAIT
		MOV A,R6
		CALL DISPLAY
		CALL WAIT
		JMP FIM1
VERIFICA:
		CJNE R1,#0,SOMAR//se na funçao detectkeys o r1 tomar o valor 0 significa que os botoes foram premidos simultaneamente
		MOV A,#11//foram premidos simultaneamente e o acumulador vai tomar o valor 11
		CALL NEW PASS//é chamada a funçao new pass
		CALL READPASS
SOMAR:
	  INC A//contar o numero de pulsos
	  CALL DISPLAY
	  CALL WAIT
	  JMP INICIO1
FIM1:
	RET

NEWPASS SEGMENT CODE
	RSEG NEWPASS

NOVA: 
	MOV DPTR,#CHAVE
	MOVX A,@DPTR
	MOV R2,A  //A password fica em R2
	INC DPTR
	INC R2
	RET


READPASS SEGMENT CODE
    RSEG READPASS
	
LERCHAVE:
		  MOV R3,#4
	      CALL READCHAR //COM UM LOOP DE 4, PARA LER A PASS
	      MOV DPTR,#CHAVE
          MOVX @DPTR,A
		  INC DPTR
	      DJNZ R3,LERCHAVE//CONDIÇAO PARA PERMITIR QUE QUANDO SE ESTA A DEFINIR UMA NOVA PASS FIQUEMOS
	      RET//NO READCHAR 


DISPLAY SEGMENT CODE
		RSEG DISPLAY
		
DISPLAY1:
        MOV P1,#0FFH
		 
ZERO:
    CJNE A,#8H,UM
	MOV P1,#8H
	JMP FIM2
UM:
    CJNE A,#0CBH,DOIS
	MOV P1,#0CBH
	JMP FIM2
DOIS:
    CJNE A,#50H,TRES
	MOV P1,#50H
	JMP FIM2
TRES:
    CJNE A,#42H,QUATRO
	MOV P1,#42H
	JMP FIM2
QUATRO:
    CJNE A,#83H,CINCO
	MOV P1,#83H
	JMP FIM2
CINCO:
    CJNE A,#22H,SEIS
	MOV P1,#22H
	JMP FIM2
SEIS:
    CJNE A,#20H,SETE
	MOV P1,#20H
	JMP FIM2
SETE:
    CJNE A,#4BH,OITO
	MOV P1,#4BH
	JMP FIM2
OITO:
    CJNE A,#00H,NOVE
	MOV P1,#00H
	JMP FIM2
NOVE:
    CJNE A,#02H,ACEITE
	MOV P1,#02H
	JMP FIM2
ACEITE:
    CJNE A,#82H,NAO_ACEITE
	MOV P1,#82H
	JMP FIM2
NAO_ACEITE:
    CJNE A,#09H,FIM
	MOV P1,#09H
	
FIM2:
    RET



CHECKCODE SEGMENT CODE
RSEG CHECKCODE
CHECKPASS:			MOV R3,#4
					MOV DPTR, #KEY		;guarda a nossa chave prédefinida no dptr
				           		       
CHECK:				CLR A				
					MOVC A,@A+DPTR		
					SUBB A,@R0			 ;subtrair os valores o da senha e o dos valores lidos
					CJNE A,#0,ERRO	//Se A diferente de 0 salta para ERRO, se o resultado da subtraçao nao for 0 nao está de acordo com a pass predefinida
					INC  DPTR			
					INC  R2			//incrementa o array
					DJNZ R3, CHECK		//verifica se o ciclo cabou
					JMP  CORRECTO			//salta para certo pois os 4 numeros corresponderam à chave certa

ERRO:				MOV A, #09H			//carrega o simbolo N para o acumulador que o carregará para o display
					CALL DISPLAY
					CALL WAIT
					JMP FIMCHECK

CORRECTO:			MOV A,#82H        // carrega o simbolo Y para o acumulador e depois para o display
					CALL DISPLAY
					CALL WAIT
					JMP FIMCHECK


FIMCHECK:			RET	


FIM3:
					END



	
	
	
	

	


