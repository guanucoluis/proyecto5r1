//INCLUDES
	#include "LCD.h"

//DECLARACION DE VARIABLES
	volatile unsigned char 	x_display;
	volatile unsigned char	y_display;
	volatile unsigned char	Cursor;

//DEFINICIÓN DE FUNCIONES
	/*Función de Inicialización del Display-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que inicializa el display de caracteres de 16x2
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void InicioDisplay(void)	//Inicialización del display
		{
			//TSend=200;			
			//while(TSend!=0){}			
			Delay_x100useg(2000);	//Demora de 200 mseg
			LcdPutCmdIni(0x30);			
			//TSend=50;							 
			//while(TSend!=0){}
			Delay_x100useg(500);	//Demora de 50 mseg
			LcdPutCmdIni(0x30);
			//TSend=50;					 
			//while(TSend!=0){}
			Delay_x100useg(500);	//Demora de 50 mseg
			LcdPutCmdIni(0x30);				
			//TSend=50;			 
			//while(TSend!=0){}
			Delay_x100useg(500);	//Demora de 200 mseg
			LcdPutCmd(0x38);		//Seguimos al pie de la letra la rutinas de *inicialización
			Delay_100useg();
			LcdPutCmd(0x14);
			Delay_100useg();
			LcdPutCmd(0x0C);
			Delay_100useg();
			LcdPutCmd(0x01);
			Delay_100useg();
			LcdPutCmd(0x06);
			x_display=0;						//variables para movernos dentro de la matriz del display
			y_display=0;
		}

	/*Función LcdPutCmd-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que envía un comando al LCD de carateres cuando éste ya está inicializado
	Entrada: Comando a enviar
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void LcdPutCmd(char Lcd_Temp)
		{
			LcdBusy(); 				//llamamos a la rutina para testear el busy
			_rs=0;						//Indico que voy a enviar un Comando
			PutNND(Lcd_Temp);
			return;
		}

	/*Función LcdPutCmdIni-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que envía un comando al LCD de caracteres sin que éste esté inicializado
	Entrada: Comando a enviar
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void LcdPutCmdIni(char Lcd_Temp)
		{
			_rs=0;						//Indico que voy a enviar un Comando
			PutNND(Lcd_Temp);
			return;
		}

	/*Función LcdBusy-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que consulta el bit de busy del lcd y sale cuando el lcd está listo
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void LcdBusy(void)
		{
			char a=0;
			while(a==0)  //*salgo cuando el LCD se desocupe
			{
				Nop();
				Nop();
				Nop();
				_rs=0;
				Nop();
				Nop();
				Nop();
				_rw=1;
				Nop();
				Nop();
				Nop();
				_e=1;
				Delay_3_6useg();	//Esperar un tiempo mayor a 600 nseg
				if (_BusyBit==0) 
					a=1;
				Nop();
				Nop();
				Nop();
				_e=0;		//Con este conjunto de instrucciones leemos el estado del Busy_Bit
				Delay_10useg();	//Esperar un tiempo mayor a 600 nseg
				_e=1;		//Para poder leerlo, es necesario que enable oscile actualizandolo
				Delay_10useg();	//Esperar un tiempo mayor a 600 nseg
				_e=0;
			}
			_e=0;
			Nop();
			Nop();
			Nop();
			_rw=0;
			return;
		}

	/*Función PutNND-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que escribe un byte en el puerto de salida
	Entrada: Byte a poner en el puerto
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void PutNND(char LcdTemp4)
		{
			_TrisBit0=0;		//los definimos como salida
			_TrisBit1=0;
			_TrisBit2=0;
			_TrisBit3=0;
			_TrisBit4=0;	
			_TrisBit5=0;
			_TrisBit6=0;
			_TrisBit7=0;
			_DataBit0 = 0;
			_DataBit1 = 0;
			_DataBit2 = 0;
			_DataBit3 = 0;
			_DataBit4 = 0;
			_DataBit5 = 0;
			_DataBit6 = 0;
			_DataBit7 = 0;
			
			_rw=0; //Modo write

			if ((LcdTemp4 & 0x01) != 0) _DataBit0 = 1;		
			if ((LcdTemp4 & 0x02) != 0) _DataBit1 = 1;
			if ((LcdTemp4 & 0x04) != 0) _DataBit2 = 1;
			if ((LcdTemp4 & 0x08) != 0) _DataBit3 = 1;
			if ((LcdTemp4 & 0x10) != 0) _DataBit4 = 1;		
			if ((LcdTemp4 & 0x20) != 0) _DataBit5 = 1;
			if ((LcdTemp4 & 0x40) != 0) _DataBit6 = 1;
			if ((LcdTemp4 & 0x80) != 0) _DataBit7 = 1;
	
			Nop();
			Nop();
			Nop();

			_e = 1;		
		
			Delay_3_6useg();	//Esperar un tiempo mayor a 600 nseg

			_e = 0;
		
			Delay_3_6useg();	//Esperar un tiempo mayor a 600 nseg
		
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

	/*Función LcdPutChar-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que escribe un byte en el puerto de salida teniendo en cuenta si el LCD está ocupado o no
	Entrada: Byte a sacar por el puerto de salida
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void LcdPutChar(char Lcd_Temp)
		{
			LcdBusy();
			_rs=1;						//Indico es dato
			PutNND(Lcd_Temp);
			return;
		}

	/*Función PrintfLcd-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que escribe una cadena de texto desde el inicio del LCD  
	Entrada: Puntero a la cadena de texto
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void PrintfLcd(char *Texto)
		{
			while(*Texto !=0)
			{
				LcdPutChar(*Texto);
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
					LcdPutCmd(Cursor);
				}
			}
		}

	/*Función PrintfLcdXY-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que escribe una cadena de texto en el LCD en la posición (x,y)
	Entrada: coordenada x, coordenada y, puntero a la cadena de texto 
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void PrintfLcdXY(unsigned char x, unsigned char y, char *Texto)
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
			LcdPutCmd(Cursor);
			PrintfLcd(Texto);
		}
