#ifndef SD_H
#define SD_H

//DEFINES
#define SD_CARD

//INCLUDES
#include "FSIO.h"

#define PERIODO_CHEQUEO_SD 200

#define	SPRE_LENTO	0b001	
#define	PPRE_LENTO	0b01

#define	SPRE_RAPIDO	0b000
#define	PPRE_RAPIDO	0b11

// Description: SD-SPI Card Detect Input bit
#define SD_CARD_DETECT	PORTAbits.RA8
// Description: SD-SPI Card Detect TRIS bit
#define SD_CARD_DETECT_TRIS	TRISAbits.TRISA8

//ESTRUCTURAS
struct SDCard{
	unsigned bSDPresente	:1;	//Indica si la  SD está (1) o no (0) colocada en el sócalo
	unsigned bSDInic	:1;	//Indica si la SD ya ha sido inicializada
	unsigned bFrecuenciaRapida :1;	//Indica si la SD se está comunicando a una frec menor a 400KHz (0) o mayor a 400 Khz (1)
	//Variables relativas a la Tarjeta SD y los archivos
	volatile FSFILE *pNewFile;
	//int bytesRead, bytesWritten;
	//struct SearchRec	rec;	//Estructura para guardar la info de los archivos encontrados
	char *newFile;
	char mode; 
	unsigned int bytesWritten;
};

//Variables relativas a la Tarjeta SD y los archivos
extern struct SDCard sd;
extern char newFile[];

//Variables de GuardarMuestra()
extern char cadenaMuestra[];

//PROTOTIPOS
void GetLastMed(void);
void OpenNewMed(void);
void InicSD(void);
void ImprimirEncabezado(void);
void GuardarMuestra(void);

#endif //Fin SD_H

