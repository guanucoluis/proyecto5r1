#ifndef VALEDIT_H
#define VALEDIT_H

//INCLUDES
#include	<button.h>

//DEFINES
//acciones de SpinEditEditar
#define ENTRAR 1
#define SALIR 2
#define CANCELAR 3
#define	IZQUIERDA 4
#define DERECHA 5

//Defines relativos a la geometría del ValEdit
#define ALTO_ELEM_VAL_ED			7
#define ANCHO_ELEM_VAL_ED			5	//Ancho en píxeles de elemento (texto) del ValEdit

#define ALTO_LABEL_3X5				5	//Alto en píxeles del caracter del Label
#define ANCHO_LABEL_3X5				3	//Ancho en píxeles del caracter del Label

#define	GROSOR_BORDE_VAL_ED		1 //Grosor en píxeles del borde que rodea al ValEdit
#define	SEP_ELEM_VAL_ED				1 //Separación en píxeles entre los elementos del ValEdit
#define	ANCHO_CURSOR_VAL_ED		1	//Ancho en píxeles del cursor del ValEdit
#define	SEP_CURSOR_VAL_ED			1	//Separación en píxeles entre el cursor y el elemento (texto) del ValEdit

#define NO_ACTUALIZAR_DIG			255	//no se actualiza ningún dígito, se redibujan todos
#define TITILEO_CURSOR_VAL_ED	250	//Contador usado para dividir la frecuencia del proceso de interfaz y crear el titileo

//Prototipos de ValEdits
void ValEditEditar(unsigned char accion);
void ValEditLeft(void);
void ValEditRight(void);
void ValEditIncDigit(void);
void ValEditDecDigit(void);
signed int ValEditGetValor(void);
void ValEditSetValor(signed int valor);

void ValEditTitCursor(void);
void ValEditActualizar(void);
void ValEditOnKeyPress(void);

#endif //VALEDIT_H


