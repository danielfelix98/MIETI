cseg at 0h
	ljmp main


cseg at 33h
	
	main:
	mov TMOD,#2H
	mov TH0,#10H
	mov IE,#82h
	subb a,#15
	jmp $
cseg at 0bh
	cpl P1.1
	reti

end
