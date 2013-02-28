#ifndef INTERFAZ_H
#define INTERFAZ_H

//INCLUDES
#include "glcdK0108.h"
#include "globals.h"
#include "teclado.h"
#include "label.h"
#include "button.h"
#include "checkbox.h"
#include "combobox.h"
#include "spinedit.h"
//#include "stringEdit.h"
#include "valedit.h"
//#include "sValEdit.h"
#include "progbar.h"
#include "msgbox.h"
#include <configinterfaz.h>	


//HABILITACION DE OBJETOS GRAFICOS DE LA BIBLIOTECA
#define FORM
#define LABEL
#define BUTTON
#define CHECK_BOX
//#define	COMBO_BOX
#define SPIN_EDIT		//Editor de numeros positivos muy simple
//#define VAL_EDIT
#define PROG_BAR
#define	MSG_BOX
//#define	SVAL_EDIT		//Simple ValEdit. Este ValEdit es mas sencillo y ocupa menos memoria de programa

//Tipos de Struct
#define STRUCT_LABEL 1
#define STRUCT_BUTTON 2
#define STRUCT_SPIN_EDIT 3
#define STRUCT_VAL_EDIT 4
#define STRUCT_STRING_EDIT 5
#define STRUCT_SVAL_EDIT 6
#define STRUCT_CHECK_BOX 7
#define STRUCT_COMBO_BOX 8
#define STRUCT_PROG_BAR 9

//Tamaño en bytes de los datos de Inicialización de los objetos gráficos
#define	TAMANIO_DATOS_LABEL 6
#define	TAMANIO_DATOS_BUTTON 6
#define	TAMANIO_DATOS_SPIN_EDIT 13
#define	TAMANIO_DATOS_VAL_EDIT 13
#define	TAMANIO_DATOS_CHECKBOX 7
#define	TAMANIO_DATOS_COMBOBOX 8
#define	TAMANIO_DATOS_PROGBAR 8

#define COLOR_NO_NEGADO 0
#define	COLOR_NEGADO		1

#define	EDITABLE	1
#define	NO_EDITABLE	0

//Foco
//Nota: los focos de las pantallas no pueden ser 0 porque ese es el valor para decir que no hay foco asignado
#define	FOCO_NINGUNO 0

struct Cargador{
	union Estado estado;
	#ifdef	LABEL
	struct Label label;
	#endif

	#ifdef	BUTTON
	struct Button button;
	#endif

	#ifdef	SPIN_EDIT
	struct SpinEdit spinEdit;
	#endif

	#ifdef	VAL_EDIT
	struct ValEdit valEdit;
	#endif

	#ifdef	CHECK_BOX
	struct CheckBox checkBox;
	#endif

	#ifdef	COMBO_BOX
	struct ComboBox comboBox;
	#endif

	#ifdef	PROG_BAR
	struct ProgBar progBar;
	#endif

	#ifdef	MSG_BOX
	struct MsgBox msgBox;
	#endif

	unsigned char tipoStruct;	//Tipo de estructura  del Objeto Gráfico
	//unsigned char indObjGraf;	//Índice del objeto dentro de la matriz de datos
	unsigned char indDatosObjGraf;	//Índice del objeto dentro de la matriz de datos

	//Variables de posición
	unsigned char x;	//Posición en X del Objeto Gráfico
	unsigned char y;	//Posición en Y del Objeto Gráfico
	unsigned char xLabel;	//Posición en X del Label asociado al Objeto Gráfico
	unsigned char yLabel;	//Posición en Y del Label asociado al Objeto Gráfico

	//Variables usadas en el manejo de las cadenas de texto asociadas a los objetos graficos
	unsigned char tamanioTexto;	//Indica el multiplicador que tiene el tamaño del texto
	unsigned char numCadena;		//Número de la cadena de texto asociada al objeto gráfico
	unsigned char indCadena;	//Indice de la cadena de texto
	unsigned int offsetDatos;	//Offset desde el inicio de la matriz de datos
	unsigned int offsetCadena;	//Offset desde el inicio de la matriz de textos
	unsigned char offsetChar;		//Offset del caracter dentro de la cadena a la que se está copiando
	char cadenaTexto[TAMANIO_CADENA_TEXTO];	//Cadena de caracteres que va a contener el texto y otros usos
	char cadenaAux[TAMANIO_CADENA_AUX];	//Cadena de texto auxiliar
	unsigned char cantCaracteres;		//Indica cuantos caracteres tiene la cadena del Label
	unsigned char cantPixeles;	//Indica cuantos pixeles tiene la cadena, sin espacios entre letras

	unsigned char cadenaDatos[TAMANIO_CADENA_DATOS];	//Cadena usada en la copia temporal de los datos	
	unsigned char indDatos;	//Índice para copias temporalmente los Datos de la Flash a la RAM

	unsigned char numValProp;	//Número del valor propio asociado al objeto gráfico
};

//PROTOTIPOS DE FUNCIONES
void InicInterfaz(void);
void ActualizarInterfaz(void);
void QuitarFoco(void);
void CargarPantalla(void);
void CambiarPantalla(unsigned char numPant);
void SetFoco(void);
unsigned char AsignarFoco(void);
void RetrocederFoco(void);
void AvanzarFoco(void);
void EventoTecla(void);

#endif //INTERFAZ_H

