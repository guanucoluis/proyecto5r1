//INCLUDES
	//#include "teclado.h"	
	//#include "p30fxxxx.h"
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
/*Funci�n de Inicializaci�n del Display-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que inicializa el display de caracteres de 16x2
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void InicioDisplay(void);	//Inicializaci�n del display
	
	/*Funci�n LcdPutCmd-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que env�a un comando al LCD de carateres cuando �ste ya est� inicializado
	Entrada: Comando a enviar
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void LcdPutCmd(char Lcd_Temp);

	/*Funci�n LcdPutCmdIni-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que env�a un comando al LCD de caracteres sin que �ste est� inicializado
	Entrada: Comando a enviar
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void LcdPutCmdIni(char Lcd_Temp);
	
	/*Funci�n LcdBusy-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que consulta el bit de busy del lcd y sale cuando el lcd est� listo
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void LcdBusy(void);

	/*Funci�n PutNND-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que escribe un byte en el puerto de salida
	Entrada: Byte a poner en el puerto
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void PutNND(char LcdTemp4);

	/*Funci�n LcdPutChar-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que escribe un byte en el puerto de salida teniendo en cuenta si el LCD est� ocupado o no
	Entrada: Byte a sacar por el puerto de salida
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void LcdPutChar(char Lcd_Temp);
		
	/*Funci�n PrintfLcd-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que escribe una cadena de texto desde el inicio del LCD  
	Entrada: Puntero a la cadena de texto
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void PrintfLcd(char *Texto);

	/*Funci�n PrintfLcdXY-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que escribe una cadena de texto en el LCD en la posici�n (x,y)
	Entrada: coordenada x, coordenada y, puntero a la cadena de texto 
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void PrintfLcdXY(unsigned char x, unsigned char y, char *Texto);
