#ifndef _RUTINAS_H
	#define _RUTINAS_H
//INCLUDES

//DEFINES RELATIVOS A CONSTANTES DEL PROGRAMA
	//#define	_CANT_MAX_MEDICIONES	10
	#define _Max_Bytes_Libres		30500
	#define	Volts_Por_Bit			0.0012207
	#define	Kgm_Por_Volt			874.3
	//#define Kte							0
	#define	Vel_Min						0.0849 //[Km/h]			
 
//DEFINES RELATIVOS A LOS MENUS
	#define	Menu_TomarMedicion		0
	#define	Menu_Tarar				1	
	#define	Menu_Borrar				2
	#define Terminar_Medicion       3
	#define Guardar_en				4
	#define Medicion_ok				5
	#define Tarar_Preg				6
	#define Borrar_Medicion			7
	#define Borrado_ok				8
	

	#define Cant_Max_Med			99		//Maximo valor de mediciones posibles

	struct Med{
		unsigned	 Usado			:1;
		unsigned int Cant_Muestras;
	};

//PROTOTIPOS DE FUNCIONES
	/*Función Rutina_Tecla_OK-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla OK
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_OK();

	/*Función Rutina_Tecla_Cancelar-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Cancelar
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Cancelar();

	/*Función Rutina_Tecla_Arriba-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Arriba
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Arriba();

	/*Función Rutina_Tecla_Abajo-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Abajo
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Abajo();

	/*Función Rutina_Tecla_Derecha-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Derecha
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Derecha();

	/*Función Rutina_Tecla_Izquierda-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina que atiende la pulsación de la Tecla Izquierda
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void Rutina_Tecla_Izquierda();
		
	/*Función RutinaMenu-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina encargada de graficar el texto que corresponda en el LCD
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutinaMenu();

	/*Función RutCalFuerza()-----------------------------------------------------------------------------------------------------------------------
	Descripción: Rutina encargada de calcular el buffer de fuerza y la fuerza promedio
	Entrada: nada
	Salida: nada
	//------------------------------------------------------------------------------------------------------------------------*/	
		void RutCalFuerza();

#endif 
