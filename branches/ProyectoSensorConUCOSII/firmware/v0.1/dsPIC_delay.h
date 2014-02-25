#ifndef DELAY_H
	#define DELAY_H

//INCLUDES
//#include "p30fxxxx.h"
#include "os_cpu.h"

//PROTOTIPOS DE FUNCIONES

/*Funci�n DelayTcy-----------------------------------------------------------------------------------------------------------------------
Descripci�n: Esta funci�n realiza una demora de "ciclos" ciclos
Entrada: 
	INT16U ciclos: n�mero de ciclos de demora
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/
void DelayTcy(INT16U ciclos);

/*Funci�n Delay_3_6useg-----------------------------------------------------------------------------------------------------------------------
Descripci�n: Esta funci�n realiza una demora de, m�s o menos, 3,6 useg.
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/
void Delay_3_6useg();

/*Funci�n Delay_10useg-----------------------------------------------------------------------------------------------------------------------
Descripci�n: Esta funci�n realiza una demora de, m�s o menos, 10 useg.
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/
void Delay_10useg();

/*Funci�n Delay_100useg-----------------------------------------------------------------------------------------------------------------------
Descripci�n: Esta funci�n realiza una demora de, m�s o menos, 100 useg.
Entrada: nada
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/
void Delay_100useg();

/*Funci�n Delay_x100useg-----------------------------------------------------------------------------------------------------------------------
Descripci�n: Esta funci�n realiza una demora de, m�s o menos, x*100 useg. Es muy imprecisa, jeje
Entrada: x: Cantidad de veces que se repite la demora de 100 useg
Salida: nada
//------------------------------------------------------------------------------------------------------------------------*/
void Delay_x100useg(int x);

#endif


