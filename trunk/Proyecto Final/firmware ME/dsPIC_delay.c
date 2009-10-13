
//INCLUDES
	#include "dsPIC_delay.h"


//DEFINICIÓN DE FUNCIONES
	/*Función Delay_3_6useg-----------------------------------------------------------------------------------------------------------------------
	Descripción: Esta función realiza una demora de, más o menos, 3,6 useg.
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void Delay_3_6useg()
		{
			Nop();
		}

	/*Función Delay_10useg-----------------------------------------------------------------------------------------------------------------------
	Descripción: Esta función realiza una demora de, más o menos, 10 useg.
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void Delay_10useg()
		{
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
			Nop();
		}

	/*Función Delay_100useg-----------------------------------------------------------------------------------------------------------------------
	Descripción: Esta función realiza una demora de, más o menos, 100 useg.
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void Delay_100useg()
		{
			char i;
			for(i=0;i<39;i++)
				Nop();
		}

	/*Función Delay_x100useg-----------------------------------------------------------------------------------------------------------------------
	Descripción: Esta función realiza una demora de, más o menos, x*100 useg. Es muy imprecisa, jeje
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

	