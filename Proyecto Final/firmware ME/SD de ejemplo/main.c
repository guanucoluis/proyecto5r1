#include "main.h"
#include "\MDD File System\FSIO.h"
#include "FSconfig.h"
#include "HardwareProfile.h"
#include "Timers.h"

#pragma udata MyBanco1 = 0x106
	FSFILE *pOldFile, *pNewFile;
	char bfr [6];
	int bytesRead, bytesWritten;
#pragma udata

#pragma idata MyBanco2 = 0x140
	char myData[]={"Hola Mundo!"};
#pragma idata

void main(void)
{

/*//	FSFILE *pOldFile, pNewFile;
//	char myData[20];
//	char bfr [6];
//	int bytesRead, bytesWritten;
//	const char newFile[] = "newfile.txt";
	
	// Must initialize the FAT16/FAT32 library. It also initializes SPI and other related pins.
	if( !FSInit() )
		// Failed to initialize FAT16 – do something…
//		return 1; // Card not present or wrong format
	
	// Create a new file
	pNewFile = FSfopen (newFile, mode);
	
	// Open an existing file to read
	pOldFile = FSfopenpgm ("myfile.txt", "r");
	
	if ( pOldFile == NULL )
		// Either file is not present or card is not present
//		return 1;
	
	// Read 10 bytes of data from the file.
	bytesRead = FSfread((void*)myData, 10, 1, pOldFile);
	// read bfrSize (5) items (of size 1 byte). returns items count
//	bytesRead = FSfread( (void *)bfr, 1, bfrSize, pOldFile );
	
	// Write those fifteen bytes to the new file
	bytesWritten = FSfwrite ((void *) myData, 10, 1, pNewFile);
//	bytesWritten = FSfwrite ((void *) bfr, 1, bfrSize, pNewFile);
	
	// After processing, close the file.
	FSfclose( pOldFile );
	FSfclose (pNewFile);
	
	//Delete the old file
	FSremovepgm ("myfile.txt");
*/  
	static const rom char newFile[] = "Paulo.txt";
	static const rom char mode[] = "w";

	TRISAbits.TRISA5=0;
	TRISBbits.TRISB1=0;
	TRISCbits.TRISC7=0;
	TRISDbits.TRISD3=1;
	TRISBbits.TRISB0=1;

	
	OSCCONbits.SCS0=0; 	// Defino el oscilador primario como fuente (16 MHz) (p. 34).
	OSCCONbits.SCS1=0;	// Idem

	// Configuro el timer 2 para despues usarlo como clock del SPI
	// Count=(Fosc/4)/(2*400KHz)=(40MHz/4)/(800KHz)=12.5
	// Entonces PR=6.25. Porque del 0 al 6 tengo 7.
	PR2=6; // 6 para aprox 400 KHz.
	T2CON=0b00000100;

INICIO:
	while (!MDD_MediaDetect());

	MDD_SDSPI_MediaInitialize();
	
	while(!FSInit());
	pNewFile = FSfopenpgm (newFile, mode);
	bytesWritten = FSfwrite ((void *) myData, 1, 11, pNewFile);
	FSfclose(pNewFile);
	_asm
	goto INICIO
	_endasm
	while(1);
}

