#ifndef LCD_H
	#define LCD_H

//INCLUDES
	#include "dsPIC_delay.h"

//DEFINES RELATIVOS AL LCD
	#define _rs					PORTFbits.RF4
	#define _rw					PORTDbits.RD3
	#define _e					PORTFbits.RF5
	#define _TrisBit0		TRISBbits.TRISB8
	#define _TrisBit1		TRISBbits.TRISB9
	#define _TrisBit2		TRISBbits.TRISB10
	#define _TrisBit3		TRISBbits.TRISB11
	#define _TrisBit4		TRISBbits.TRISB12
	#define _TrisBit5		TRISDbits.TRISD0
	#define _TrisBit6		TRISDbits.TRISD1
	#define _TrisBit7		TRISDbits.TRISD2
	#define _DataBit0   PORTBbits.RB8
	#define _DataBit1   PORTBbits.RB9
	#define _DataBit2   PORTBbits.RB10
	#define _DataBit3   PORTBbits.RB11
	#define _DataBit4   PORTBbits.RB12
	#define _DataBit5   PORTDbits.RD0
	#define _DataBit6   PORTDbits.RD1
	#define _DataBit7   PORTDbits.RD2
	#define _BusyBit    PORTDbits.RD2	

//PROTOTIPOS DE FUNCIONES
/*Función de Inicialización del Display-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que inicializa el display de caracteres de 16x2
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void InicializarDisplay(void);	//Inicialización del display
	
	/*Función LCDPutCmd-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que envía un comando al LCD de carateres cuando éste ya está inicializado
	Entrada: Comando a enviar
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void LCDPutCmd(char LCD_Temp);

	/*Función LCDPutCmdIni-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que envía un comando al LCD de caracteres sin que éste esté inicializado
	Entrada: Comando a enviar
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void LCDPutCmdIni(char LCD_Temp);
	
	/*Función LCDBusy-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que consulta el bit de busy del LCD y sale cuando el LCD está listo
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void LCDBusy(void);

	/*Función PutNND-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que escribe un byte en el puerto de salida
	Entrada: Byte a poner en el puerto
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void PutNND(char LCD_Temp);

	/*Función LCDPutChar-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que escribe un byte en el puerto de salida teniendo en cuenta si el LCD está ocupado o no
	Entrada: Byte a sacar por el puerto de salida
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void LCDPutChar(char LCD_Temp);
		
	/*Función PrintfLCD-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que escribe una cadena de texto desde el inicio del LCD  
	Entrada: Puntero a la cadena de texto
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void PrintfLCD(char *Texto);

	/*Función PrintfLCDXY-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que escribe una cadena de texto en el LCD en la posición (x,y)
	Entrada: coordenada x, coordenada y, puntero a la cadena de texto 
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void PrintfLCDXY(unsigned char x, unsigned char y, char *Texto);

	/*Función LimpiarLCD-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que borra todos los caracteres que haya escritos en el LCD
	Entrada: nada 
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void LimpiarLCD(void);

#endif
