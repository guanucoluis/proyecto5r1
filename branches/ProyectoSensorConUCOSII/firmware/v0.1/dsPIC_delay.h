#ifndef DELAY_H
	#define DELAY_H

//INCLUDES
//#include "p30fxxxx.h"
#include "os_cpu.h"

//PROTOTIPOS DE FUNCIONES

/*Función DelayTcy-----------------------------------------------------------------------------------------------------------------------
Descripción: Esta función realiza una demora de "ciclos" ciclos
Entrada: 
	INT16U ciclos: número de ciclos de demora
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/
void DelayTcy(INT16U ciclos);

/*Función Delay_3_6useg-----------------------------------------------------------------------------------------------------------------------
Descripción: Esta función realiza una demora de, más o menos, 3,6 useg.
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/
void Delay_3_6useg();

/*Función Delay_10useg-----------------------------------------------------------------------------------------------------------------------
Descripción: Esta función realiza una demora de, más o menos, 10 useg.
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/
void Delay_10useg();

/*Función Delay_100useg-----------------------------------------------------------------------------------------------------------------------
Descripción: Esta función realiza una demora de, más o menos, 100 useg.
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/
void Delay_100useg();

/*Función Delay_x100useg-----------------------------------------------------------------------------------------------------------------------
Descripción: Esta función realiza una demora de, más o menos, x*100 useg. Es muy imprecisa, jeje
Entrada: x: Cantidad de veces que se repite la demora de 100 useg
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/
void Delay_x100useg(int x);

#endif


