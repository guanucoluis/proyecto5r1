 #include <p16f84a.inc> 

	CBLOCK 0X20
	decremento0
	decremento1
	decremento2
	decremento3
	inc_dec
	ENDC

	ORG	0x0
	goto	INICIO
	
	ORG 0x4

	btfsc	INTCON,1
	goto arriba
		
	btfsc	INTCON,0; testeo el cambio de estado de RB7
	goto abajo
	
	retfie
	
	
INICIO
   	bsf		STATUS,RP0	;Me ubico en el banco 1 de la memoria
	movlw	b'00000'
	movwf	TRISA		;PUERTO COMO SALIDA
	movlw	b'10000001'
	movwf	TRISB		; Entradas RB0 y RB7. Resto COMO SALIDA
	movlw	b'11000000' ;Flanco de RB0 como ascendente
	movwf	OPTION_REG
	bcf		STATUS,RP0
	movlw	b'10011000'; habilito interrupciones globales y perisfericos, RB0, y RB4-RB7
	movwf	INTCON
	movlw	b'01000'; seteo al puerto A como 01000 para que el motor arranque parado.
	movwf	inc_dec
	movf	inc_dec,0
	movwf	PORTA
	clrf 	PORTB



MAIN
	clrwdt	

		
	goto MAIN

arriba
	bcf		INTCON,INTF  ; borro la bandera de RB0 por soft
	btfsc	inc_dec,4  ; se pasa para arriba de 1111
	goto 	desTxMax
	bcf		PORTB,4
	bcf		PORTB,1
	incf	inc_dec,1
	movf	inc_dec,0
	movwf	PORTA
	retfie

abajo
	bcf		INTCON,RBIF ; borro la bandera de RB7 por soft
	andwf	inc_dec,1
	btfsc	STATUS,Z	; si se pasa para abajo de 0000
	goto 	desTxMin
	bcf		PORTB,4
	bcf		PORTB,2
	decf	inc_dec,1
	movf	inc_dec,0
	movwf	PORTA
	retfie
desTxMax
	bsf		PORTB,4
	bsf		PORTB,1
	retfie
desTxMin
	bsf		PORTB,4
	bsf		PORTB,2
	retfie

	END

	
