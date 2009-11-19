//INCLUDES
	#include "sensores.h" 
	#include <stdio.h>
	#include "main.h"

//DECLARACION DE VARIABLES
	//Variables relativas a la velocidad
		volatile int Timer_Inst_Trac[Cant_Tim_Inst] = {0};	//Velocidad instantanea del tractor
		volatile int Timer_Inst_Maq[Cant_Tim_Inst] = {0};		//Velocidad instantanea de la maquina
		volatile long int Timer_Prom_Trac	    	= 0;	//Velocidad promedio del tractor
		volatile long int Timer_Prom_Maq			    = 0;	//Velocidad promedio de la maquina
		volatile float Vel_Prom_Trac = 0;		
		volatile float Vel_Prom_Maq = 0;
		extern volatile unsigned char Indice_Buffer_Maq;
		extern volatile unsigned char Indice_Buffer_Trac;
		volatile unsigned char  indice;					//Lleva el indice de los for	
		extern struct Sensores Band_Sensor;		//inicializo la estructura
		volatile unsigned char  Cant_Elem_Usados_Maq;
		volatile unsigned char  Cant_Elem_Usados_Trac;
		extern volatile unsigned char Radio_Tractor;
		extern volatile unsigned char Radio_Maquina;
		volatile float Seccion_Trac = 0;
		volatile float Seccion_Maq = 0;


//DEFINICION DE FUNCIONES
		void RutinaSensores()
		{	
		
			
			Timer_Prom_Maq=0;	
			if (Band_Sensor.Vel_Maq_Min != 1)
				for(indice=0; indice < Cant_Elem_Usados_Maq; indice++)
					Timer_Prom_Maq = Timer_Prom_Maq + Timer_Inst_Maq[indice];
			else
				for(indice=0; indice < Cant_Tim_Inst; indice++)
					Timer_Inst_Maq[indice] = 0;
			
			Timer_Prom_Maq = (float)((float) Timer_Prom_Maq / (float)Cant_Elem_Usados_Maq);
			
			Timer_Prom_Trac=0;
			if (Band_Sensor.Vel_Trac_Min != 1)
				for(indice=0; indice < Cant_Elem_Usados_Trac; indice++)
					Timer_Prom_Trac = Timer_Prom_Trac + Timer_Inst_Trac[indice];
 			else		
				for(indice=0; indice < Cant_Tim_Inst; indice++)
					Timer_Inst_Trac[indice] = 0;

			Timer_Prom_Trac = (float)((float)Timer_Prom_Trac / (float) Cant_Elem_Usados_Trac);
			
			Seccion_Maq = (float) Radio_Maquina * (float) Angulo * 0.01; 				//la multiplicacion por 0.01 se hace para pasar el valor a metros ya que el radio viene en cm

			Seccion_Trac = (float) Radio_Tractor * (float) Angulo * 0.01; 				//la multiplicacion por 0.01 se hace para pasar el valor a metros ya que el radio viene en cm
			
			Vel_Prom_Maq = (float) (Seccion_Maq / (float)((float) Tcy * (float) Timer_Prom_Maq));
			Vel_Prom_Trac =(float) (Seccion_Trac /(float)((float) Tcy * (float) Timer_Prom_Trac));
		}

