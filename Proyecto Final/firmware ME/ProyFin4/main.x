#include "main.h"

// DS 51537 - Configuration Settings (Ver. C)
#pragma config OSC = HS     	/* Para osc a 20Mhz */
#pragma config FCMEN = OFF		/* Para forzar a usar solo el osc externo */
#pragma config IESO = OFF		/* Osc Interno OFF */
#pragma config PWRT = ON 		/* Power Up Timer ON */
#pragma config BOREN = OFF		/* Si detecta una falla en la alimentacion: RESET */
#pragma config BORV = 3     	/* La tensión a la que se resetea, antes 43 */
#pragma config WDT = OFF, WDTPS = 128 /* Watch Dog Timer ON y con un preescaler de 128 */
#pragma config MCLRE = ON		/* MCLR Externo ON */
#pragma config LPT1OSC = OFF	/* Timer 1 Osc Int OFF */
#pragma config PBADEN = OFF		/* Pines del B no analógicos */
//#pragma config CCP2MX = PORTC	/* El capture del PWM lo manejo por el puerto C */
#pragma config STVREN = ON 		/* Si hay un desborde del stack: RESET */
#pragma config LVP = OFF		/* Low Voltage Programming OFF */
#pragma config XINST = ON		/* Para modo extendido */
#pragma config DEBUG = ON		/* Para habilitar el ICD */


#pragma udata MyBanco1 = 0x100
	unsigned char PRUEBA;
	FSFILE *pOldFile, *pNewFile;
	char bfr [6];
	int bytesRead, bytesWritten;
	unsigned char LocalData;
	unsigned char LocalAddress;
	unsigned char COUNT;
	unsigned int Conversor;
	unsigned char AcumAD;
	unsigned int Canal0;
	char Cadena[128];
	unsigned char TSend;			// Para el display
	unsigned char x_display;
	unsigned char y_display;
	unsigned char Columna;			// Para el teclado
	unsigned char Temp_Tec;
	unsigned char Temp_No_Tec;
	unsigned char Last_Tec;
	unsigned char New_Tec;
	unsigned char Tecla;
	unsigned char Etapa;
	unsigned char TempNro;
	unsigned char TempNro1;
	unsigned char TempRes;
	unsigned char TempPos;
	unsigned char segundo;
	unsigned char minuto;	
	unsigned char hora;
	unsigned char dia;
	unsigned char mes;
	unsigned char ano;
	unsigned char Hexa;
	unsigned char semana;
	int	IntTemp;

	
//Para el RX232
	char RxData;
	unsigned char SaveFSR0L;
	unsigned char SaveFSR0H;
	

#pragma udata


//-----------------------------------------
//-----Estructura del buffer RS232---------
//-----------------------------------------

#pragma udata MyBanco2 = 0x200
	struct BuRx Buffer232; //Defino una estructura para el buffer de recepcion RS232
	unsigned char velocidad[13];
	unsigned char Cadena1[16];
#pragma udata


