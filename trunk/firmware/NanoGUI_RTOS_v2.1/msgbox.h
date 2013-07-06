#ifndef MSGBOX_H
#define MSGBOX_H

//INCLUDES
#include <interfaz.h>
//#include	<stdint.h>

//DEFINES

//Defines relativos a la geometr�a del MsgBox
#define	MARGEN_A_CAJA	5 //Separaci�n entre los objetos (texto, botones, etc.) y la caja del mensaje en p�xeles
#define	SEPARACION_OBJETOS 2 //Separaci�n en p�xeles entre los objetos 
#define	ANCHO_BORDE_MSG	1	//Ancho del Borde del mensaje
#define	ANCHO_EFECTO_3D	1	//Ancho del efecto de profundidad
#define	BORDE_EXT_CAJA	2	//Ancho del espacio en blanco que rodea a la caja
//Prototipos de MsgBox
void MostrarMsg(const uint8_t *ptrTexto, const uint8_t *ptrOpciones, uint8_t anchoMax, uint8_t segundos);

#endif //end MSGBOX_H

