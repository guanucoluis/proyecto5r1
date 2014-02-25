#ifndef STRINGEDIT_H
#define STRINGEDIT_H

//comienzo de stringEdit
//#ifdef STRING_EIDT

//INCLUDES
#include "glcdK0108.h"
#include "globals.h"

//DEFINES
#define	NUM_ELEM_STR_ED_0			4	//Indica el número de elementos que tiene el StringEdit
#define	NUM_ELEM_STR_ED_1			4	//Indica el número de elementos que tiene el StringEdit
#define	NUM_ELEM_STR_ED_2			8	//Indica el número de elementos que tiene el StringEdit
#define	NUM_ELEM_STR_ED_3			4	//Indica el número de elementos que tiene el StringEdit

#define	NUM_ELEM_VIS_STR_ED_0	4	//Indica el número de elementos que se muestran del StringEdit
#define NUM_ELEM_VIS_STR_ED_1	4	//Indica el número de elementos que se muestran del StringEdit
#define NUM_ELEM_VIS_STR_ED_2	4	//Indica el número de elementos que se muestran del StringEdit
#define NUM_ELEM_VIS_STR_ED_3	4	//Indica el número de elementos que se muestran del StringEdit

//Defines relativos a la geometría del StringEdit
#define ALTO_ELEM_STR_ED			7
#define ANCHO_ELEM_STR_ED			5	//Ancho en píxeles de elemento (texto) del StringEdit

#define	GROSOR_BORDE_STR_ED		1 //Separación en píxeles entre el texto del StringEdit y la parte de arriba
#define	SEP_ELEM_STR_ED				1 //Separación en píxeles entre los elementos del StringEdit
#define	ANCHO_CURSOR_STR_ED		1	//Ancho en píxeles del cursor del StringEdit
#define	SEP_CURSOR_STR_ED			1	//Separación en píxeles entre el cursor y el elemento (texto) del StringEdit

#define NO_ACTUALIZAR_STR_ED	255	//Código usado para indicar que no es necesario actualizar el StringEdit		

#define TITILEO_CURSOR_STR_ED		8	//Contador usado para dividir la frecuencia del proceso de interfaz y crear el titileo

//ESTRUCTURAS
struct StringEdit{
	unsigned  char tipoStruct; //Utilizado para identificar la estructura
	unsigned	bVisible	: 1;	//Indica si el StringEdit debe ser dibujado o no
	unsigned  bRedibujar:	1;	//Indica si el StringEdit debe ser redibujado completamente
	unsigned	bEnFoco		:	1;	//Indica si el StringEdit tiene actualmente el foco
	unsigned 	tamanioTexto:	3;//Indica el multiplicador que tiene el tamaño del texto con el que se dibuja el Objeto de interfaz

	unsigned	bEditable	: 1;	//Indica si el valor almacenado en el StringEdit se puede editar o no
	unsigned	bEditando	:	1;	//Indica si el StringEdit está siendo editado en este momento
	unsigned	bCursorDib:	1;	//Indica si el cursor esta dibujado debajo del caracter que se esta editando

	unsigned char indFocoElem;		//Indica  cual  de los elementos del StringEdit tiene el foco (esta siendo editado) dentro de la  máscara de edición
	unsigned char indActualiz;//Indica cual de los  elementos debe ser actualizado en pantalla (redibujado) - 255 indica que no es necesario actualizar
	char	*ptrCadena;					//Puntero a la Cadena de dígitos que muestra el StringEdit
	unsigned char numElem;		//Indica cuantos elementos tiene la cadena del StringEdit
	unsigned char numElemVis;	//Indica cuantos elementos se muestran en el StringEdit
	unsigned char offset;			//Indica cual elemento de la cadena del StringEdit se muestra en la posición de más a la izquierda
	unsigned char posX;				//Posición en X de la parte inferior izquierda del StringEdit
	unsigned char posY; 			//Posición en Y de la parte inferior izquierda del StringEdit
};


extern char cadenaStrEd0[NUM_ELEM_STR_ED_0];
extern char cadenaStrEd1[NUM_ELEM_STR_ED_1];
extern char cadenaStrEd2[NUM_ELEM_STR_ED_2];
extern char cadenaStrEd3[NUM_ELEM_STR_ED_3];


//Prototipos Del StringEdit
void StrEd_AvFocoElem();
void StrEd_RetFocoElem();
void StrEd_SetString( char *ptrString);
void StrEd_SetElemSup();
void StrEd_SetElemInf();
void StrEd_OnKeyPress();
void StrEd_TitCursor();
void StrEd_Actualizar();

//#endif //fin de stringEdit

#endif //end STRINGEDIT_H