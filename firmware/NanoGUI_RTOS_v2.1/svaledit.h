#ifndef SVALEDIT_H
#define SVALEDIT_H

//comienzo sValEdit
//#ifdef SVAL_EDIT

//INCLUDES
#include "glcdK0108.h"
#include "globals.h"

//DEFINES
#define	NUM_ELEM_SVAL_ED_0			3	//Indica el n�mero de elementos que tiene el SValEdit
#define	NUM_ELEM_SVAL_ED_1			4	//Indica el n�mero de elementos que tiene el SValEdit
#define	NUM_ELEM_SVAL_ED_2			4	//Indica el n�mero de elementos que tiene el SValEdit
#define	NUM_ELEM_SVAL_ED_3			4	//Indica el n�mero de elementos que tiene el SValEdit

//Defines relativos a la geometr�a del SValEdit
#define ALTO_ELEM_SVAL_ED			7
#define ANCHO_ELEM_SVAL_ED			5	//Ancho en p�xeles de elemento (texto) del SValEdit

#define	GROSOR_BORDE_SVAL_ED		1 //Grosor en p�xeles del borde que rodea al SValEdit
#define	SEP_ELEM_SVAL_ED				1 //Separaci�n en p�xeles entre los elementos del SValEdit
#define	ANCHO_CURSOR_SVAL_ED		1	//Ancho en p�xeles del cursor del SValEdit
#define	SEP_CURSOR_SVAL_ED			1	//Separaci�n en p�xeles entre el cursor y el elemento (texto) del SValEdit

#define NO_ACTUALIZAR_SVAL_ED	255	//C�digo usado para indicar que no es necesario actualizar el SValEdit		

#define TITILEO_CURSOR_SVAL_ED		8	//Contador usado para dividir la frecuencia del proceso de interfaz y crear el titileo

//ESTRUCTURAS
struct SValEdit{
	unsigned  char tipoStruct; //Utilizado para identificar la estructura
	unsigned	bVisible	: 1;	//Indica si el SValEdit debe ser dibujado o no
	unsigned  bRedibujar:	1;	//Indica si el SValEdit debe ser redibujado completamente
	unsigned	bEnFoco		:	1;	//Indica si el SValEdit tiene actualmente el foco
	unsigned 	tamanioTexto:	3;//Indica el multiplicador que tiene el tama�o del texto
	
	unsigned	bEditable	: 1;	//Indica si el valor almacenado en el SValEdit se puede editar o no
	unsigned	bEditando	:	1;	//Indica si el SValEdit est� siendo editado en este momento
	unsigned 	bSignoPos	:	1;	//Indica si el signo del valor del SValEdit es positivo cuando est� en modo num�rico
	unsigned	bCursorDib:	1;	//Indica si el cursor esta dibujado debajo del caracter que se esta editando

	unsigned char indFocoElem;//Indica  cual  de los elementos del SValEdit tiene el foco (esta siendo editado) dentro de la  m�scara de edici�n
	char	*ptrCadena;					//Puntero a la Cadena de d�gitos que muestra el SValEdit
	unsigned char numElem;		//Indica cuantos elementos tiene la cadena del SValEdit
	unsigned char posX;				//Posici�n en X de la parte inferior izquierda del SValEdit
	unsigned char posY; 			//Posici�n en Y de la parte inferior izquierda del SValEdit
	signed int valMax;				//Valor m�ximo capaz de almacenar el SValEdit en modo N�merico
	signed int valMin;				//Valor m�nimo capaz de almacenar el SValEdit en modo N�merico
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