#ifndef EEPROM_H
#define EEPROM_H

#include "globals.h"

//#define	TableWrite();	_asm TBLWT*+ _endasm

#define TAMANIO_BLOQUE_BORRADO 1255
#define TAMANIO_BLOQUE_LECTURA 512
#define TAMANIO_BLOQUE_ESCRITURA 64
#define CANT_BLOQUES_ESCRITURA	6

//Direcciones de los bloques de Flash
#define	BLOQUE_FLASH	0x15300

//Offsets para cada variable
#define	OFFSET_CONFIG	0
#define	OFFSET_PARAMETROS	2
#define	OFFSET_FOCOS	OFFSET_PARAMETROS + CANT_GRUP_PARAM * 4

//Prototipos
void FlashBlockErase(void);
void FlashByteRead(void);
void FlashWordWrite(void);

#endif //end EEPROM_H

