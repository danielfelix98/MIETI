#include <89C51rx2.inc>
NAME MAIN
			
	LJMP		START			
	
	CSEG 		AT 30H	
		
START:
		jmp limpa
		
ba1:		
		setb p1.7 & p1.3																																																																																												
		clr p1.7 & p1.3
ba2:		
		setb p1.6 & p1.2
		clr p1.6 & p1.2
ba3:
		setb p1.5 & p1.1
		clr p1.5 & p1.1
ba4:	
		setb p1.4 & p1.0
		clr p1.4 & p1.0
ba5:
		setb p1.3 & p1.7
		clr p1.3 & p1.7
ba6:
		setb p1.2 & p1.6
		clr p1.2 & p1.6
ba7:
		setb p1.1 & p1.5
		clr p1.1 & p1.5
ba8:
		setb p1.0 & p1.4
		clr p1.0 & p1.4
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




