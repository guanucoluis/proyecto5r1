#ifndef COMBO_BOX_H
#define COMBO_BOX_H

//INCLUDES
#include <label.h>

//DEFINES
//Defines relativos a la geometría del Label
#define ALTO_ELEM_CBOB_LABEL			7	//Alto en píxeles del caracter del Label
#define ANCHO_ELEM_CBOB_LABEL			5	//Ancho en píxeles del caracter del Label

#define ALTO_LABEL_3X5				5	//Alto en píxeles del caracter del Label
#define ANCHO_LABEL_3X5				3	//Ancho en píxeles del caracter del Label

#define	GROSOR_BORDE_CBOB			1 //Separación en píxeles entre el texto del Label y la parte de arriba
#define	SEP_ELEM_CBOB_LABEL		1 //Separación en píxeles entre los elementos del Label

#define	GROSOR_BORDE_LABEL		1 //Separación en píxeles entre el texto del Label y la parte de arriba

#define ALTO_TEXTO_35					5	//Altura del texto de 3x5
#define ALTO_TEXTO_57					7	//Altura del texto de 5x7
#define	SEPAR_CUAD_LABEL_CBOB	2	//Separación en píxeles del cuadrado y el Label

#define	ANCHO_CUAD_35_CBOB		9	//Ancho del cuadrado  al costado del ComboBox para el texto de 3x5
#define	ANCHO_CUAD_57_CBOB		9	//Ancho del cuadrado  al costado del ComboBox para el texto de 5x7

#define	CANT_OPCIONES_MOST		3	//Cantidad de opciones que  se muestran al entrar en modo edición
#define ANCHO_BARRA_DESPLAZ_CBOB	9	//Ancho de la barra de desplazamiento
#define	ESPACIO_LIMPIO_BORDE			2	//Ancho en píxeles del espacio extra que se limpia alrededor del ComboBox 

//Prototipos de ComboBoxs
void ComboBoxDesdibujar(void);
void ComboBoxActualizar(void);
void ComboBoxOnKeyPress(void);
void InicializarComboBox(void);

#endif //end COMBO_BOX_H


