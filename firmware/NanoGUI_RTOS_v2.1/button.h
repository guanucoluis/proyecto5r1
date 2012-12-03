#ifndef BUTTON_H
#define BUTTON_H

//INCLUDES
//#include "glcdK0108.h"
//#include "globals.h"
#include "interfaz.h"
#include <label.h>


//DEFINES
//Defines relativos a la geometría del Label
#define ALTO_ELEM_BT_LABEL			7	//Alto en píxeles del caracter del Label
#define ANCHO_ELEM_BT_LABEL			5	//Ancho en píxeles del caracter del Label

#define ALTO_LABEL_3X5				5	//Alto en píxeles del caracter del Label
#define ANCHO_LABEL_3X5				3	//Ancho en píxeles del caracter del Label

#define	GROSOR_BORDE_BT			1 //Separación en píxeles entre el texto del Label y la parte de arriba
#define	SEP_ELEM_BT_LABEL		1 //Separación en píxeles entre los elementos del Label

#define	GROSOR_BORDE_LABEL		1 //Separación en píxeles entre el texto del Label y la parte de arriba

//Prototipos de Botones
void ButtonActualizar(void);
void ButtonOnKeyPress(void);

#endif //end BUTTON_H

