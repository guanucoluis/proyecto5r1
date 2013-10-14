#ifndef INTERFAZ_CFG_H
#define INTERFAZ_CFG_H

#include "interfaz.h"
#include "objetos.h"
#include "configobj.h"

//Defines de las pantallas:
#define	NUM_PANTALLAS       6
#define PANTALLA_PRESENTA   1
#define PANTALLA_INICIO     2
#define PANTALLA_MEDICIONES 3
#define PANTALLA_TARAR      4
#define PANTALLA_PARAMETROS 5
#define PANTALLA_CONFIG     6

#define	CANT_MAX_OBJETOS_PANTALLA   30	//Máxima cantidad de objetos dentro de un Form (pantalla)
#define CANT_MAX_OBJETOS_FOCO       15	//Máxima cantidad de objetos dentro de un Form que pueden tener foco
#define CANT_FOCO CANT_MAX_OBJETOS_FOCO

//Contenidos de los Formularios
#define CANT_LABEL_FORM_PRESENTA    3
#define	CANT_OBJ_FORM_PRESENTA			CANT_LABEL_FORM_PRESENTA

#define CANT_LABEL_FORM_INICIO      1
#define CANT_BUTTON_FORM_INICIO     4
#define	CANT_OBJ_FORM_INICIO				CANT_LABEL_FORM_INICIO + CANT_BUTTON_FORM_INICIO

#define CANT_LABEL_FORM_MEDICIONES        12
#define CANT_BUTTON_FORM_MEDICIONES       2
#define CANT_SPIN_EDIT_FORM_MEDICIONES    12
#define	CANT_CHECK_BOX_FORM_MEDICIONES    1
#define	CANT_OBJ_FORM_MEDICIONES					CANT_LABEL_FORM_MEDICIONES + CANT_BUTTON_FORM_MEDICIONES + CANT_SPIN_EDIT_FORM_MEDICIONES + CANT_CHECK_BOX_FORM_MEDICIONES

#define CANT_LABEL_FORM_TARAR         5
#define CANT_BUTTON_FORM_TARAR        1
#define CANT_SPIN_EDIT_FORM_TARAR     2
#define	CANT_OBJ_FORM_TARAR     			CANT_LABEL_FORM_TARAR + CANT_BUTTON_FORM_TARAR + CANT_SPIN_EDIT_FORM_TARAR

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

#define	CANT_SPIN_EDIT	CANT_SPIN_EDIT_FORM_MEDICIONES + CANT_SPIN_EDIT_FORM_PARAMETROS + CANT_SPIN_EDIT_FORM_CONFIG + CANT_SPIN_EDIT_FORM_TARAR
#define	CANT_PROGBAR		CANT_PROG_BAR_FORM_CONFIG

#define MSEG_PANT_PRESENTA	2000


//Defines de los Mensajes
#define	MENSAJE_SOBRESCRIBIR	0
#define	MENSAJE_INSERTAR_SD		1
#define	MENSAJE_ERROR_SD			2
#define MENSAJE_FIN_ENSAYO    3

//Defines de posiciones en pantalla
//Offsets de Pantallas
#define OFFSETY_PANT_INICIO 0

//Display Virtual
#define	ALTO_DISP_VIRT		256
#define	ANCHO_DISP_VIRT		256

extern struct Form formPresenta;
extern struct Form formInicio;
extern struct Form formMediciones;
extern struct Form formTarar;
extern struct Form formParametros;
extern struct Form formConfig;

//Funciones
void InicInterfaz(void);
void CargarPantalla(void);
void ExtrasDePantalla(void);
void SetFoco(void);

#endif //INTERFAZ_CFG_H



