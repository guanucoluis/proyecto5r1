#ifndef MSGBOX_H
#define MSGBOX_H

//INCLUDES
#include <interfaz.h>
//#include	<stdint.h>

//DEFINES

//Defines relativos a la geometría del MsgBox
#define	MARGEN_A_CAJA	5 //Separación entre los objetos (texto, botones, etc.) y la caja del mensaje en píxeles
#define	SEPARACION_OBJETOS 2 //Separación en píxeles entre los objetos 
#define	ANCHO_BORDE_MSG	1	//Ancho del Borde del mensaje
#define	ANCHO_EFECTO_3D	1	//Ancho del efecto de profundidad
#define	BORDE_EXT_CAJA	2	//Ancho del espacio en blanco que rodea a la caja
#define ESPACIO_BOTONES	12 //Espacio dejado en la parte de abajo del mensaje para los botones

//TIPOS DE MENSAJE
#define	MENSAJE_POR_TIEMPO 0
#define MENSAJE_OK	1
#define MENSAJE_OK_ESC	2

//Prototipos de MsgBox
void MostrarMsg(const uint8_t *ptrTexto, uint8_t tipoMsg, uint8_t anchoMax, uint8_t segundos);

#endif //end MSGBOX_H

