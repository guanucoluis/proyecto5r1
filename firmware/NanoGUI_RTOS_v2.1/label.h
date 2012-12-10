#ifndef LABEL_H
#define LABEL_H

//INCLUDES
#include <interfaz.h>

//DEFINES

//Defines relativos a la geometría del Label
#define ALTO_ELEM_LABEL				7	//Alto en píxeles del caracter del Label
#define ANCHO_ELEM_LABEL			5	//Ancho en píxeles del caracter del Label
#define	SEP_ELEM_LABEL				1 //Separación en píxeles entre los elementos del Label

#define ALTO_LABEL_3X5				5	//Alto en píxeles del caracter del Label
#define ANCHO_LABEL_3X5				3	//Ancho en píxeles del caracter del Label

//Prototipos de Label
void LabelActualizar(void);
void LabelCantPixels(void);

#endif //end LABEL_H