void main(void)
{

	static const rom char newFile[] = "Rulo.txt";
	static const rom char mode[] = "w";
	unsigned char count1=0;
	unsigned char i=0;	

	Columna=0;
	Temp_No_Tec=250;
	Last_Tec=0;
	New_Tec=0;
	Temp_Tec=0;
	AcumAD = 64;
	Conversor=0;

//	ADCON1 = 0x8E;

	TRISA = 0xFF;
	TRISB = 0x00;
	TRISC = 0x80;
	TRISD = 0x00;
	TRISE = 0x00;

	TRISAbits.TRISA5=0;
	TRISCbits.TRISC7=1;
	TRISAbits.TRISA0=1;
	TRISCbits.TRISC4=1;

	

	
	// Configuro el timer 2 para despues usarlo como clock del SPI
	// Count=(Fosc/4)/(2*400KHz)=(20MHz/4)/(800KHz)=6.25
	// Entonces PR=6.25. Porque del 0 al 6 tengo 7.
	PR2=6; // 6 para aprox 400 KHz.
//	T2CON=0b00000100;

	//Config Timer 2


/*	OpenTimer3(	TIMER_INT_ON &       // Timer 3 con interrupciones cada medio segundo aprox.
				T2_PS_1_4	 &
				T2_POST_1_8	  );*/

	PR2 = 156;
	OpenTimer2(	TIMER_INT_ON &       //SE COMENTA PORQ HAY UN ERROR DE CONFIGURACION EN ESTE MICRO SE DEBE HACER MANUAL
				T2_PS_1_4	 &
				T2_POST_1_8	  );

//	PIE2|=0x02;
//	T3CON = 0b10110001;

	OpenADC( 	ADC_FOSC_8 		&
				ADC_RIGHT_JUST	&
				ADC_16_TAD		&
				ADC_CH0			&
				ADC_VREFPLUS_VDD	&
				ADC_VREFMINUS_VSS,
				ADC_INT_ON, 0X0E);    
	
	ADCON0=0X01;
	ADCON1=0X0E;
	ADCON2=0XA5;

	OpenUSART(	USART_TX_INT_OFF 	&
				USART_RX_INT_ON 	&
				USART_ASYNCH_MODE	&
				USART_EIGHT_BIT		&
				USART_CONT_RX		&
				USART_BRGH_LOW, 64);		//Para configurar a 4800 para 20Mhz
	
	//BAUDCON|=0x08;
//	BAUDCON|=0x20;
	
	INTCON |= 0xC0;

	ResetBufferRx((unsigned char *)&Buffer232);

	InicioDisplay();	
	
	Etapa=0;
	New_Tec=0;
	TempNro=0;
	
	sprintf(Cadena, "BIENVENIDO: ");
	PrintfLcdXY(0,0,Cadena);
	
/*
	while (!MDD_MediaDetect());

	MDD_SDSPI_MediaInitialize();
	
	while(!FSInit());
	pNewFile = FSfopenpgm (newFile, mode);
	bytesWritten = FSfwrite ((void *) myData, 1, 11, pNewFile);
	FSfclose(pNewFile);
*/

	
	while(1)
	{
		RxData=Get_Dato_Buffer((unsigned char *)&Buffer232);
		if(RxData=='$')
		{
    	    RxData=Get_Dato_Buffer((unsigned char *)&Buffer232); 
			while(RxData==-1)
			{
					RxData=Get_Dato_Buffer((unsigned char *)&Buffer232);
			}
			if(RxData=='G')
    	    {
    	        RxData=Get_Dato_Buffer((unsigned char *)&Buffer232); 
    	        while(RxData==-1)
				{
					RxData=Get_Dato_Buffer((unsigned char *)&Buffer232);
				}
				if(RxData=='P')
    	        {
    	            RxData=Get_Dato_Buffer((unsigned char *)&Buffer232); 
					while(RxData==-1)
					{	
						RxData=Get_Dato_Buffer((unsigned char *)&Buffer232);
					}			        
    				if(RxData=='R')
       		        {
                    	RxData=Get_Dato_Buffer((unsigned char *)&Buffer232); 
                    	while(RxData==-1)
						{	
							RxData=Get_Dato_Buffer((unsigned char *)&Buffer232);
						}
						if(RxData=='M')
                    	{
            				RxData=Get_Dato_Buffer((unsigned char *)&Buffer232); 
							while(RxData==-1)
							{
								RxData=Get_Dato_Buffer((unsigned char *)&Buffer232);
							}
							if(RxData=='C')
                        	{
                        	    while(count1<1)
                        	    {
                            	    RxData=Get_Dato_Buffer((unsigned char *)&Buffer232); 
									while(RxData==-1)
									{
										RxData=Get_Dato_Buffer((unsigned char *)&Buffer232);
									}                                	
									if(RxData==',')
                                	    count1++;
                            	}
								count1=0;
								RxData=Get_Dato_Buffer((unsigned char *)&Buffer232); 
                            	TSend=32;
								while(TSend!=0){}
								RxData=Get_Dato_Buffer((unsigned char *)&Buffer232); 
								while(RxData!=',')
								{
									if(RxData!='-1'&&i<10)
                        	    	{
										velocidad[i]=RxData;
										i++;
									}

									RxData=Get_Dato_Buffer((unsigned char *)&Buffer232); 
								}
								velocidad[i]='\0';
								i=0;
								LcdPutCmd(0x01);
								sprintf(Cadena, "H: %s", velocidad);
								PrintfLcdXY(0,0,Cadena);
                        	}
                    	}
                	}
            	}
         	}
		}

	}
}



