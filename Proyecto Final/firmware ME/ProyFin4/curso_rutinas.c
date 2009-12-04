#include "curso_rutinas.h"


extern unsigned char LocalData;		// Extern es porque las variables ya están definidas en otra  parte.
extern unsigned char LocalAddress;
extern unsigned char COUNT;
extern unsigned char x_display;
extern unsigned char y_display;
extern unsigned char TSend;
extern unsigned char i;

extern struct banderas enable, ejec;

extern unsigned char Buffer_uart[MAX_BUFFER];
extern unsigned char Hora[3];
extern unsigned char Minu[3];
extern unsigned char Segu[3];
extern unsigned char hora;
extern unsigned char minuto;
extern unsigned char segundo;
extern unsigned char Cadena[16];


void InicioDisplay(void)			//Configuracion del display
{
	//PORT initialization  
	//8-bit mode, use whole port
    XLCD_DATAPORT_TRIS  = 0x00;             //make DATAPORT output
    XLCD_DATAPORT = 0;

	//control port initialization
	XLCD_RSPIN_TRIS = 0;                         //make control ports output
	XLCD_ENPIN_TRIS = 0;
	XLCD_RWPIN_TRIS = 0;
	
	XLCD_RSPIN = 0;                             //clear control ports
	XLCD_ENPIN = 0;
	XLCD_RWPIN = 0;	

//initialization by instruction

    XLCDDelay15ms(); 
	XLCDDelay15ms();                  
	XLCDDelay15ms();

    XLCD_DATAPORT   = 0b00110000;   // Function set cmd(8-bit interface)
    Nop();
    Nop();
	Nop();
    Nop();
	Nop();
	Nop();
	XLCD_ENPIN = 1;                 // Clock the cmd in
    Nop();
	Nop();
	Nop();
	Nop();
	Nop();
    XLCD_ENPIN = 0;

    XLCDDelay4ms();
 /*              
    XLCD_DATAPORT   = 0b00110000;   // Function set cmd(8-bit interface)
    Nop();
	Nop();
    Nop();
	Nop();
    Nop();
	Nop();
	XLCD_ENPIN = 1;                 // Clock the cmd in
    Nop();
	Nop();
	Nop();
	Nop();
	Nop();  
    XLCD_ENPIN = 0;
   */
    XLCDDelay4ms(); 
                 
    XLCD_DATAPORT   = 0b00110000;   // Function set cmd(8-bit interface)
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	XLCD_ENPIN = 1;                 // Clock the cmd in
    Nop();
	Nop();
	Nop();
	Nop();
	Nop();    
    XLCD_ENPIN = 0;

// 	LcdPutCmd(0x28);					//Seguimos al pie de la letra la rutinas de
//	LcdPutCmd(0x14);
//	LcdPutCmd(0x0C);
//	LcdPutCmd(0x0F);
//	LcdPutCmd(0x01);
//	LcdPutCmd(0x06);
	LcdPutCmd(0x38);
	LcdPutCmd(0x0C);   //Disp ON - Cur OFF - Blink OFF
	LcdPutCmd(0x01);   //Clear Disp
	LcdPutCmd(0x06);   //Shift Cursor Incremental

}


void LcdPutCmd(unsigned char cmd)
{
    XLCDIsBusy();
	XLCD_RSPIN=0;
	XLCD_ENPIN=0;
	XLCD_RWPIN=0;
	Nop();
    XLCD_DATAPORT = cmd;                    // Write command to data port
    Nop();
	Nop();
	Nop();
	XLCD_ENPIN = 1;                         // Clock the cmd in
	Nop();
	Nop();
	Nop();
    XLCD_ENPIN = 0;
    return;
}

void XLCDIsBusy(void)
{
	char a=0;
	XLCD_DATAPORT_TRIS  = 0xFF;	
	while(a==0)
	{
		XLCD_RSPIN=0;
		XLCD_RWPIN=1;
		XLCD_ENPIN=1;
		Nop();
		Nop();
		Nop();
		//PORTEbits.RE0=1;
		if (XLCD_BUSYBit==0) 
			a=1;
		XLCD_ENPIN=0;		//Con este conjunto de instrucciones leemos el estado del Busy_Bit
		//PORTEbits.RE0=0;
		Nop();
		Nop();
		Nop();
		XLCD_ENPIN=1;
		//PORTEbits.RE0=1;		//Para poder leerlo, es necesario que enable oscile actualizandolo
		Nop();
		Nop();
		Nop();
		XLCD_ENPIN=0;
		//PORTEbits.RE0=0;
	}
	XLCD_DATAPORT_TRIS  = 0x00;
	return;
}

void LcdPutChar(char Lcd_Temp)
{
	XLCDIsBusy();
	XLCD_RWPIN=0;
	XLCD_RSPIN=1;
	XLCD_ENPIN=0;
	Nop();
	Nop();
	Nop();
	XLCD_DATAPORT = Lcd_Temp;                    // Write command to data port
    Nop();
	Nop();
	Nop();
	XLCD_ENPIN = 1;                         // Clock the cmd in
	Nop();
	Nop();
	Nop();
    XLCD_ENPIN = 0;
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

void XLCDDelay15ms (void)
{
    int i;
    for(i=0;i<0.015/TIEMPO_INSTR;i++)
    {
		Nop();
    }
    return;
}

/*The user  is require to write this 4 milli second delay in his routine,this  delay */
/*is required as it is used in XLCDInit() which is used to initialize the LCD module*/

void XLCDDelay4ms (void)
{
    int i;
    for(i=0;i<0.05/TIEMPO_INSTR;i++)
    {
		Nop();
    }
    return;
}

void RutinaHora(void)
{
	enable.uart_write=1;
	if(Buffer_uart[18]=='A') //Dato Válido
	{
		Hora[0]=Buffer_uart[7];
		Hora[1]=Buffer_uart[8];
		Hora[2]='\0';
		Minu[0]=Buffer_uart[9];
		Minu[1]=Buffer_uart[10];
		Minu[2]='\0';
		Segu[0]=Buffer_uart[11];
		Segu[1]=Buffer_uart[12];
		Segu[2]='\0';
		enable.uart_write=0;    //Libero el buffer
		hora=atoi((char *)Hora);
		minuto=atoi((char *)Minu);
		segundo=atoi((char *)Segu);
		if(hora<3)
			hora=hora+21;
		else
			hora=hora-3;
		sprintf((char *)Cadena, "   %02d:%02d:%02d   ", hora, minuto, segundo);
		PrintfLcdXY(0,0, (char *)Cadena);
	}	
	else   //Caso contrario muestro "ESPERANDO SATELITES"
	{
   	    sprintf((char *)Cadena,"   ESPERANDO  ");
		PrintfLcdXY(0,0,(char *)Cadena);
		sprintf((char *)Cadena,"   SATELITES  ");
		PrintfLcdXY(0,1,(char *)Cadena);
		enable.uart_write=0;
	}
}