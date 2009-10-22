//INCLUDES
	#include "rutinas.h"	

//DECLARACION DE VARIABLES
	//Variables de Men�s
		volatile char *ptrMenuActual;
		volatile char MenuPrinc[5][17]={	"Tomar Medicion  ",
																			"Tarar           ",
																			"Configuracion   ",
																			"Tarar?          ",
																			"CANCELAR      OK"};
		volatile char MenuSeleccionado = 1; 

//DEFINICI�N DE FUNCIONES
	/*Funci�n BinABCD-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que convierte 
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/		
		void BinABCD(void)
		{
			
		}

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
					MenuSeleccionado = Menu_Tarar;
					break;
				case Menu_Tarar: 
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
				case Menu_Tarar: 
					MenuSeleccionado = Menu_TomarMedicion;
					break;
				case Menu_Configuracion:
					MenuSeleccionado = Menu_Tarar;
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
			//Limpiar Display
				LimpiarLCD();

			//Parte SUPERIOR del Display
				ptrMenuActual = &(MenuPrinc[MenuSeleccionado][0]);
				PrintfLCDXY(0,0,ptrMenuActual);
			
			//Parte INFERIOR del Display
				ptrMenuActual = &(MenuPrinc[MenuSeleccionado][0]);
				PrintfLCDXY(0,0,ptrMenuActual);
		}
