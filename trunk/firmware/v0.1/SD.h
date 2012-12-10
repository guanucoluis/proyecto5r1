#ifndef SD_H
#define SD_H

//DEFINES
#define SD_CARD
#define	IMPRIMIR_PARAM_PID

//INCLUDES
#include <FSIO.h>
//#include <globals.h>


//ESTRUCTURAS
struct SDCard{
	unsigned bSDPresente	:1;	//Indica si la  SD está (1) o no (0) colocada en el sócalo
	unsigned bSDInic	:1;	//Indica si la SD ya ha sido inicializada
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

