#include <p16f873a.inc> 

CBLOCK 0X20
	decremento0
	decremento1
	decremento2
	decremento3

	decremento4
	decremento5
	decremento6
	decremento7
	ENDC

	ORG	0x0
	goto	INICIO
	ORG 0x4
	btfss	INTCON,2
	retfie
	incf		PORTC,1
	bcf		INTCON,2
	retfie
	
INICIO

   	bsf		STATUS,RP0	;Me ubico en el banco 1 de la memoria
	clrf	TRISA		;PUERTO COMO SALIDA
	clrf	TRISB		;PUERTO COMO SALIDA
	clrf	TRISC		;PUERTO COMO SALIDA
	movlw	b'00000101'
	movwf	OPTION_REG
	bcf		STATUS,RP0;  
    ;EL TIMER 0 VA EN EL BANCO 0
	bcf		PORTC,0
	bsf		INTCON,4
	bsf		INTCON,3		; capacitores de 15pf para 100Khz
	bsf		INTCON,7
	bsf		INTCON,5
	movlw 	.200		;seteo el timer 0
	movwf	TMR0
		


MAIN
	clrwdt
	GOTO MAIN
	END

	
