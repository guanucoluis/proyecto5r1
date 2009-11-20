#ifndef MAIN_H
	#define MAIN_H

	#include "p30fxxxx.h" /*El compilador se fija cual es el micro e incluye el header indicado */
	#include <libpic30.h>
	#include "rutinas.h"
	#include "teclado.h"
	#include "LCD.h"
	#include "dsPIC_delay.h"
	#include "timer.h"
	#include <stdio.h>
	#include "sensores.h"
	#include <dsp.h>
	#include <uart.h>

//DEFINES RALATIVOS A LAS CARACTERÍSTICAS QUE SE EJECUTARÁN
	//#define EJEC_RESINCRONIZACION

//DEFINES VARIOS	
	#define	Vrefmas											5
	#define	Vrefmenos										0
	#define Si												1
	#define si												1
	#define SI												1
	#define No												0
	#define no												0
	#define NO												0
	#define	Habilitada										1
	#define	Deshabilitada									0

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

//DEFINES RELATIVOS A LAS BASES DE TIEMPO
	#define Tcy									0.0000004
	#define TcyAux1								0.001
	#define	TcyAux2								(Tcy / TcyAux1)
	#define	BaseTCritica						0.001			
	#define	BaseTNormal							0.0003004

//DEFINES	RELATIVOS A LOS TIMERS
	#define	PrescalerT1							T1_PS_1_8	
	#define	PeriodoT1								93
	#define PrescalerT2							T2_PS_1_8									
	#define	PeriodoT2								0xFF
	#define PrescalerT3							T3_PS_1_8
	#define	PeriodoT3								3125
	#define PrescalerT4							T4_PS_1_256
	#define	PeriodoT4								14648
	#define PrescalerT5							T5_PS_1_256
	#define	PeriodoT5								14648

//DEFINES RELATIVOS A LOS SENSORES
	#define	Cant_Max_Desborde_Trac				10
	#define	Cant_Max_Desborde_Maq					10
	#define Tamanio_Buffer_Fuerza					100
	#define Cant_Muest_Por_Int						16

//DEFINES RELATIVOS AL A/D
	//define	MuestPorInt									15						//Cantidad de muestras tomadas antes de interrumpir

//DEFINES Y ESTRUCTURAS RELATIVOS A LOS PROCESOS/RUTINAS

	//Frecuencias de Ejecución de los procesos/rutinas
		#define	FEMuestreo								500					//Frecuencia de ejecución del Muestreo
		#define	FETeclado								166					//Frecuencia de ejecución de la rutina de teclas
		#define	FETeclas								55					//Frecuencia de ejecución de la rutina de teclado
		#define	FEMenu									10					//Frecuencia de ejecución de la rutina de actualización de menu

	
	//Defines Máximos de los Contadores de Espera de procesos/rutinas
		#define CEMenu										( 1 / ( FEMenu * BaseTNormal ) )			//Contador de Espera
		#define CEMuestreo								( 1 / ( FEMuestreo * BaseTCritica ) )
		#define CETeclado									( 1 / ( FETeclado * BaseTNormal ) )
		#define CETeclas									( 1 / ( FETeclas * BaseTNormal ) )

	//Defines relativas al filtrado
		//#define BLOCK_LENGTH    130 //256             /*We will filter a block of 256 samples in this example*/



	//Variables de los procesos/rutinas
		struct VariablesDeProcesos{
			unsigned 			EjecRutFiltrado			: 1;
			unsigned 			HabRutFiltrado			: 1;
			unsigned int 		ContEspFiltrado;
			unsigned 			EjecRutPuertoSerie	: 1;
			unsigned 			HabRutPuertoSerie		: 1;
			unsigned int 		ContEspPuertoSerie;
			unsigned 			EjecRutCalFuerza		: 1;
			unsigned 			HabRutCalFuerza			: 1;
			unsigned int 		ContEspCalFuerza;
			unsigned			EjecRutSensores			: 1;
			unsigned			HabRutSensores			: 1;
			unsigned int		ContEspSensores;
			unsigned 			EjecRutMenu				: 1;
			unsigned 			HabRutMenu				: 1;
			unsigned int 		ContEspMenu;
			unsigned 			EjecRutTeclado			: 1;
			unsigned 			HabRutTeclado			: 1;
			unsigned int 		ContEspTeclado;
			unsigned 			EjecRutTeclas			: 1;
			unsigned 			HabRutTeclas			: 1;
			unsigned int 		ContEspTeclas;
		};	


//DEFINES Y ESTRUCTURAS RELATIVOS AL MENU
	
//BANDERAS DE USO GENERAL
	struct	Banderas{
		
	};
	//Banderas de los sensores

	struct Sensores{
	unsigned	Vel_Trac_Min			:	1;
	unsigned	Vel_Maq_Min				:	1;
	unsigned	Band_Maq				:	1;
	unsigned	Band_Trac				:	1;
	unsigned	Buffer_Completo_Maq		:	1;
	unsigned 	Buffer_Completo_Trac	:	1;
	};

//PROTOTIPOS DE FUNCIONES	

#endif


