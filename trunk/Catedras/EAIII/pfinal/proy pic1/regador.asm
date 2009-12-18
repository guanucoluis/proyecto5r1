    #include <p16f873a.inc> 

	CBLOCK 0X20
	decremento0
	decremento1
	decremento2
	decremento3
	ENDC
	
	ORG	0x0
	goto	INICIO

INICIO
   	bsf		STATUS,RP0	;Me ubico en el banco 1 de la memoria
	clrf	TRISA		;PUERTO COMO SALIDA
	clrf	TRISB		;PUERTO COMO SALIDA
	clrf	TRISC		;PUERTO COMO SALIDA
	bcf		STATUS,RP0;  
		


MAIN clrwdt
	bcf	PORTC,0;
	movlw 0x2F;
	movwf decremento0;
loop3
	movlw 0x2F;
	movwf decremento1; 
loop2
	movlw 0x3F;
	movwf decremento2;
loop1
	movlw 0x4F;
	movwf decremento3;
	
loop0	
	clrwdt	
	decfsz decremento3,1;
	goto loop0
		
	decfsz decremento2,1;
	goto loop1
		
	decfsz decremento1,1;
	goto loop2

	decfsz decremento0,1;
	goto loop3

	bsf	    PORTC,0;

	movlw 0x2F;
	movwf decremento0;
looop3
	movlw 0x2F;
	movwf decremento1;
looop2
	movlw 0x3F;
	movwf decremento2;
looop1
	movlw 0x4F;
	movwf decremento3;
	
looop0	
	clrwdt	
	decfsz decremento3,1;
	goto looop0
		
	decfsz decremento2,1;
	goto looop1
		
	decfsz decremento1,1;
	goto looop2

	decfsz decremento0,1;
	goto looop3
	goto	MAIN
	
	END

	
