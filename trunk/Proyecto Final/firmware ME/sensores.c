//INCLUDES
	#include "sensores.h" 
	#include <stdio.h>
	#include "main.h"

//DECLARACION DE VARIABLES
	//Variables relativas a la velocidad
		volatile long int Timer_Inst_Trac[Cant_Tim_Inst];	//Velocidad instantanea del tractor
		volatile long int Timer_Inst_Maq[Cant_Tim_Inst];		//Velocidad instantanea de la maquina
		volatile float Timer_Prom_Trac	    	= 0;	//Velocidad promedio del tractor
		volatile float Timer_Prom_Maq			    = 0;	//Velocidad promedio de la maquina
		volatile float Vel_Prom_Trac = 0;		
		volatile float Vel_Prom_Maq = 0;
	//	extern volatile unsigned char Per_TotalT5;
	//	extern volatile unsigned char Per_TotalT4;
		extern volatile unsigned char Indice_Buffer_Maq;
		extern volatile unsigned char Indice_Buffer_Trac;
		volatile unsigned char  indice;					//Lleva el indice de los for
		extern struct Sensores Band_Sensor;		//inicializo la estructura



//DEFINICION DE FUNCIONES
		void RutinaSensores()
		{	
		
			
			Timer_Prom_Maq=0;	
			if (Band_Sensor.Vel_Maq_Min != 1)
				for(indice=0; indice < Cant_Tim_Inst; indice++)
					Timer_Prom_Maq = Timer_Prom_Maq + Timer_Inst_Maq[indice];
			else
				Timer_Inst_Maq[Indice_Buffer_Maq] = 0;
			
			Timer_Prom_Maq = (float)((float) Timer_Prom_Maq / (float)Cant_Tim_Inst);
			
			Timer_Prom_Trac=0;
			if (Band_Sensor.Vel_Trac_Min != 1)
				for(indice=0; indice < Cant_Tim_Inst; indice++)
					Timer_Prom_Trac = Timer_Prom_Trac + Timer_Inst_Trac[indice];
 			else		
				Timer_Inst_Trac[Indice_Buffer_Trac] = 0;

			Timer_Prom_Trac = (float)((float)Timer_Prom_Trac / (float)Cant_Tim_Inst);

			Vel_Prom_Maq = (float) (Seccion / (float)((float) Tcy * (float) Timer_Prom_Maq));
			Vel_Prom_Trac =(float) (Seccion /(float)((float) Tcy * (float) Timer_Prom_Trac));
		}

