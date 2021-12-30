NAME MAIN
			
	LJMP		START			
	
	CSEG 		AT 30H	
		
START:
		mov a, 60h
		swap a
		mov 60h,a 
	 
	 
END



