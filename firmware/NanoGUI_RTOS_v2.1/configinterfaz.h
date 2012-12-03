#ifndef CONFIGINTERFAZ_H
#define CONFIGINTERFAZ_H

#include <objetos.h>

//HABILITACION DE OBJETOS GRAFICOS DE LA BIBLIOTECA
#define FORM
#define LABEL
#define BUTTON
#define CHECK_BOX
#define	COMBO_BOX
#define SPIN_EDIT		//Editor de numeros positivos muy simple
#define VAL_EDIT
#define PROG_BAR
//#define	SVAL_EDIT		//Simple ValEdit. Este ValEdit es mas sencillo y ocupa menos memoria de programa

//Defines de las pantallas:
#define	NUM_PANTALLAS       9	
#define PANTALLA_PRESENTA   1
#define PANTALLA_INICIO     2
#define PANTALLA_ENSAYO     3
#define PANTALLA_COMPOSITE  4
#define PANTALLA_ENSAYO_LIBRE   5
#define PANTALLA_PROGRAMAS      6
#define PANTALLA_CONFIG         7
#define PANTALLA_CONFIG_ENSAYO	8	
#define PANTALLA_EJEC_ENSAYO    9

#define	CANT_MAX_OBJETOS_PANTALLA   30	//Máxima cantidad de objetos dentro de un Form (pantalla)
#define CANT_MAX_OBJETOS_FOCO       15	//Máxima cantidad de objetos dentro de un Form que pueden tener foco
#define CANT_FOCO CANT_MAX_OBJETOS_FOCO

//Contenidos de los Formularios
#define CANT_LABEL_FORM_PRESENTA    4
#define	CANT_OBJ_FORM_PRESENTA			CANT_LABEL_FORM_PRESENTA

#define CANT_LABEL_FORM_INICIO      1
#define CANT_BUTTON_FORM_INICIO     4
#define	CANT_OBJ_FORM_INICIO				CANT_LABEL_FORM_INICIO + CANT_BUTTON_FORM_INICIO

#define CANT_LABEL_FORM_ENSAYO      1
#define CANT_BUTTON_FORM_ENSAYO     2
#define	CANT_OBJ_FORM_ENSAYO				CANT_LABEL_FORM_ENSAYO + CANT_BUTTON_FORM_ENSAYO

#define CANT_LABEL_FORM_COMPOSITE       6
#define CANT_BUTTON_FORM_COMPOSITE      1
#define CANT_SPIN_EDIT_FORM_COMPOSITE   1
#define	CANT_VAL_EDIT_FORM_COMPOSITE    2
#define	CANT_OBJ_FORM_COMPOSITE					CANT_LABEL_FORM_COMPOSITE + CANT_BUTTON_FORM_COMPOSITE + CANT_SPIN_EDIT_FORM_COMPOSITE + CANT_VAL_EDIT_FORM_COMPOSITE

#define CANT_LABEL_FORM_ENSAYO_LIBRE        12
#define CANT_BUTTON_FORM_ENSAYO_LIBRE       2
#define CANT_SPIN_EDIT_FORM_ENSAYO_LIBRE    6
#define	CANT_CHECK_BOX_FORM_ENSAYO_LIBRE    2
#define	CANT_OBJ_FORM_ENSAYO_LIBRE					CANT_LABEL_FORM_ENSAYO_LIBRE + CANT_BUTTON_FORM_ENSAYO_LIBRE + CANT_SPIN_EDIT_FORM_ENSAYO_LIBRE + CANT_CHECK_BOX_FORM_ENSAYO_LIBRE

#define CANT_LABEL_FORM_PROGRAMAS       7
#define CANT_BUTTON_FORM_PROGRAMAS      3
#define CANT_SPIN_EDIT_FORM_PROGRAMAS   5
#define	CANT_COMBO_BOX_FORM_PROGRAMAS   1
#define	CANT_OBJ_FORM_PROGRAMAS					CANT_LABEL_FORM_PROGRAMAS + CANT_BUTTON_FORM_PROGRAMAS + CANT_SPIN_EDIT_FORM_PROGRAMAS + CANT_COMBO_BOX_FORM_PROGRAMAS


#define CANT_LABEL_FORM_CONFIG      3
#define CANT_BUTTON_FORM_CONFIG     1
#define CANT_PROG_BAR_FORM_CONFIG   2
#define	CANT_OBJ_FORM_CONFIG				CANT_LABEL_FORM_CONFIG + CANT_BUTTON_FORM_CONFIG + CANT_PROG_BAR_FORM_CONFIG		

