#ifndef TECLADO_H
	#define TECLADO_H

//INCLUDES
	#include "p30fxxxx.h"
	#include "dsPIC_delay.h"
	#include "rutinas.h"

//DEFINES RELATIVOS AL TECLADO

	//Defines Generales
		#define NumColum			3					//Numero de columnas del teclado
		#define NumFilas			2					//Numero de filas del teclado
 		#define Antirrebote 	20				//Indica la cantidad de veces que una tecla debe ser detectada para ser tomada como válida

	//Valores asignados a cada tecla
		#define Tecla_No_Pres			100
		#define Tecla_OK	 				2
		#define	Tecla_Cancelar		5
		#define Tecla_Derecha 		0
		#define Tecla_Izquierda 	4
		#define Tecla_Arriba 			3	
		#define Tecla_Abajo	 			1

	//Salidas del teclado
		#define	Salida0						PORTBbits.RB8
		#define	Salida1						PORTBbits.RB9
		#define	Salida2						PORTBbits.RB10

	//Entradas del teclado
		#define	Entrada0					PORTBbits.RB11
		#define	Entrada1					PORTBbits.RB12

//PROTOTIPOS DE FUNCIONES
	/*Función/Rutina Teclado------------------------------------------------------------------------------------------------------------------------
	Descripción: 	Descripción: Rutina que barre el teclado matricial buscando cual tecla ha sido presionada. Y luego asigna a Tecla_Presionada el valor de la tecla presionada 
	Entrada: nada
	Salida: nada
	//-------------------------------------------------------------------------------------------------------------------------------------*/
		void RutinaTeclado(void);

	/*Función/Rutina Teclas------------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que evalúa el valor de Tecla_Presionada (la tecla que actualmente está siendo presionada) y toma una acción en función de ésta 
	Entrada: nada
	Salida: nada
	//-------------------------------------------------------------------------------------------------------------------------------------*/
		void RutinaTeclas(void);

#endif
