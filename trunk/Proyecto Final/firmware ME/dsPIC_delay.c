
//INCLUDES
	#include "dsPIC_delay.h"


//DEFINICI�N DE FUNCIONES
	/*Funci�n Delay_x100useg-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Esta funci�n realiza una demora de, m�s o menos, x*100 useg. Es muy imprecisa, jeje
	Entrada: x: Cantidad de veces que se repite la demora de 100 useg
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void Delay_x100useg(int x)
		{
			int i;
			while(x!=0)
			{
				for(i=0;i<37;i++)
					Nop();
				x--;
			}
		}
