
//INCLUDES
	#include <stdio.h>	
	#include "sensores.h"

//DECLARACION DE VARIABLES
	//valores para test
		extern volatile float Vel_Prom_Trac;		
		extern volatile float Vel_Prom_Maq;	

		volatile unsigned char Radio_Tractor = 7;
		volatile unsigned char Radio_Maquina = 7;
		volatile unsigned char Var_Radio = 1;

	//Variables relativas a la Fuerza
		volatile unsigned char i_RCF;
		volatile unsigned char i_ADCI;
		volatile unsigned int i_Buffer_Muestras;
		volatile unsigned int i_Buffer_Muestras_Aux;

		volatile float FuerzaPromedio = 0;
		volatile unsigned int *ptrBufferMuestras;
		volatile unsigned long int SumatoriaFuerza;
		volatile float Offset = 0;

	//Variables de Procesos/Rutinas
		extern struct VariablesDeProcesos Proc;

		//volatile struct Med Mediciones[Cant_Max_Med];	//Inicializo la estructura Med.
		extern volatile struct Sensores Band_Sensor;
                                       

	/*Función RutCalFuerza()-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina encargada de calcular el buffer de fuerza y la fuerza promedio
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutCalFuerza()
		{

			/*//Calcular la Fuerza promedio
				SumatoriaFuerza = 0;
				if(i_Buffer_Muestras == 0)
					i_Buffer_Muestras_Aux = Tamanio_Buffer_Fuerza - Cant_Muest_Por_Int;
				else
					i_Buffer_Muestras_Aux = i_Buffer_Muestras - Cant_Muest_Por_Int;
				for(i_RCF=0;i_RCF<Cant_Muest_Por_Int;i_RCF++)
				{
					SumatoriaFuerza = SumatoriaFuerza + BufferMuestras[i_Buffer_Muestras_Aux];
					if (i_Buffer_Muestras_Aux >= Tamanio_Buffer_Fuerza)
						i_Buffer_Muestras_Aux = 0;
					else
						i_Buffer_Muestras_Aux++;
				}
			FuerzaPromedio = (float) ((float) SumatoriaFuerza / (float) Cant_Muest_Por_Int);
			FuerzaPromedio = (float) ((float) FuerzaPromedio * (float) Volts_Por_Bit * (float) Kgf_Por_Volt);
			FuerzaPromedio = FuerzaPromedio - Offset;*/

			////////////
			//FuerzaPromedio = (float) ((float) BufferMuestras[0] * (float) Volts_Por_Bit * (float) Kgf_Por_Volt);
			//FuerzaPromedio = FuerzaPromedio - Offset;
			////////////

		}
		
		