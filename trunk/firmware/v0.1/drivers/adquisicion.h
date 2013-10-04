#ifndef ADQUISICION_H
#define ADQUISICION_H

#include <ucos_ii.h>
#include <globals.h>

//#define PERIODO_MIN_ADQUI 100
#define PERIODO_MUESTREO 	1000

#define ENSAYO_SIN_DURACION 99 //Define utilizado para indicar que no se debe finalizar el ensayo cuando este es sin duracion

//Estructura de tiempo
#ifndef TIEMPO
#define TIEMPO
extern struct Tiempo{
	unsigned int 	ms;		//Milisegundos
	unsigned char seg;	//Segundos
	unsigned char min;	//Minutos
	unsigned char hs;		//Horas
};
#endif

//Estructuras
struct Adquisicion{

	unsigned bGuardarEnSD			:1;		//Indica si los datos de cada muestra deben ser guardados en la SD
	unsigned bMuestreando			:1;		//Indica si el m�dulo se encuentra en proceso de muestreo
	unsigned bGuardarMuestra	:1;		//Indica si hay que enviar una nueva muestra a la SD
	unsigned bGuardandoEnSD		:1;		//Esta bandera sirve como sem�foro para la SD
	
	OS_EVENT	*msgGuardarMuestra;	//Manejador del mensaje que ordena a la Tarea de Adquisicion calcular y almacenar en SD una nueva muestra

	uint8_t numMedActual;	//Indica el n�mero de medici�n con el que se est� trabajando actualmente
	uint16_t nroMuestra;		//N�mero de la muestra actual

	uint16_t contMuestreo;		//Contador para el per�odo de Muestreo
	uint16_t periodoMuestreo;	//Per�odo de Muestreo
};

struct Ensayo{
	unsigned bEnsayando	:1;	//Indica si actualmente se est� realizando un ensayo
  unsigned bIniciarEnsayo :1; //Indica si es necesario iniciar un nuevo ensayo
  unsigned bTerminarEnsayo :1; //Indica cuando se debe terminar el ensayo que se est� ejecutando
	unsigned tipoEnsayo	:2;	//Indica el tipo de ensayo, Libre o Programado

  struct Tiempo duracion;
  //unsigned int duracion;		//Duraci�n del ensayo libre
};

//Variables
extern struct Adquisicion adqui;
extern struct Ensayo ensayo;

//Prototipos
void InicAdquisicion(void);

#endif //ADQUISICION_H

