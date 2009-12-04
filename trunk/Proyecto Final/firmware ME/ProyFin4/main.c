#include "main.h"

// DS 51537 - Configuration Settings (Ver. C)
#pragma udata MyBanco1 = 0x100

/* VARIABLES DE LA SDCARD */
	FSFILE *pOldFile, *pNewFile;
	int bytesRead, bytesWritten;
	

#pragma udata

#pragma idata MyBanco3 = 0x300
	/* DECLARACION E INICILIACION DE VARIABLES SDCARD */
	char myData[]={"ESTE ES UN GRAN AVANCE!!! \n\n\n"};
 	static const char newFile[] = "LUIS.txt";
	static const char mode[] = "w";

	/* DECLARACION E INICILIACION DE VARIABLES UART */


#pragma code

int main(void)
{
	
	SD_CS_TRIS = 0; //CS
	SPICLOCK = 0;		//SCK
	SPIOUT = 0;			//SDO
	SD_CD_TRIS = 1;	//CD
	SPIIN = 1;			//SDI
	
	SPICON1bits.PPRE = 0b01;	//Preescaler primario de 16
	SPICON1bits.SPRE = 0b110;	//Preescaler secundario de 2


	while (!MDD_MediaDetect());

	while(!MDD_SDSPI_MediaInitialize());
	
	while(!FSInit());
	pNewFile = FSfopen(newFile, mode);
	bytesWritten = FSfwrite ((void *) myData, 1, 25, pNewFile);
	FSfclose(pNewFile);

	while(1);
   	
}		