#define CANT_LABEL_FORM_CONFIG_ENSAYO       3
#define CANT_BUTTON_FORM_CONFIG_ENSAYO      1
#define CANT_SPIN_EDIT_FORM_CONFIG_ENSAYO   2
#define	CANT_CHECK_BOX_FORM_CONFIG_ENSAYO   2
#define	CANT_OBJ_FORM_CONFIG_ENSAYO					CANT_LABEL_FORM_CONFIG_ENSAYO + CANT_BUTTON_FORM_CONFIG_ENSAYO + CANT_SPIN_EDIT_FORM_CONFIG_ENSAYO + CANT_CHECK_BOX_FORM_CONFIG_ENSAYO

#define CANT_LABEL_FORM_EJEC_ENSAYO     10
#define CANT_SPIN_EDIT_FORM_EJEC_ENSAYO 8
#define	CANT_OBJ_FORM_EJEC_ENSAYO				CANT_LABEL_FORM_EJEC_ENSAYO + CANT_SPIN_EDIT_FORM_EJEC_ENSAYO

#define	CANT_SPIN_EDIT	CANT_SPIN_EDIT_FORM_COMPOSITE + CANT_SPIN_EDIT_FORM_ENSAYO_LIBRE + CANT_SPIN_EDIT_FORM_PROGRAMAS + CANT_SPIN_EDIT_FORM_CONFIG_ENSAYO + CANT_SPIN_EDIT_FORM_EJEC_ENSAYO
#define	CANT_VAL_EDIT		CANT_VAL_EDIT_FORM_COMPOSITE
#define	CANT_COMBOBOX		CANT_COMBO_BOX_FORM_PROGRAMAS
#define	CANT_PROGBAR		CANT_PROG_BAR_FORM_CONFIG

#define DIG_VAL_EDIT_COMP_DIAM				5
#define DIG_VIS_VAL_EDIT_COMP_DIAM		4
#define DIG_VAL_EDIT_COMP_ESP					5
#define DIG_VIS_VAL_EDIT_COMP_ESP			4

#define MSEG_PANT_PRESENTA	2000

//Defines de posiciones en pantalla
//Offsets de Pantallas
#define OFFSETY_PANT_INICIO 0

//Display Virtual
#define	ALTO_DISP_VIRT		256
#define	ANCHO_DISP_VIRT		256

extern char cadenaAux[32]; //utilizada en Label, SpinEdit y ValEdit

//Punteros a Struct para pasar valores a funciones
//extern struct dForm 				*ptrForm;
extern struct Form 				*ptrForm;

extern volatile unsigned char contTitileo;	//Contador que sirve para hacer titilar el cursor 
extern union Estado *ptrFoco[CANT_FOCO];
extern unsigned char	pantallaActual;	//Número de pantalla en la que se encuentra el usuario
//extern unsigned char indFocoAnterior;	//Entero con el índice del objeto de la interfaz que se le quito el foco
extern unsigned char indFoco;				//Entero con el índice del objeto de la interfaz que tiene el foco
extern unsigned char indFocoActual;	//Guarda el foco del objeto actual antes de ejecutar su comportamiento predefinido. 
																		//Esta variable sirve para redefinir el comportamiento por defecto del foco

extern struct Cargador c;

extern struct Form formPresenta;
extern struct Form formInicio;
extern struct Form formEnsayo;
extern struct Form formComposite;
extern struct Form formEnsayoLibre;
extern struct Form formProgramas;
extern struct Form formConfig;
extern struct Form formConfigEnsayo;
extern struct Form formEjecEnsayo;

extern union Estado objetosPresenta[CANT_OBJ_FORM_PRESENTA];
extern union Estado objetosInicio[CANT_OBJ_FORM_INICIO];
extern union Estado objetosEnsayo[CANT_OBJ_FORM_ENSAYO];
extern union Estado objetosComposite[CANT_OBJ_FORM_COMPOSITE];
extern union Estado objetosEnsayoLibre[CANT_OBJ_FORM_ENSAYO_LIBRE];
extern union Estado objetosProgramas[CANT_OBJ_FORM_PROGRAMAS];
extern union Estado objetosConfig[CANT_OBJ_FORM_CONFIG];
extern union Estado objetosConfigEnsayo[CANT_OBJ_FORM_CONFIG_ENSAYO];
extern union Estado objetosEjecEnsayo[CANT_OBJ_FORM_EJEC_ENSAYO];

extern struct ValPropSpinEdit vPSpinEdits[CANT_SPIN_EDIT];
extern struct ValPropValEdit vPValEdits[CANT_VAL_EDIT];
extern struct ValPropComboBox vPComboBoxes[CANT_COMBOBOX];
extern struct ValPropProgBar vPProgBars[CANT_PROGBAR];

extern unsigned char valEditCompositeDiametro[DIG_VAL_EDIT_COMP_DIAM];
extern unsigned char valEditCompositeEspesor[DIG_VAL_EDIT_COMP_ESP];

#endif //CONFIGINTERFAZ_H



