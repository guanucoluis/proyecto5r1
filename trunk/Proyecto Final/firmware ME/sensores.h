#include "p30fxxxx.h" /*El compilador se fija cual es el micro e incluye el header indicado */

//DEFINES RELATIVOS A CONSTANTES DEL PROGRAMA

	#define pi			3.141592	
	#define Angulo	    (( 22.5 * 2 * pi ) / 360 )	//angulo expresado en radianes
//	#define Seccion		( Angulo * Radio )		//seccion es S
	#define Cant_Tim_Inst	50					//Cantidad de velocidades instantaneas que quiero tomar para promediar
	#define Tcy									0.0000004



//PROTOTIPOS DE FUNCIONES
	/*Función RutinaSensores-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que calcula las velocidades tomadas por los sensores
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	

		void RutinaSensores ();
