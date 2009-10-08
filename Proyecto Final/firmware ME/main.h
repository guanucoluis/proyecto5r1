#ifndef _MAIN_H
	#define _MAIN_H
	#include "p30fxxxx.h" /*El compilador se fija cual es el micro e incluye el header indicado */
	#include <libpic30.h>
	#include "rutinas.h"
	#include "teclado.h"
	#include "LCD.h"
	#include "dsPIC_delay.h"
	#include "timer.h"

//DEFINES RALATIVOS A LAS CARACTERÍSTICAS QUE SE EJECUTARÁN
	//#define EJEC_RESINCRONIZACION

//DEFINES VARIOS	
	#define	Vrefmas											5
	#define	Vrefmenos										0
	#define Si													1
	#define si													1
	#define SI													1
	#define No													0
	#define no													0
	#define NO													0
	#define	Habilitada									1
	#define	Deshabilitada								0

//DEFINES DE CONFIGURACIÓN DE PRIORIDADES
	#define PrioridadT1							1		
	#define PrioridadT2							2	
	#define PrioridadT3							1	
	#define PrioridadT4							1
	#define PrioridadT5							1	
	#define PrioridadINT0						1
	#define PrioridadINT1						1
	#define PrioridadINT2						1
	#define PrioridadAD							3

//DEFINES	RELATIVOS A LOS PERIODOS DE LOS TIMERS
	#define	PeriodoT1								0xFF				
	#define	PeriodoT2								0xFF
	#define	PeriodoT3								625
	#define	PeriodoT4								0xFF

//DEFINES RELATIVOS AL A/D
	#define	MuestPorInt							15						//Cantidad de muestras tomadas antes de interrumpir

//DEFINES RELATIVOS A LAS BASES DE TIEMPO
	#define Tcy													0.0000001
	#define	BaseTCritica								0.001			
	#define	BaseTNormal									0.0008188

//DEFINES Y ESTRUCTURAS RELATIVOS A LOS PROCESOS/RUTINAS

	//Frecuencias de Ejecución de los procesos/rutinas
		#define	FEMuestreo								500					//Frecuencia de ejecución del Muestreo
		#define	FETeclado									166					//Frecuencia de ejecución de la rutina de teclas
		#define	FETeclas									55					//Frecuencia de ejecución de la rutina de teclado
		#define	FEMenu										25					//Frecuencia de ejecución de la rutina de actualización de menu
	
	//Valores Máximos de los Contadores de Espera de procesos/rutinas
		#define CEMenu										( 1 / ( FEMenu * BaseTNormal ) )			//Contador de Espera
		#define CEMuestreo								( 1 / ( FEMuestreo * BaseTCritica ) )
		#define CETeclado									( 1 / ( FETeclado * BaseTNormal ) )
		#define CETeclas									( 1 / ( FETeclas * BaseTNormal ) )
	
	//Variables de los procesos/rutinas
		struct VariablesDeProcesos{
			unsigned 			EjecRutMenu				: 1;
			unsigned 			HabRutMenu				: 1;
			unsigned char ContEspMenu;
			unsigned 			EjecRutTeclado		: 1;
			unsigned 			HabRutTeclado			: 1;
			unsigned char ContEspTeclado;
			unsigned 			EjecRutTeclas			: 1;
			unsigned 			HabRutTeclas			: 1;
			unsigned char ContEspTeclas;
		};	

//DEFINES Y ESTRUCTURAS RELATIVOS AL MENU
	
//BANDERAS DE USO GENERAL
	struct	Banderas{
		
	};

//PROTOTIPOS DE FUNCIONES	

#endif


