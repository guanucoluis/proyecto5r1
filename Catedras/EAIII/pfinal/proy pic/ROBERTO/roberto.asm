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
	btfss	INTCON,1
	retfie
	incf	PORTB,1
	movlw 0x0F
	movwf decremento0;
loop3
	movlw 0x0F;
	movwf decremento1;
loop2
	movlw 0x0F;
	movwf decremento2;
loop1
	movlw 0xFF;
	movwf decremento3;
	
loop0	
;	clrwdt	
	decfsz decremento3,1;
	goto loop0
		
	decfsz decremento2,1;
	goto loop1
		
	decfsz decremento1,1;
	goto loop2

	decfsz decremento0,1;
	goto loop3

	bsf		PORTC,0
	bcf		INTCON,2
	retfie
	
INICIO

   	bsf		STATUS,RP0	;Me ubico en el banco 1 de la memoria
	clrf	TRISA		;PUERTO COMO SALIDA
	clrf	TRISB		;PUERTO COMO SALIDA
	clrf	TRISC		;PUERTO COMO SALIDA
	movlw	b'01000000'
	movwf	OPTION_REG
	bcf		STATUS,RP0;  
    ;EL TIMER 0 VA EN EL BANCO 0
	bcf		PORTC,0
	movlw 	0x0 		;seteo el timer 0
	movwf	TMR0
	bsf		INTCON,4
	bsf		INTCON,3		; capacitores de 15pf para 100Khz
	bsf		INTCON,7
	bsf		INTCON,5
		


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

;	decfsz decremento6,1
;	goto looop2

	;decfsz decremento7,1
	;goto looop3

	bsf		PORTC,1

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
		
;	decfsz decremento6,1
;	goto loooop2

;	decfsz decremento7,1
;	goto loooop3

	bcf		PORTC,1

	
	GOTO MAIN
	END

	
