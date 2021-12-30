
	
	org 0H
LJMP carrega

org 000BH
jmp isr_t0


org 33H
carrega:
	mov p0,#0ffh
	mov r3,#24
	mov r4,#2
	clr p3.3
	clr p1.0
	
config_t0:
	mov tmod,#01h
	mov th0,#HIGH(-15000)
	MOV TL0,#LOW(-15000)
	mov ie, #82h
	setb tr0
	
testa:
	jb p3.3,vermelho
	jmp testa
	
vermelho:
	clr tr0
	mov th0,#HIGH(-15000)
	MOV TL0,#LOW(-15000)
	mov r3,#115
	cpl p1.0
	cpl p1.1
	setb tr0
	
vermelho_2:
	jnb p3.3, carrega
	jmp vermelho_2


isr_t0:
	jnb p3.3,amarelo_isr

vermelho_isr:
	djnz r3, sair_isr
	mov r3,#115
	djnz r4,sair_isr
	cpl p1.0
	cpl p3.3
	jmp sair_isr

amarelo_isr:
	djnz r3,sair_isr
	cpl p1.1
	mov r3,#24
	
sair_isr:
	reti
	
	
END
