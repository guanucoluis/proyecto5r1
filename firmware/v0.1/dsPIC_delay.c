
//INCLUDES
	#include "dsPIC_delay.h"


//DEFINICI�N DE FUNCIONES
	/*Funci�n DelayTcy-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Esta funci�n realiza una demora de "ciclos" ciclos
	Entrada: 
		INT16U ciclos: n�mero de ciclos de demora
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
	void DelayTcy(INT16U ciclos)
	{
		INT16U i;
		for	(i=0;i<ciclos;i++)
			Nop();
	}	

	/*Funci�n Delay_3_6useg-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Esta funci�n realiza una demora de, m�s o menos, 3,6 useg.
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void Delay_3_6useg()
		{
			Nop();
		}

	/*Funci�n Delay_10useg-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Esta funci�n realiza una demora de, m�s o menos, 10 useg.
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

	/*Funci�n Delay_100useg-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Esta funci�n realiza una demora de, m�s o menos, 100 useg.
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/
		void Delay_100useg()
		{
			char i;
			for(i=0;i<39;i++)
				Nop();
		}

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
	