 #include <p16f84a.inc> 

	CBLOCK 0X20
	inc_dec
	vari
	vari1
	ENDC

	ORG	0x0
	goto	INICIO
	
	ORG 0x4

	btfsc	INTCON,1
	goto arriba
	movf	PORTB,0
	movwf	vari
	btfss	vari,7
	nop
	btfss	vari1,0
	goto 	abajo
	clrf	vari
	clrf	vari1
	bcf		INTCON,RBIF ; borro la bandera de RB7 por soft
	retfie
	
	
INICIO
	movlw	0x00
	movwf	vari1
	movlw	0x00
	movwf	vari
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
	clrf	vari	
	goto MAIN

arriba
	
	movlw	b'10001'
	addwf	inc_dec,0
	btfsc	STATUS,1		; se pasa para arriba de 1111
	goto 	desTxMax		
	bcf		PORTB,3			; Deshabilita transmición
	bcf		PORTB,2			;Led Min
	incf	inc_dec,1
	movf	inc_dec,0
	movwf	PORTA
	bcf		INTCON,INTF  	; borro la bandera de RB0 por soft
	retfie

abajo
	movlw	b'01111'
	andwf	inc_dec,0
	btfsc	STATUS,Z		; si se pasa para abajo de 0000
	goto 	desTxMin
	bcf		PORTB,3			; Deshabilita transmición
	bcf		PORTB,1	
	decf	inc_dec,1
	movf	inc_dec,0
	movwf	PORTA
	movlw	0x01
	movwf	vari1
	bcf		INTCON,RBIF 	; borro la bandera de RB7 por soft
	retfie
desTxMax
	bsf		PORTB,3			; Deshabilita transmición
	bsf		PORTB,1			; Led Max
	bcf		INTCON,INTF  	; borro la bandera de RB0 por soft
	retfie
desTxMin
	bsf		PORTB,3			; Deshabilita transmición
	bsf		PORTB,2			; Led Min
	movlw	0x01
	movwf	vari1
	bcf		INTCON,RBIF 	; borro la bandera de RB7 por soft
	retfie

	END

	
