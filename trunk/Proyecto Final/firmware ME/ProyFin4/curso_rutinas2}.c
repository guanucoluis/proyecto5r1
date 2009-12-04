#include "curso_rutinas.h"
extern unsigned char LocalData;		// Extern es porque las variables ya están definidas en otra  parte.
extern unsigned char LocalAddress;
extern unsigned char COUNT;
extern unsigned char x_display;
extern unsigned char y_display;
extern unsigned char TSend;

void InicioDisplay(void)			//Configuracion del display
{
	TSend=200;		//200				
	while(TSend!=0){}				//Esperamos los 40mseg, ya TSend se decrementa cada 500useg
	PutNibbleHi(0x30);				//Llamada a la funcion 
	TSend=20;					//Delay menor 
	while(TSend!=0){}				//a 1mseg
	PutNibbleHi(0x20);
	TSend=20;					 
	while(TSend!=0){}
	PutNibbleHi(0x20);				
	TSend=30;				 
	while(TSend!=0){}
	LcdPutCmd(0x28);					//Seguimos al pie de la letra la rutinas de
	LcdPutCmd(0x14);
	LcdPutCmd(0x0C);
	LcdPutCmd(0x01);
	LcdPutCmd(0x06);
	x_display=0;						//variables para movernos dentro de la matriz del display
	y_display=0;
}


void PutNibbleHi(char Lcd_Temp4)
{
	_TrisBit4=0;		//los definimos como salida
	_TrisBit5=0;
	_TrisBit6=0;
	_TrisBit7=0;
	_rs=0;				//habilita el envio de comando
	_rw=0;				//escribe
	_e=1;				//habilitamos
	if ((Lcd_Temp4 & 0x10) !=0)
		_DataBit4=1;
	else
		_DataBit4=0;
	if ((Lcd_Temp4 & 0x20) !=0)
		_DataBit5=1;
	else
		_DataBit5=0;
	if ((Lcd_Temp4 & 0x40) !=0)
		_DataBit6=1;
	else
		_DataBit6=0;
	if ((Lcd_Temp4 & 0x80) !=0)
		_DataBit7=1;
	else
		_DataBit7=0;
	Nop();
	Nop();
	Nop();
	_e=0;
	Nop();
	Nop();
	Nop();
	_TrisBit4=1;		//los definimos como entrada para que los pueda usar otro dispositivo
	_TrisBit5=1;
	_TrisBit6=1;
	_TrisBit7=1;
	return;
}

void LcdPutCmd(char Lcd_Temp)
{
	LcdBusy(); 			//llamamos a la rutina para testear el busy
	_rs=0;				//Comando
	PutNND(Lcd_Temp);
	return;
}

void LcdBusy(void)
{
	char a=0;
	while(a==0)
	{
		_rs=0;
		_rw=1;
		_e=1;
		if (_BusyBit==0) 
			a=1;
		_e=0;		//Con este conjunto de instrucciones leemos el estado del Busy_Bit
		Nop();
		Nop();
		Nop();
		_e=1;		//Para poder leerlo, es necesario que enable oscile actualizandolo
		Nop();
		Nop();
		Nop();
		_e=0;
	}
	_e=0;
	_rw=0;
	return;
}

void PutNND(char LcdTemp4) //Todo este quilombo es para inicializar el display
{
	_TrisBit4=0;		//los definimos como salida
	_TrisBit5=0;
	_TrisBit6=0;
	_TrisBit7=0;

	_DataBit4 = 0;
	_DataBit5 = 0;
	_DataBit6 = 0;
	_DataBit7 = 0;

	_rw=0; //Modo write

	if ((LcdTemp4 & 0x10) != 0) _DataBit4 = 1;		//Parte alta
	if ((LcdTemp4 & 0x20) != 0) _DataBit5 = 1;
	if ((LcdTemp4 & 0x40) != 0) _DataBit6 = 1;
	if ((LcdTemp4 & 0x80) != 0) _DataBit7 = 1;

	_e=1;		//Para poder leerlo, es necesario que enable oscile actualizandolo
	Nop();
	Nop();
	Nop();
	_e=0;
	Nop();
	Nop();
	Nop();
	_DataBit4 = 0;
	_DataBit5 = 0;
	_DataBit6 = 0;
	_DataBit7 = 0;

	if ((LcdTemp4 & 0x01) != 0) _DataBit4 = 1;		//Parte baja
	if ((LcdTemp4 & 0x02) != 0) _DataBit5 = 1;
	if ((LcdTemp4 & 0x04) != 0) _DataBit6 = 1;
	if ((LcdTemp4 & 0x08) != 0) _DataBit7 = 1;

	_e = 1;		

	Nop();
	Nop();
	Nop();

	_e = 0;

	Nop();
	Nop();
	Nop();

	_TrisBit4 = 1;		//Como Entrada
	_TrisBit5 = 1;		//Como Entrada
	_TrisBit6 = 1;		//Como Entrada
	_TrisBit7 = 1;		//Como Entrada
	return;
}

void LcdPutChar(char Lcd_Temp)
{
	LcdBusy();
	_rs=1;	//Indico es dato
	PutNND(Lcd_Temp);
	return;
}

void PrintfLcd(char *Texto)
{
	unsigned char Cursor;
	while(*Texto !='\0')
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
//---------------------------------
// Buffer RS232
//----------------------------------

void putrsUSART(const rom char *InString)  //rom es porq la constante que le pasamos está en la rom (flash).
{
	while(*InString)
	{
		TXREG = *InString;
		while((TXSTA & 0x02)==0){};
		InString++;
	}
}

void putRAMUSART(char *InString)  //rom es porq la constante que le pasamos está en la rom (flash).
{
	while(*InString)
	{
		TXREG = *InString;
		while((TXSTA & 0x02)==0){};
		InString++;
	}
}

