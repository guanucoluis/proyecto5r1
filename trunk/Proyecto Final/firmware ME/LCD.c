//INCLUDES
	#include "LCD.h"

//DECLARACION DE VARIABLES
	volatile unsigned char 	x_display;
	volatile unsigned char	y_display;
	volatile unsigned char	Cursor;
	volatile char CadenaEnBlanco1[17]={"                "};
	volatile char CadenaEnBlanco2[17]={"                "};
//DEFINICIÓN DE FUNCIONES
	/*Función de Inicialización del Display-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que inicializa el display de caracteres de 16x2
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void InicializarDisplay(void)	//Inicialización del display
		{		
			Delay_x100useg(2000);	//Demora de 200 mseg
			LCDPutCmdIni(0x30);			
			Delay_x100useg(500);	//Demora de 50 mseg
			LCDPutCmdIni(0x30);
			Delay_x100useg(500);	//Demora de 50 mseg
			LCDPutCmdIni(0x30);				
			Delay_x100useg(500);	//Demora de 50 mseg
			LCDPutCmd(0x38);		
			LCDPutCmd(0x14);
			LCDPutCmd(0x0C);
			LCDPutCmd(0x01);
			LCDPutCmd(0x06);
			x_display=0;					
			y_display=0;
		}

	/*Función LCDPutCmd-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que envía un comando al LCD de carateres cuando éste ya está inicializado
	Entrada: Comando a enviar
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void LCDPutCmd(char LCD_Temp)
		{
			LCDBusy(); 				//llamamos a la rutina para testear el busy
			_rs=0;						//Indico que voy a enviar un Comando
			//LCDTemp_PNND = LCD_Temp;
			PutNND(LCD_Temp);
			return;
		}

	/*Función LCDPutCmdIni-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que envía un comando al LCD de caracteres sin que éste esté inicializado
	Entrada: Comando a enviar
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void LCDPutCmdIni(char LCD_Temp)
		{
			_rs=0;						//Indico que voy a enviar un Comando
			//LCDTemp_PNND = LCD_Temp;
			PutNND(LCD_Temp);
			return;
		}

	/*Función LCDBusy-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que consulta el bit de busy del LCD y sale cuando el LCD está listo
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void LCDBusy(void)
		{
			char a=0;
			while(a==0)  //*salgo cuando el LCD se desocupe
			{
				_rs=0;
				_rw=1;
				_e=1;
				Nop();
				Nop();
				if (_BusyBit==0) 
					a=1;
				Nop();
				Nop();
				Nop();
				Nop();
				_e=0;		//Con este conjunto de instrucciones leemos el estado del Busy_Bit
				Nop();
				Nop();
				Nop();
				Nop();
				Nop();
				Nop();
				_e=1;		//Para poder leerlo, es necesario que enable oscile actualizandolo
				Nop();
				Nop();
				Nop();
				Nop();
				Nop();
				Nop();
				_e=0;
			}
			_e=0;
			_rw=0;
			return;
		}

	/*Función PutNND-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que escribe un byte en el puerto de salida
	Entrada: Byte a poner en el puerto
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void PutNND(char LCD_Temp)
		{
			_TrisBit0=0;		//los definimos como salida
			_TrisBit1=0;
			_TrisBit2=0;
			_TrisBit3=0;
			_TrisBit4=0;	
			_TrisBit5=0;
			_TrisBit6=0;
			_TrisBit7=0;
			
			_rw=0; //Modo write

			if ((LCD_Temp & 0x01) != 0) 
				_DataBit0 = 1;	
			else
				_DataBit0 = 0;	
			if ((LCD_Temp & 0x02) != 0) 
				_DataBit1 = 1;
			else
				_DataBit1 = 0;
			if ((LCD_Temp & 0x04) != 0) 
				_DataBit2 = 1;
			else
				_DataBit2 = 0;
			if ((LCD_Temp & 0x08) != 0) 
				_DataBit3 = 1;
			else
				_DataBit3 = 0;
			if ((LCD_Temp & 0x10) != 0) 
				_DataBit4 = 1;
			else
				_DataBit4 = 0;		
			if ((LCD_Temp & 0x20) != 0) 
				_DataBit5 = 1;
			else
				_DataBit5 = 0;
			if ((LCD_Temp & 0x40) != 0) 
				_DataBit6 = 1;
			else
				_DataBit6 = 0;
			if ((LCD_Temp & 0x80) != 0) 
				_DataBit7 = 1;
			else
				_DataBit7 = 0;
	
			_e = 1;		
		
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();

			_e = 0;
		
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();	
		
			_TrisBit0 = 1;		//Como Entrada
			_TrisBit1 = 1;		
			_TrisBit2 = 1;		
			_TrisBit3 = 1;	
			_TrisBit4 = 1;		//Como Entrada
			_TrisBit5 = 1;		
			_TrisBit6 = 1;		
			_TrisBit7 = 1;

			return;
		}

	/*Función LCDPutChar-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que escribe un byte en el puerto de salida teniendo en cuenta si el LCD está ocupado o no
	Entrada: Byte a sacar por el puerto de salida
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void LCDPutChar(char LCD_Temp)
		{
			LCDBusy();
			_rs=1;						//Indico es dato
			//LCDTemp_PNND = LCD_Temp;
			PutNND(LCD_Temp);
			return;
		}

	/*Función PrintfLCD-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que escribe una cadena de texto desde el inicio del LCD  
	Entrada: Puntero a la cadena de texto
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void PrintfLCD(char *Texto)
		{
			while(*Texto !=0)
			{
				LCDPutChar(*Texto);
				Texto++;
				x_display++;
				if (x_display > 15)
				{
					x_display=0;
					y_display++;
					//if (y_display > 3)
					if (y_display > 1)
						y_display=0;
					switch(y_display)
					{
						case 0:
							Cursor=0x00;
							break;
						case 1:
							Cursor=0x40;
							break;
						//Estas 6 líneas son para el caso de que tengamos un display de 4 líneas
						/*case 2:
							Cursor=0x14;
							break;
						case 3:
							Cursor=0x54;
							break;*/
					}
					Cursor += x_display;
					Cursor += 0x80;
					LCDPutCmd(Cursor);
				}
			}
		}

	/*Función PrintfLCDXY-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que escribe una cadena de texto en el LCD en la posición (x,y)
	Entrada: coordenada x, coordenada y, puntero a la cadena de texto 
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void PrintfLCDXY(unsigned char x, unsigned char y, char *Texto)
		{
			unsigned char Cursor=0;
			x_display = x;
			y_display = y;
			switch (y_display)
			{
				case 0:
					Cursor=0x00;
					break;
				case 1:
					Cursor=0x40;
					break;
				//Estas 6 líneas son para el caso de que tengamos un display de 4 líneas
				/*case 2:
					Cursor=0x14;
					break;
				case 3:
					Cursor=0x54;
					break;*/
			}
			Cursor += x_display;
			Cursor += 0x80;
			LCDPutCmd(Cursor);
			PrintfLCD(Texto);
		}

	/*Función LimpiarLCD-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que borra todos los caracteres que haya escritos en el LCD
	Entrada: nada 
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void LimpiarLCD(void)
		{
			PrintfLCDXY(0,0,(char *) CadenaEnBlanco1);
			PrintfLCDXY(0,1,(char *) CadenaEnBlanco2);
		}
