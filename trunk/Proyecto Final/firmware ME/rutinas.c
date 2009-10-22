//INCLUDES
	#include "rutinas.h"	

//DECLARACION DE VARIABLES
	//Variables de Menús
		volatile char *ptrMenuActual;
		volatile char MenuPrinc[5][17]={	"Tomar Medicion  ",
																			"Tarar           ",
																			"Configuracion   ",
																			"Tarar?          ",
																			"CANCELAR      OK"};
		volatile char MenuSeleccionado = 1; 

//DEFINICIÓN DE FUNCIONES
	/*Función BinABCD-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que convierte 
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/		
		void BinABCD(void)
		{
			
		}

	/*Función Rutina_Tecla_OK-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla OK
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_OK()
		{
			
		}

	/*Función Rutina_Tecla_Cancelar-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Cancelar
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Cancelar()
		{
			
		}

	/*Función Rutina_Tecla_Arriba-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Arriba
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Arriba()
		{
			
		}

	/*Función Rutina_Tecla_Abajo-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Abajo
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Abajo()
		{
			
		}

	/*Función Rutina_Tecla_Derecha-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Derecha
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Derecha()
		{
			switch (MenuSeleccionado) // ¿En que menú estoy?
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

	/*Función Rutina_Tecla_Izquierda-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Izquierda
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Izquierda()
		{
			switch (MenuSeleccionado) // ¿En que menú estoy?
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

	/*Función RutinaMenu-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina encargada de graficar el texto que corresponda en el LCD
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
