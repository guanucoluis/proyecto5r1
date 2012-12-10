#ifndef	SENSORES_H
#define SENSORES_H

#define	CANT_GRUP_PARAM	8

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
	
#endif //SENSORES_H

