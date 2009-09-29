
//INCLUDES
	#include "dsPIC_delay.h"


//DEFINICIÓN DE FUNCIONES
	/*Función Delay_100TCYx-----------------------------------------------------------------------------------------------------------------------
	Descripción: Esta función realiza una demora de x*100 ciclos de intrucción
	Entrada: x: Cantidad de veces que se repite la demora de 100 ciclos de instrucción
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void Delay_100TCYx(int x)
		{
			int i;
			while(x!=0)
			{
				for(i=0;i<3030;i++)
					Nop();
				x--;
			}
		}
