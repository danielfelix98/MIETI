#include <89C51rx2.inc>
NAME MAIN
			
	LJMP		START			
	
	CSEG 		AT 30H	
		
START:
		jmp limpa
		
ba1:		
		setb p1.7
		clr p1.7
ba2:		
		setb p1.6
		clr p1.6
ba3:
		setb p1.5
		clr p1.5
ba4:	
		setb p1.4
		clr p1.4
ba5:
		setb p1.3
		clr p1.3
ba6:
		setb p1.2
		clr p1.2
ba7:
		setb p1.1
		clr p1.1
ba8:
		setb p1.0
		clr p1.0
ba9:
		setb p1.1
		clr p1.1
ba10:
		setb p1.2
		clr p1.2
ba11:
		setb p1.3
		clr p1.3
ba12:	
		setb p1.4
		clr p1.4
ba13:
		setb p1.5
		clr p1.5
ba14:		
		setb p1.6
		clr p1.6
ba15:		
		setb p1.7
		clr p1.7
ba16:		
		setb p1.7
		clr p1.7

		
		
limpa:
		clr p1.0
		clr p1.1
		clr p1.2
		clr p1.3
		clr p1.4
		clr p1.5
		clr p1.6
		clr p1.7
		
		jmp ba1

end




