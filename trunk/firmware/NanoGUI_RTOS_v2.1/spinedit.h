#ifndef SPINEDIT_H
#define SPINEDIT_H

//INCLUDES
#include <interfaz.h>

//DEFINES
#define TITILEO_CURSOR_SPIN_EDIT 250 //veces por segund que titila el cursor

//acciones de SpinEditEditar
#define ENTRAR 1
#define SALIR 2
#define CANCELAR 3

//Defines relativos a la geometría del SpinEdit
#define ALTO_ELEM_SPIN_ED			7
#define ANCHO_ELEM_SPIN_ED		5	//Ancho en píxeles de elemento (texto) del SpinEdit

#define ALTO_LABEL_3X5				5	//Alto en píxeles del caracter del Label
#define ANCHO_LABEL_3X5				3	//Ancho en píxeles del caracter del Label

#define	GROSOR_BORDE_SPIN_ED		1 //Grosor en píxeles del borde que rodea al SpinEdit
#define	SEP_ELEM_SPIN_ED				1 //Separación en píxeles entre los elementos del SpinEdit
#define	ANCHO_CURSOR_SPIN_ED		0	//Ancho en píxeles del cursor del SpinEdit
#define	SEP_CURSOR_SPIN_ED			0	//Separación en píxeles entre el cursor y el elemento (texto) del SpinEdit

//Variables
extern unsigned int valorTemp; //toma el valor temporal del SpinEdit hasta que se presione ACEPTAR

//Prototipos de SValEdits
void SpinEditIncrementar(void);
void SpinEditDecrementar(void);
void SpinEditEditar(unsigned char accion);
void SpinEditEfectoEdicion(void);
void SpinEditActualizar(void);
void SpinEditOnKeyPress(void);

#endif //end SPINEDIT_H


