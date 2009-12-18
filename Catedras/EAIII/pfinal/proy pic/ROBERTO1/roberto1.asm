#include <p16f877a.inc> 

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
	btfss	INTCON,1
	retfie
	incf	PORTA,1
	bcf		INTCON,1
	retfie
	
INICIO

   	bsf		STATUS,RP0	;Me ubico en el banco 1 de la memoria
	clrf	TRISA		;PUERTO COMO SALIDA
	movlw	b'00000000'
	movwf	TRISB		;PUERTO COMO SALIDA Y RB0 COMO ENTRADA
	clrf	TRISC		;PUERTO COMO SALIDA		
	clrf	TRISD
	clrf	TRISE
	movlw	b'01000000'
	movwf	OPTION_REG
	bcf		STATUS,RP0
	clrf	PORTC
	bcf		PORTC,0
	bsf		INTCON,4
	bsf		INTCON,3
	bsf		INTCON,7		; capacitores de 15pf para 100Khz


MAIN
	clrwdt

	movlw 0xF0;
	movwf decremento4;
looop3
	movlw 0xF0;
	movwf decremento5;
looop2
	movlw 0xF0;
	movwf decremento6;
looop1
	movlw 0xFF;
	movwf decremento7;
	
looop0	
	clrwdt	
	decfsz decremento4,1
	goto looop0
		
	decfsz decremento5,1
	goto looop1

	bsf		PORTD,1

	movlw 0xF0;
	movwf decremento4
loooop3
	movlw 0xF0;
	movwf decremento5
loooop2
	movlw 0xF0;
	movwf decremento6
loooop1
	movlw 0xFF;
	movwf decremento7
	
loooop0	
	;clrwdt	
	decfsz decremento4,1
	goto loooop0
		
	decfsz decremento5,1
	goto loooop1
		
	bcf		PORTD,1

	
	GOTO MAIN
	END