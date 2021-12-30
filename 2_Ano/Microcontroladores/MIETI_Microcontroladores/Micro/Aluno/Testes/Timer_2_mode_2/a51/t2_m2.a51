#define MSB_reload_value 0x36 /* msb reload value exemple */
#define LSB_reload_value 0x36 /* lsb reload value exemple */


$INCLUDE   (reg_c51.INC)

org 000h
ljmp begin

org 02Bh
ljmp it_timer2
;/**
; * FUNCTION_PURPOSE: This file set up timer 2 in mode 1 (clock-out mode and 
; * negative transition detector).
; * The 16-bits register consist of all 8 bits of TH2 and all 8 bits of TL2.
; * TF2 does not generate interrupt.   
; * A negative transition on P1.1(T2EX) generate an interrupt.
; * FUNCTION_INPUTS: void
; * FUNCTION_OUTPUTS: P1.0(T2) as clock output : Fout = Fperiph / (2*(65536-RCAP2)).
; */
org 0100h

begin:
	ANL T2MOD,#0FEh;			      /* T2OE=1;DCEN=0; */
	ORL T2MOD,#02h;

   CLR EXF2;                   /* reset flag */
   CLR TCLK;
   CLR RCLK;                   /* disable baud rate generator */

   SETB EXEN2;                 /* enable events on T2EX */ 
   MOV TH2,MSB_reload_value;	 /* Init msb_value */
   MOV TL2,LSB_reload_value;	 /* Init lsb_value */
   MOV RCAP2H,MSB_reload_value;/* reload msb_value */
   MOV RCAP2L,LSB_reload_value;/* reload lsb_value */
   CLR C_T2;                   /* timer mode */
   CLR CP_RL2;                 /* reload mode */
   SETB EA;                    /* interupt enable */
   SETB ET2;                   /* enable timer2 interrupt */
   SETB TR2;                   /* timer2 run */

	JMP $;				          /* endless  */


;/**
; * FUNCTION_PURPOSE: timer2 interrupt
; * FUNCTION_INPUTS: void
; * FUNCTION_OUTPUTS: P1.2 toggle period = 2 *  P1.1(T2EX) period 
; */
it_timer2:
	CLR TF2;						/* reset  interrupt flag */
	CPL P1.2;					/* P1.2 toggle when interrupt. */
   RETI

end
