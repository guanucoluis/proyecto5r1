#include "main.h"

// DS 51537 - Configuration Settings (Ver. C)
#pragma udata MyBanco1 = 0x100

/* VARIABLES DE LA SDCARD */
	FSFILE *pOldFile, *pNewFile;
	int bytesRead, bytesWritten;
	

#pragma udata

#pragma idata MyBanco3 = 0x300
	/* DECLARACION E INICILIACION DE VARIABLES SDCARD */
	char myData[]={"Siii Vamos! \n\n\n"};
 	static const char newFile[] = "Gonza.txt";
	static const char mode[] = "w";

	/* DECLARACION E INICILIACION DE VARIABLES UART */


#pragma code

int main(void)
{
	//INICIALIZACIÓN DE BANDERAS
	/*bandera=0;   // Bandera de la UART 
	enable.teclado=1;
	enable.teclas=1;
	enable.uart_write=0;
	enable.uart=0;
	enable.disp_hora =0;
	enable.disp_menu =0;
	enable.disp_pulso=0;
	enable.disp_corazon=0;
	enable.hora=1;
	
	ejec.teclado=0;
	ejec.teclas=0;
	ejec.uart_write=0;
	ejec.uart=0;
	ejec.disp_hora =0;
	ejec.disp_menu =0;
	ejec.disp_pulso=0;
	ejec.disp_corazon=0;
	ejec.hora=0;


	TRISA = 0xFF;
	TRISB = 0b00111111;;   //Configuro el RB1 como entrada, para la int del GPS cada 1 seg
	TRISC = 0x80;
	PORTC = 0X00;
	TRISD = 0x00;
	TRISE = 0x00;

	TRISAbits.TRISA5=0;
	TRISCbits.TRISC7=1;
	TRISCbits.TRISC6=1;
	TRISAbits.TRISA0=1;
	TRISCbits.TRISC4=1;*/
	
	SD_CS_TRIS = 0; //CS
	SPICLOCK = 0;		//SCK
	SPIOUT = 0;			//SDO
	SD_CD_TRIS = 1;	//CD
	SPIIN = 1;			//SDI
	
	SPICON1bits.PPRE = 0b01;	//Preescaler primario de 16
	SPICON1bits.SPRE = 0b110;	//Preescaler secundario de 2

	// Configuro el timer 2 para despues usarlo como clock del SPI
	// Count=(Fosc/4)/(2*400KHz)=(20MHz/4)/(800KHz)=6.25
	// Entonces PR=6.25. Porque del 0 al 6 tengo 7.
	//PR2=6; // 6 para aprox 400 KHz.
	//T2CON=0b00000100;

	//Config Timer 0

	/*OpenTimer1(TIMER_INT_ON & 
		   		T1_16BIT_RW & 
		   		T1_SOURCE_INT & 
		   		T1_PS_1_1);

	
	OpenUSART(	USART_TX_INT_OFF 	&
				USART_RX_INT_ON 	&
				USART_ASYNCH_MODE	&
				USART_EIGHT_BIT		&
				USART_CONT_RX		&
				USART_BRGH_LOW, 64);		//Para configurar a 4800 para 20Mhz
	BAUDCON=0x00;*/	

	//OSCCONbits.SCS0=0; 	// Defino el oscilador primario como fuente (16 MHz) (p. 34).
	//OSCCONbits.SCS1=0;	// Idem

	/* Habilito las interrupciones del RB1 para el GPS_1seg */
	/*INTCON2bits.INTEDG1=1;			// RISING EDGE
	INTCON3bits.INT1IP=0;   		// LOW PRIORITY
	INTCON3bits.INT1IE=1;*/
	
	//ADCON0=0X01;

	//ADCON2=0XA5;

	//InicioDisplay();	
	
	//sprintf((char *)Cadena, "  BIENVENIDO  ");
	//PrintfLcdXY(0,0,(char *)Cadena);

	while (!MDD_MediaDetect());

	while(!MDD_SDSPI_MediaInitialize());
	
	while(!FSInit());
	pNewFile = FSfopen(newFile, mode);
	bytesWritten = FSfwrite ((void *) myData, 1, 11, pNewFile);
	FSfclose(pNewFile);

	while(1);
   	
}		



