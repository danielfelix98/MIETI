NAME MAIN
			
	LJMP		START			
	
	CSEG 		AT 30H	
		
START:
		mov a, 75h
		mov b, 76h
		mov dpl, a
		mov dph, b

fim:
end




