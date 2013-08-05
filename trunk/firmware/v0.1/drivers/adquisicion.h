#ifndef ADQUISICION_H
#define ADQUISICION_H

#include <ucos_ii.h>
#include <globals.h>

#define PERIODO_MIN_ADQUI 100
#define PERIODO_MUESTREO 	500

//Estructuras
struct Adquisicion{

	unsigned bGuardarEnSD			:1;		//Indica si los datos de cada muestra deben ser guardados en la SD
	unsigned bMuestreando			:1;		//Indica si el módulo se encuentra en proceso de muestreo
	unsigned bGuardarMuestra	:1;		//Indica si hay que enviar una nueva muestra a la SD
	unsigned bGuardandoEnSD		:1;		//Esta bandera sirve como semáforo para la SD
	
	OS_EVENT	*msgGuardarMuestra;	//Manejador del mensaje que ordena a la Tarea de Adquisicion calcular y almacenar en SD una nueva muestra

	uint8_t numMedActual;	//Indica el número de medición con el que se está trabajando actualmente
	uint16_t nroMuestra;		//Número de la muestra actual

	uint16_t contMuestreo;		//Contador para el período de Muestreo
	uint16_t periodoMuestreo;	//Período de Muestreo
};

struct Ensayo{
	unsigned bEnsayando	:1;	//Indica si actualmente se está realizando un ensayo
	unsigned tipoEnsayo	:2;	//Indica el tipo de ensayo, Libre o Programado

	unsigned int duracion;		//Duración del ensayo libre
};

//Variables
extern struct Adquisicion adqui;
extern struct Ensayo ensayo;

//Prototipos
void InicAdquisicion(void);

#endif //ADQUISICION_H

