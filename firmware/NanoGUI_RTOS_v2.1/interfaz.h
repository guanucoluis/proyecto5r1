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
#include "configinterfaz.h"	

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

