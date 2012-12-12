#ifndef	SENSORES_H
#define SENSORES_H

#include <globals.h>

#define	CANT_GRUP_PARAM	8

#define	DIAMETRO_TRAC_DEFECTO			180	//Valores en cent�metros
#define	DIAMETRO_NO_TRAC_DEFECTO	70	//Valores en cent�metros

struct Diametros{
	INT16U	diametroTrac;		//Di�metro de la rueda de Tracci�n en cent�metros
	INT16U	diametroNoTrac;	//Di�metro de la rueda de No Tracci�n	 en cent�metros
};

struct GrupoDeParam{
	unsigned bParamCargadosDesdeFlash	:1;	//Indica si los par�metros ya han sido cargados desde la Flash (1) o no (0)	

	INT8U	iGdP;
	struct Diametros diametros[8];
};

struct Med{
	unsigned	Usado						:1;
	unsigned 	Cant_Muestras		:15;
};
	
struct Sensores{
	unsigned	Vel_Trac_Min					:	1;
	unsigned	Vel_Maq_Min						:	1;
	unsigned	Band_Maq							:	1;
	unsigned	Band_Trac							:	1;
	unsigned	Buffer_Completo_Maq		:	1;
	unsigned 	Buffer_Completo_Trac	:	1;
	};
	
//Variables
extern struct GrupoDeParam param;

#endif //SENSORES_H