#pragma code HiVector = 0x08	
void atHiVector(void)
{
	_asm goto MiVector _endasm
}

#pragma code

#pragma interrupt MiVector

void MiVector(void)
{
	_asm
	btfsc	PIR1,1,0	//Chequeo si la int vino del Timer3
	goto	Timer3
	btfsc	PIR1,6,0	//Chequeo si la int vino del conv
	goto	Rconvert
	btfsc	PIR1,5,0	//Chequeo RCIF para ver si la int vino de la USART
	goto	RecRxPc
	goto	FinInt


//++++++++++++++++++++++++++++
//    Rutina Rx232
//++++++++++++++++++++++++++++
RecRxPc:
	bcf		PIR1,5,0
	movlb	0x01
	movff	FSR0H,SaveFSR0H   	//Salvo el puntero del FSR apra el direccionamiento indirecto
	movff	FSR0L,SaveFSR0L
	btfsc	RCSTA,2,0   	  	//FERR
	goto	WasErr2
	btfsc	RCSTA,1,0		  	//0ERR
	goto	WasErr2
	movlw	MxBufferSize
	movlb	0x02
	subwf	(Buffer232+0),0,1   //NDatos
	bc		WasErr2
	clrf	FSR0H,0
	movf	(Buffer232+1),0,1   //Leo la direccion de PunteroIn
	addlw	(Buffer232+3)		//Le sumo la direccion de donde comienza el buffer
	movwf	FSR0L,0				//Guardo el valor del buffer en el fsr0l
	movlw	0x02
	addwf	FSR0H,1,0      		//Le sumo 2 a la parte alta porq estoy en el banco 2
	movff	RCREG,INDF0			//Paso RCREG a la direccion del buffer
	incf	(Buffer232+1),1,1	//Incremento PunteroIn
	movlw	MxBufferSize		
	subwf	(Buffer232+1),0,1   //Chequeo que PunteroIn no sea mayor que MxBufferSize
	bnc		NoRst2				//Si no es mayor salto
	clrf	(Buffer232+1),1		//Sino Limpio PunteroIn	
NoRst2:
	incf	(Buffer232+0),1,1   //Incremento NDatos
	goto 	SalRx2
WasErr2:	
	movff	RCREG,WREG			//Para limpiar el error
SalRx2:
	movlb	0x01
	movff	SaveFSR0H,FSR0H
	movff	SaveFSR0L,FSR0L
	goto	FinInt

//++++++++++++++++++++++++++++
// 		Rutina Timer 3
//++++++++++++++++++++++++++++
Timer3:
	bcf		PIR1,1,0
	movlb	0x01			//_endasm
	btfsc	PORTB,0,0
	goto	Sigue
	bsf		PORTB,0,0
	goto 	Sigue2
Sigue:	
	bcf		PORTB,0,0
//	goto 	FinInt
Sigue2:
	movf	TSend,1,1		//if (TSend != 0)
	bz		Conv			
	decf	TSend,1,1		


Conv:
//	bsf		ADCON0,1,0	//GO
//	movlw	0x03
//	movwf	TSend,1
	goto 	FinInt
//++++++++++++++++++++++++++++
//    Rutina Conversor
//++++++++++++++++++++++++++++
Rconvert:
	bcf		PIR1,6,0
	movlb	0x01
	movf	ADRESL,0,0
	addwf	Conversor+0,1,1
	movf	ADRESH,0,0
	addwfc	Conversor+1,1,1
/*	decfsz	AcumAD,1,1
	goto	FinInt
	movlw	64
	movwf	AcumAD,1
	movf	Conversor+0,0,1
	movwf	Canal0+0,1
	movf	Conversor+1,0,1
	movwf	Canal0+1,1
	clrf	Conversor+0,1
	clrf	Conversor+1,1
*/
	goto	FinInt


FinInt:
	_endasm
}
