#include "p30fxxxx.h" /*El compilador se fija cual es el micro e incluye el header indicado */

//DEFINES RELATIVOS A CONSTANTES DEL PROGRAMA

	#define pi			3.141592	
	#define Angulo		(22.5 * pi)				//angulo expresado en radianes
	#define Radio		0.0071					//radio en metros
	#define Seccion		(Angulo * Radio)		//seccion es S
	#define Cant_Vel_Inst	10					//Cantidad de velocidades instantaneas que quiero tomar para promediar



//PROTOTIPOS DE FUNCIONES
	/*Función RutinaSensores-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que calcula las velocidades tomadas por los sensores
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	

		void RutinaSensores ();
