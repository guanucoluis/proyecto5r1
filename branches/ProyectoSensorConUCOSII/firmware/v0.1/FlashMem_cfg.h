#ifndef EEPROM_H
#define EEPROM_H

#include "globals.h"
#include "sensores.h"

//#define	TableWrite();	_asm TBLWT*+ _endasm

#define TAMANIO_BLOQUE_BORRADO 1255
#define TAMANIO_BLOQUE_LECTURA 512
#define TAMANIO_BLOQUE_ESCRITURA 64
#define CANT_BLOQUES_ESCRITURA	6

//Direcciones de los bloques de Flash
#define	BLOQUE_FLASH	0x15300

//Offsets para cada variable
#define	OFFSET_CONFIG	0
#define	OFFSET_TARA	OFFSET_CONFIG + 6
#define	OFFSET_PARAMETROS	OFFSET_TARA + 6
#define	OFFSET_FOCOS	OFFSET_PARAMETROS + CANT_GRUP_PARAM * 4


//Prototipos
//void FlashBlockErase(void);
//void FlashByteRead(void);
//void FlashWordWrite(void);

void GuardarConfigFlash(void);
void CargarConfigFlash(void);

void GuardarParametros(void);
void CargarParametros(void);

void GuardarFocos(void);
void CargarFocos(void);

void GuardarTarar(void);
void CargarTarar(void);

#endif //end EEPROM_H

