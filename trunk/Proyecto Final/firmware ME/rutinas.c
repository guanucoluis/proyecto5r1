//INCLUDES
	#include "rutinas.h"	

//DECLARACION DE VARIABLES
	//Variables de Men�s
		volatile char *ptrMenuActual;
		volatile char MenuPrinc[4][17]={	"Tomar Medicion  ",
																			"Borrar Medicion ",
																			"Enviar a PC     ",
																			"Configuracion   "};
		volatile char MenuSeleccionado = 1; 

//DEFINICI�N DE FUNCIONES
	/*Funci�n Rutina_Tecla_OK-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla OK
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_OK()
		{
			
		}

	/*Funci�n Rutina_Tecla_Cancelar-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Cancelar
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Cancelar()
		{
			
		}

	/*Funci�n Rutina_Tecla_Arriba-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Arriba
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Arriba()
		{
			
		}

	/*Funci�n Rutina_Tecla_Abajo-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Abajo
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Abajo()
		{
			
		}

	/*Funci�n Rutina_Tecla_Derecha-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Derecha
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Derecha()
		{
			switch (MenuSeleccionado) // �En que men� estoy?
			{
				//Grupo del Menu principal
				case Menu_TomarMedicion:
					MenuSeleccionado = Menu_BorrarMedicion;
					break;
				case Menu_BorrarMedicion: 
					MenuSeleccionado = Menu_EnviarAPC;
					break;
				case Menu_EnviarAPC: 
					MenuSeleccionado = Menu_Configuracion;
					break;
				case Menu_Configuracion:
					MenuSeleccionado = Menu_TomarMedicion;
					break;
			}
		}

	/*Funci�n Rutina_Tecla_Izquierda-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Izquierda
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Izquierda()
		{
			switch (MenuSeleccionado) // �En que men� estoy?
			{
				//Grupo del Menu principal
				case Menu_TomarMedicion:
					MenuSeleccionado = Menu_Configuracion;
					break;
				case Menu_BorrarMedicion: 
					MenuSeleccionado = Menu_TomarMedicion;
					break;
				case Menu_EnviarAPC: 
					MenuSeleccionado = Menu_BorrarMedicion;
					break;
				case Menu_Configuracion:
					MenuSeleccionado = Menu_EnviarAPC;
					break;
			}
		}

	/*Funci�n RutinaMenu-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina encargada de graficar el texto que corresponda en el LCD
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutinaMenu()
		{
			LimpiarLCD();
			ptrMenuActual = &(MenuPrinc[MenuSeleccionado][0]);
			PrintfLCDXY(0,0,ptrMenuActual);
		}
