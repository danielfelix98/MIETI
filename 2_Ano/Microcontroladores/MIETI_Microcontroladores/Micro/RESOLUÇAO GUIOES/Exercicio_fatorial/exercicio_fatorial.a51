cseg at 0h
jmp main
cseg at 30h
//programa principal
main:
	//receber o nº no acumulador
	mov r1,#5
	mov a,r1
	//verificar se o nº é válido [1,6[ 
	call verifica_num
	//se C=0 salta para nao_valido
	jnc nao_valido
	//chama a subrotina fatorial
	call fatorial
	mov r0,a
nao_valido:
	jmp $
		
//subrotina verificar numero se é valido	
verifica_num:
	
	//verifica a<6
	cjne a,#6,check1
check1:
	//se o C=1 salta para check2, senão vai para o fim da subrotina
	jc check2
	jmp fim_verifica_num
check2:
	//verifica a>=1
	cjne a,#1,not1
valid:
	setb C
	jmp fim_verifica_num
not1:
	//Se C=0 salta para
	jnc valid
	clr c
fim_verifica_num:
	ret
	
//subrotina fatorial
fatorial:
	//guardar na stack o valor do acumulador(A)
	PUSH ACC
	//verifica se A=1, senão salta para not_one
	CJNE A,#1,not_one
fim_fatorial:
	//restaura o valor do acumulador(A)
	pop acc
	ret
not_one:
	//A=A-1
	DEC A
	//chama a função fatorial(recursividade)
	call fatorial
	//B=A
	mov b,a
	//restaura o valor do acumulador(A)
	pop acc
	//A=A*B
	mul ab
	ret

end