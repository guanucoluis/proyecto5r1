#ifndef RUTINAS_H
	#define RUTINAS_H

//INCLUDES

//DEFINES RELATIVOS A CONSTANTES DEL PROGRAMA
	//#define	_CANT_MAX_MEDICIONES	10
	#define _Max_Bytes_Libres		30500
	#define	Volts_Por_Bit				0.0012207
	#define	Kgf_Por_Volt				55
	//#define Kte								0
	#define	Vel_Min							0.0849 //[Km/h]			
 
//DEFINES RELATIVOS A LOS MENUS
	#define	Menu_TomarMedicion		0
	#define	Menu_Tarar						1	
	#define	Menu_Borrar						2
	#define Terminar_Medicion     3
	#define Guardar_en						4
	#define Medicion_ok						5
	#define Tarar_Preg						6
	#define Borrar_Medicion				7
	#define Borrado_ok						8
	#define Menu_Avanzado					9
	#define Radio_Trac						10
	#define Radio_Maq							11
	#define Ingresar_Radio_Trac		12
	#define Ingresar_Radio_Maq		13
	

	#define Cant_Max_Med			50		//Maximo valor de mediciones posibles
	#define Delay_Refresco		3
	#define Radio_Max					99

	struct Med{
		unsigned	Usado						:1;
		unsigned 	Cant_Muestras		:15;
	};

//PROTOTIPOS DE FUNCIONES
	/*Funci�n Rutina_Tecla_OK-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla OK
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_OK();

	/*Funci�n Rutina_Tecla_Cancelar-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Cancelar
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Cancelar();

	/*Funci�n Rutina_Tecla_Arriba-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Arriba
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Arriba();

	/*Funci�n Rutina_Tecla_Abajo-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Abajo
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Abajo();

	/*Funci�n Rutina_Tecla_Derecha-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Derecha
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Derecha();

	/*Funci�n Rutina_Tecla_Izquierda-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que atiende la pulsaci�n de la Tecla Izquierda
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Izquierda();
		
	/*Funci�n RutinaMenu-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina encargada de graficar el texto que corresponda en el LCD
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutinaMenu();

	/*Funci�n RutCalFuerza()-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina encargada de calcular el buffer de fuerza y la fuerza promedio
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutCalFuerza();

	/*Funci�n RutCalFuerza()-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina encargada de calcular el buffer de fuerza y la fuerza promedio
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutinaPuertoSerie();

	/*Funci�n Filtrado-----------------------------------------------------------------------------------------------------------------------
	Descripci�n: Rutina que realiza el filtrado de las muestras tomadas del AD
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutinaFiltrado();

#endif 
