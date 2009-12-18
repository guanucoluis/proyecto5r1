#include <p16f873A.inc> 

	CBLOCK 0X20
	decremento4
	decremento5
	decremento6
	incremento
	ENDC

	ORG	0x0
	goto	INICIO
	ORG 0x4
	btfss	INTCON,1
	retfie
	movlw 0xFF;
	movwf decremento6
lop0
	decfsz decremento6,1
	goto lop0
	btfss	INTCON,1	
	retfie
	incf	incremento,1
	movf	incremento,w
	movwf	PORTC
	bcf		INTCON,1	;BORRO EL BIT DE BANDERA DE LA INT RB0
	bcf		INTCON,2   ;BORRO EL BIT DE BANDERA DEL TIMER 0
	retfie
	
INICIO

   	bsf		STATUS,RP0	;Me ubico en el banco 1 de la memoria
	clrf	TRISA		;PUERTO COMO SALIDA
	movlw	b'00000001'
	movwf	TRISB		;PUERTO COMO SALIDA Y RB0 COMO ENTRADA
	clrf	TRISC		;PUERTO COMO SALIDA		
	movlw	b'01000000'
	movwf	OPTION_REG
	bcf		STATUS,RP0
	clrf	PORTC
	clrf	PORTA
	clrf	incremento
	bsf		INTCON,4
	bsf		INTCON,3		
	bsf		INTCON,7
MAIN
	clrwdt
	movlw 0xF0;
	movwf decremento5;
looop1
	movlw 0xFF;
	movwf decremento4;
	
looop0	
	clrwdt	
	decfsz decremento4,1
	goto looop0
		
	decfsz decremento5,1
	goto looop1

	;bsf		PORTC,1


	movlw 0xF0;
	movwf decremento5
loooop1
	movlw 0xFF;
	movwf decremento4
	
loooop0	

	decfsz decremento4,1
	goto loooop0
		
	decfsz decremento5,1
	goto loooop1
		
	;bcf		PORTC,1
	
	GOTO MAIN
	END