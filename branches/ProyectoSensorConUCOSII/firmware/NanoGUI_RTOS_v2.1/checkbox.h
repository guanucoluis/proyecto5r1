#ifndef CHECK_BOX_H
#define CHECK_BOX_H

//INCLUDES
#include <label.h>

//DEFINES
//Defines relativos a la geometr�a del Label
#define ALTO_ELEM_CB_LABEL		7	//Alto en p�xeles del caracter del CheckBox
#define ANCHO_ELEM_CB_LABEL		5	//Ancho en p�xeles del caracter del CheckBox

#define ALTO_LABEL_3X5				5	//Alto en p�xeles del caracter del Label
#define ANCHO_LABEL_3X5				3	//Ancho en p�xeles del caracter del Label

#define	GROSOR_BORDE_CB				1 //Separaci�n en p�xeles entre el texto del Label y la parte de arriba
#define	SEP_ELEM_CB_LABEL			1 //Separaci�n en p�xeles entre los elementos del Label

#define	GROSOR_BORDE_LABEL		1 //Separaci�n en p�xeles entre el texto del Label y la parte de arriba

#define ALTO_TEXTO_35					5	//Altura del texto de 3x5
#define ALTO_TEXTO_57					7	//Altura del texto de 5x7
#define	SEPAR_CUAD_LABEL_CB		2	//Separaci�n en p�xeles del cuadrado y el Label

//Prototipos de CheckBox
void CheckBoxActualizar(void);
void CheckBoxOnKeyPress(void);

#endif //end CHECK_BOX_H

