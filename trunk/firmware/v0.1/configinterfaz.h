#ifndef CONFIGINTERFAZ_H
#define CONFIGINTERFAZ_H

#include "interfaz.h"
#include "objetos.h"

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

//Defines de las pantallas:
#define	NUM_PANTALLAS       9	
#define PANTALLA_PRESENTA   1
#define PANTALLA_INICIO     2
#define PANTALLA_MEDICIONES 3
#define PANTALLA_PARAMETROS 4
#define PANTALLA_CONFIG     5

#define	CANT_MAX_OBJETOS_PANTALLA   30	//Máxima cantidad de objetos dentro de un Form (pantalla)
#define CANT_MAX_OBJETOS_FOCO       15	//Máxima cantidad de objetos dentro de un Form que pueden tener foco
#define CANT_FOCO CANT_MAX_OBJETOS_FOCO

//Contenidos de los Formularios
#define CANT_LABEL_FORM_PRESENTA    3
#define	CANT_OBJ_FORM_PRESENTA			CANT_LABEL_FORM_PRESENTA

#define CANT_LABEL_FORM_INICIO      1
#define CANT_BUTTON_FORM_INICIO     4
#define	CANT_OBJ_FORM_INICIO				CANT_LABEL_FORM_INICIO + CANT_BUTTON_FORM_INICIO

#define CANT_LABEL_FORM_MEDICIONES        11
#define CANT_BUTTON_FORM_MEDICIONES       2
#define CANT_SPIN_EDIT_FORM_MEDICIONES    9
#define	CANT_CHECK_BOX_FORM_MEDICIONES    2
#define	CANT_OBJ_FORM_MEDICIONES					CANT_LABEL_FORM_MEDICIONES + CANT_BUTTON_FORM_MEDICIONES + CANT_SPIN_EDIT_FORM_MEDICIONES + CANT_CHECK_BOX_FORM_MEDICIONES

#define CANT_LABEL_FORM_PARAMETROS      7
#define CANT_BUTTON_FORM_PARAMETROS     3
#define CANT_SPIN_EDIT_FORM_PARAMETROS  5
#define	CANT_OBJ_FORM_PARAMETROS				CANT_LABEL_FORM_PARAMETROS + CANT_BUTTON_FORM_PARAMETROS + CANT_SPIN_EDIT_FORM_PARAMETROS

#define CANT_LABEL_FORM_CONFIG      4
#define CANT_BUTTON_FORM_CONFIG     1
#define CANT_SPIN_EDIT_FORM_CONFIG  1
#define	CANT_CHECK_BOX_FORM_CONDFIG 1
#define CANT_PROG_BAR_FORM_CONFIG   2
#define	CANT_OBJ_FORM_CONFIG				CANT_LABEL_FORM_CONFIG + CANT_BUTTON_FORM_CONFIG + CANT_SPIN_EDIT_FORM_CONFIG + CANT_CHECK_BOX_FORM_CONDFIG + CANT_PROG_BAR_FORM_CONFIG		

#define	CANT_SPIN_EDIT	CANT_SPIN_EDIT_FORM_MEDICIONES + CANT_SPIN_EDIT_FORM_PARAMETROS + CANT_SPIN_EDIT_FORM_CONFIG
#define	CANT_PROGBAR		CANT_PROG_BAR_FORM_CONFIG

#define MSEG_PANT_PRESENTA	2000

//Defines de posiciones en pantalla
//Offsets de Pantallas
#define OFFSETY_PANT_INICIO 0

//Display Virtual
#define	ALTO_DISP_VIRT		256
#define	ANCHO_DISP_VIRT		256


//extern union Estado objetosPresenta[CANT_OBJ_FORM_PRESENTA];
//extern union Estado objetosInicio[CANT_OBJ_FORM_INICIO];
//extern union Estado objetosMediciones[CANT_OBJ_FORM_MEDICIONES];
//extern union Estado objetosParametros[CANT_OBJ_FORM_PARAMETROS];
//extern union Estado objetosConfig[CANT_OBJ_FORM_CONFIG];

extern char cadenaAux[32]; //utilizada en Label, SpinEdit y ValEdit

//Punteros a Struct para pasar valores a funciones
//extern struct dForm 				*ptrForm;
extern struct Form 				*ptrForm;

extern uint16_t contTitileo;	//Contador que sirve para hacer titilar el cursor 
extern union Estado *ptrFoco[CANT_FOCO];
extern unsigned char	pantallaActual;	//Número de pantalla en la que se encuentra el usuario
//extern unsigned char indFocoAnterior;	//Entero con el índice del objeto de la interfaz que se le quito el foco
extern unsigned char indFoco;				//Entero con el índice del objeto de la interfaz que tiene el foco
extern unsigned char indFocoActual;	//Guarda el foco del objeto actual antes de ejecutar su comportamiento predefinido. 
																		//Esta variable sirve para redefinir el comportamiento por defecto del foco

//extern struct ValPropSpinEdit vPSpinEdits[CANT_SPIN_EDIT];
//extern struct ValPropProgBar vPProgBars[CANT_PROGBAR];

extern struct Cargador c;

extern struct Form formPresenta;
extern struct Form formInicio;
extern struct Form formMediciones;
extern struct Form formParametros;
extern struct Form formConfig;


#endif //CONFIGINTERFAZ_H



