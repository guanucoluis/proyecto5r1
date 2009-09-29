
//INCLUDES
	#include "dsPIC_delay.h"


//DEFINICI�N DE FUNCIONES
	/*Funci�n Delay_100TCYx-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Esta funci�n realiza una demora de x*100 ciclos de intrucci�n
	Entrada: x: Cantidad de veces que se repite la demora de 100 ciclos de instrucci�n
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
