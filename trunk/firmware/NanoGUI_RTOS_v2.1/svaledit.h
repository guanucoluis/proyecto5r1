#ifndef SVALEDIT_H
#define SVALEDIT_H

//comienzo sValEdit
//#ifdef SVAL_EDIT

//INCLUDES
#include "glcdK0108.h"
#include "globals.h"

//DEFINES
#define	NUM_ELEM_SVAL_ED_0			3	//Indica el número de elementos que tiene el SValEdit
#define	NUM_ELEM_SVAL_ED_1			4	//Indica el número de elementos que tiene el SValEdit
#define	NUM_ELEM_SVAL_ED_2			4	//Indica el número de elementos que tiene el SValEdit
#define	NUM_ELEM_SVAL_ED_3			4	//Indica el número de elementos que tiene el SValEdit

//Defines relativos a la geometría del SValEdit
#define ALTO_ELEM_SVAL_ED			7
#define ANCHO_ELEM_SVAL_ED			5	//Ancho en píxeles de elemento (texto) del SValEdit

#define	GROSOR_BORDE_SVAL_ED		1 //Grosor en píxeles del borde que rodea al SValEdit
#define	SEP_ELEM_SVAL_ED				1 //Separación en píxeles entre los elementos del SValEdit
#define	ANCHO_CURSOR_SVAL_ED		1	//Ancho en píxeles del cursor del SValEdit
#define	SEP_CURSOR_SVAL_ED			1	//Separación en píxeles entre el cursor y el elemento (texto) del SValEdit

#define NO_ACTUALIZAR_SVAL_ED	255	//Código usado para indicar que no es necesario actualizar el SValEdit		

#define TITILEO_CURSOR_SVAL_ED		8	//Contador usado para dividir la frecuencia del proceso de interfaz y crear el titileo

//ESTRUCTURAS
struct SValEdit{
	unsigned  char tipoStruct; //Utilizado para identificar la estructura
	unsigned	bVisible	: 1;	//Indica si el SValEdit debe ser dibujado o no
	unsigned  bRedibujar:	1;	//Indica si el SValEdit debe ser redibujado completamente
	unsigned	bEnFoco		:	1;	//Indica si el SValEdit tiene actualmente el foco
	unsigned 	tamanioTexto:	3;//Indica el multiplicador que tiene el tamaño del texto
	
	unsigned	bEditable	: 1;	//Indica si el valor almacenado en el SValEdit se puede editar o no
	unsigned	bEditando	:	1;	//Indica si el SValEdit está siendo editado en este momento
	unsigned 	bSignoPos	:	1;	//Indica si el signo del valor del SValEdit es positivo cuando está en modo numérico
	unsigned	bCursorDib:	1;	//Indica si el cursor esta dibujado debajo del caracter que se esta editando

	unsigned char indFocoElem;//Indica  cual  de los elementos del SValEdit tiene el foco (esta siendo editado) dentro de la  máscara de edición
	char	*ptrCadena;					//Puntero a la Cadena de dígitos que muestra el SValEdit
	unsigned char numElem;		//Indica cuantos elementos tiene la cadena del SValEdit
	unsigned char posX;				//Posición en X de la parte inferior izquierda del SValEdit
	unsigned char posY; 			//Posición en Y de la parte inferior izquierda del SValEdit
	signed int valMax;				//Valor máximo capaz de almacenar el SValEdit en modo Númerico
	signed int valMin;				//Valor mínimo capaz de almacenar el SValEdit en modo Númerico
};

extern char cadenaSValEd0[NUM_ELEM_SVAL_ED_0];
extern char cadenaSValEd1[NUM_ELEM_SVAL_ED_1];
extern char cadenaSValEd2[NUM_ELEM_SVAL_ED_2];
extern char cadenaSValEd3[NUM_ELEM_SVAL_ED_3];


//Prototipos de SValEdits
void SValEd_AvFocoElem();
void SValEd_RetFocoElem();
signed int SValEd_GetValor();
void SValEd_SetValor( signed int valor);
void SValEd_SetElemSup();
void SValEd_SetElemInf();
void SValEd_OnKeyPress();
void SValEd_TitCursor();
void SValEd_Actualizar();

//#endif //end SVAL_EDIT

#endif //end SVALEDIT_H