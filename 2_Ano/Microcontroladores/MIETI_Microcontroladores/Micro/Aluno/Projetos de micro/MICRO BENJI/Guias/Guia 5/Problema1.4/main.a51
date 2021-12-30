NAME MAIN
			
	LJMP		START			
	
	CSEG 		AT 30H	
		
START:
		mov r0,#0
		mov a, 60h
		
		rotina0:
		jnb acc.0, rotina1
		inc r0
		
		rotina1:
		jnb acc.1, rotina2
		inc r0
		
		rotina2:
		jnb acc.2, rotina3
		inc r0
		
		rotina3:
		jnb acc.3, rotina4
		inc r0
		
		rotina4:
		jnb acc.4, rotina5
		inc r0
		
		rotina5:
		jnb acc.5, rotina6
		inc r0
		
		rotina6:
		jnb acc.6, rotina7
		inc r0
		
		rotina7:
		jnb acc.7, fim
		inc r0
		
		jmp fim
		

fim:
end




