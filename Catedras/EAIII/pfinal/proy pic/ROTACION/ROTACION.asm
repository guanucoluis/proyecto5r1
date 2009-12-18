#include <p16f873a.inc> 

CBLOCK 0X20
	decremento0
	decremento1
	incremento
	ENDC

	ORG	0x0
	goto	INICIO
	ORG 0x4
	btfss	INTCON,1
	retfie
	movlw	0x01
	movwf	decremento0
decremento
	decfsz	decremento0,1
	goto decremento
	movlw	0x01
	movwf	decremento1
decremento00
	decfsz	decremento1,1
	goto decremento00
	bcf		INTCON,1
	clrw	0x0
	incf	incremento
	movf	incremento,0
	call 	convert
	movwf 	PORTC;   ****ver que pasa aca!!!!!!!!
	retfie
convert
	addwf	PCL,1
	retfie '00000000'
	retfie '00000001'
	retfie '00000010'
	retfie '00000011'
	retfie '00000100'
	retfie '00000101'
	retfie '00000110'	
	retfie '00000111'
	retfie '00001000'	
	retfie '00001001'
	retfie '00010000'
	retfie '00010001'
	retfie '00010010'
	retfie '00010011'
	retfie '00010100'
	retfie '00010101'
	retfie '00010110'	
	retfie '00010111'
	retfie '00011000'	
	retfie '00011001'
	retfie '00100000'
	retfie '00100001'
	retfie '00100010'
	retfie '00100011'
	retfie '00100100'
	retfie '00100101'
	retfie '00100110'	
	retfie '00100111'
	retfie '00101000'	
	retfie '00101001'
	retfie '00100000'
	retfie '00100001'
	retfie '00100010'
	retfie '00100011'
	retfie '00100100'
	retfie '00100101'
	retfie '00100110'	
	retfie '00100111'
	retfie '00101000'	
	retfie '00101001'
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
	clrf	incremento
	bcf		PORTC,0
	bsf		INTCON,4
	bsf		INTCON,3
	bsf		INTCON,7		; capacitores de 15pf para 100Khz


MAIN
	clrwdt
	
	GOTO MAIN
	END