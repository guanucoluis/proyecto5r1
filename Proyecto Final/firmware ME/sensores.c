//INCLUDES
	#include "sensores.h" 

//DECLARACION DE VARIABLES
	//Variables relativas a la velocidad
		volatile unsigned float Vel_Inst_Trac = 0;	//Velocidad instantanea del tractor
		volatile unsigned float Vel_Inst_Maq = 0;	//Velocidad instantanea de la maquina
		volatile unsigned float Vel_Prom_Trac = 0;	//Velocidad promedio del tractor
		volatile unsigned float Vel_Prom_Maq = 0;	//Velocidad promedio de la maquina
		volatile unsigned float Vel_Ang_Trac = 0;		//Velocidad angular instantanea del tractor
		volatile unsigned float Vel_Ang_Maq = 0;		//Velocidad angular instantanea de la maquina


//DEFINICION DE FUNCIONES
