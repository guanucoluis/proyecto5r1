//INCLUDES
	#include "sensores.h" 
	#include <stdio.h>
	#include "main.h"

//DECLARACION DE VARIABLES
	//Variables relativas a la velocidad
		volatile float Vel_Inst_Trac[Cant_Vel_Inst];	//Velocidad instantanea del tractor
		volatile float Vel_Inst_Maq[Cant_Vel_Inst];	//Velocidad instantanea de la maquina
		volatile float Vel_Prom_Trac = 0;	//Velocidad promedio del tractor
		volatile float Vel_Prom_Maq = 0;	//Velocidad promedio de la maquina
		extern volatile unsigned char Per_TotalT5;
		extern volatile unsigned char Per_TotalT4;
		extern volatile unsigned char Indice_Buffer_Maq;
		extern volatile unsigned char Indice_Buffer_Trac;
		volatile unsigned char  indice;					//Lleva el indice de los for


//DEFINICION DE FUNCIONES
		void RutinaSensores()
		{
			Vel_Inst_Maq[Indice_Buffer_Maq] = Seccion / Per_TotalT4;
			Vel_Inst_Trac[Indice_Buffer_Trac] = Seccion / Per_TotalT5;

			for(indice=0; indice < Cant_Vel_Inst; indice++)
				{
				Vel_Prom_Maq =+ (Vel_Inst_Maq[indice] / Cant_Vel_Inst);
				if(Vel_Prom_Maq > 99)
					Vel_Prom_Maq = 99;
				}
			for(indice=0; indice < Cant_Vel_Inst; indice++)
				{
				Vel_Prom_Trac =+ (Vel_Inst_Trac[indice] / Cant_Vel_Inst);
				if(Vel_Prom_Trac > 99)
					Vel_Prom_Trac = 99;
				}

		}
